#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define BUFF_SIZE 100

struct smth{
    char name[25];
    char id[5];
    char level[100];
};

float get_file_size(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        return -1;
    }
    
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fclose(file);
    
    return (float)size;
}

void Print(struct smth *massiv){
    for (int i = 0; i < 50; i++) {
        printf("Фамилия, имя: %s    Номер: %s   Уровень: %s\n", massiv[i].name, massiv[i].id, massiv[i].level);
    }
}

void find(){
    int id;
    printf("Введите id: "); scanf("%d", &id);

    FILE *file = fopen("database.dat", "rb");
    if (file == NULL){ printf("Не удалось открыть файл\n"); return; }

    struct smth temp;
    int found = 0;
    
    while(fread(&temp, sizeof(struct smth), 1, file) == 1){
        if(atoi(temp.id) == id){
            printf("\nСотрудник найден:\n");
            printf("Фамилия, имя: %s    Номер: %s   Уровень: %s\n", temp.name, temp.id, temp.level);
            found = 1;
            break;
        }
    }
    if(!found){ printf("Сотрудник с ID %d не найден\n", id); }

    fclose(file);
}

int compress(){
    FILE *file = fopen("database.dat", "rb");
    FILE *file_for_w = fopen("database.rle", "wb");
    char buf[sizeof(struct smth)];
    char *buf_for_new_file = NULL;
    int count_byte = 0;
    char temp = '*';
    int count = 0;
    while (fread(&buf, sizeof(struct smth), 1, file)){
        for (int i = 0; i<sizeof(struct smth); i++){
            if (temp == '*'){ temp = buf[i]; count++; }
            else if (buf[i] == temp){ count++; }
            else {
                count_byte+=2;
                buf_for_new_file = realloc(buf_for_new_file, count_byte*sizeof(char));
                buf_for_new_file[count_byte-2] = temp;
                buf_for_new_file[count_byte-1] = count;
                temp = buf[i];
                count = 1;
            }
        }
    }
    if (count > 0) {
        count_byte += 2;
        buf_for_new_file = realloc(buf_for_new_file, count_byte * sizeof(char));
        buf_for_new_file[count_byte-2] = temp;
        buf_for_new_file[count_byte-1] = count;
    }
    fwrite(buf_for_new_file, 1, count_byte, file_for_w);

    fclose(file);
    fclose(file_for_w);

    return count_byte;
}

void decompress(int count_byte){
    FILE *file = fopen("database.rle", "rb");
    FILE *file_for_w = fopen("end.dat", "wb");
    char buf[count_byte];
    char *buf_for_new_file = NULL;
    int count_new_buf = 0;
    char temp;
    int count;
    fread(&buf, count_byte, 1, file);
    for (int i = 0; i<count_byte; i+=2){
        temp = buf[i];
        count = buf[i+1];
        count_new_buf += count;
        buf_for_new_file = realloc(buf_for_new_file, count_new_buf*sizeof(char));
        for (int j = count_new_buf-count; j<count_new_buf; j++){
            buf_for_new_file[j] = temp;
        }
    }
    fwrite(buf_for_new_file, 1, count_new_buf, file_for_w);

    fclose(file);
    fclose(file_for_w);
}

int main(int argc, char *argv[]){
    if (argc < 2){ printf("Мало аргументов\n"); return -1; }
    else if (argc > 2){ printf("Много аргументов\n"); return -1; }

    char *filename = argv[1];
    int fd = open(filename, O_RDONLY);
    if (fd == -1){ printf("Ошибка при открытии файла\n"); return -1; }

    struct smth *massiv = malloc(50*sizeof(struct smth));
    int struct_num = 0;
    char buff[BUFF_SIZE];
    ssize_t len_stroka;
    int pole_num = 0;
    int ptr_on_place = 0;

    while((len_stroka = read(fd, buff, BUFF_SIZE)) > 0){
        for (int i = 0; i<len_stroka; i++){
            char now;
            if (buff[i] == ';'){ now = '\0'; }
            else if (buff[i] == '\n'){ struct_num++; pole_num = 0; ptr_on_place = 0; continue; }
            else { now = buff[i]; }

            if (pole_num == 0){ massiv[struct_num].name[ptr_on_place] = now; }
            else if (pole_num == 1){ massiv[struct_num].id[ptr_on_place] = now; }
            else if (pole_num == 2){ massiv[struct_num].level[ptr_on_place] = now; }

            if (now == '\0'){ pole_num++; ptr_on_place = 0; continue; }

            ptr_on_place++;
        }
    }

    Print(massiv);
    close(fd);

    FILE *file = fopen("database.dat", "wb");
    if (file == NULL){ printf("Не удалось открыть файл\n"); return -1; }
    fwrite(massiv, sizeof(struct smth), 50, file);
    fclose(file);

    find();
    int count_byte = compress();
    decompress(count_byte);

    printf("Размер до: %.0f б, Размер после: %.0f б. Сжатие: %.2f процентов\n", get_file_size("database.dat"), get_file_size("database.rle"), 
            (get_file_size("database.dat")-get_file_size("database.rle"))/get_file_size("database.dat")*100);
}