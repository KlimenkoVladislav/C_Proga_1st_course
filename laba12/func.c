#include "head.h" 

long long get_time_usec() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (long long)tv.tv_sec * 1000000LL + tv.tv_usec;
}

void ZapolnenieForTest(struct Student *student){
    student->f = "__Фамилия__";
    student->name = "__Имя__";
    student->group = rand()%1000;
    student->srball = rand()%101;
}

void zapolnenie(struct Student *student){
    char *for_f = malloc(100*sizeof(char));
    char *for_name = malloc(100*sizeof(char));
    if (for_f == NULL){ return; }
    if (for_name == NULL){ return; }

    printf("\nВведите фамилию студента: ");
    fgets(for_f, 100*sizeof(char), stdin);
    char *na_raz = realloc(for_f, (strlen(for_f))*sizeof(char));
    if (na_raz == NULL){ return; }
    na_raz[strlen(na_raz)-1] = '\0';
    student->f = na_raz;

    printf("Введите имя студента: ");
    fgets(for_name, 100*sizeof(char), stdin);
    na_raz = realloc(for_name, (strlen(for_name))*sizeof(char));
    if (na_raz == NULL){ return; }
    na_raz[strlen(na_raz)-1] = '\0';
    student->name = na_raz;

    do{
        printf("Введите номер группы студента: ");
        scanf("%d", &student->group);
    }while(student->group <= 0 || student->group >= 10000);

    do{
        printf("Введите средний балл студента по физике: ");
        scanf("%f%*c", &student->srball);
    }while(student->srball < 0.0 || student->srball > 100.0);
}

void print(const struct Student *students, int n){
    printf("Фамилия         Имя             Группа     Балл по физике\n");
    for (int i = 0; i<n; i++){
        printf("%s      %s          %d          %.2f\n", students[i].f, students[i].name, students[i].group, students[i].srball);
    }
}

int sravnenie_grupp(const struct Student *A, const struct Student *B){
    if (A->group < B->group){ return 1; }
    return 0;
}

int sravnenie_ballov(const struct Student *A, const struct Student *B){
    if (A->srball < B->srball){ return 1; }
    return 0;
}

void sort(struct Student *students, int n, int (*sravnenie)(const struct Student *A, const struct Student *B)){
    struct Student for_swap;
    for (int i = 0; i<n-1; i++){
        int index_min = i;
        for (int j = i+1; j<n; j++){
            if (sravnenie(&students[j], &students[index_min])){
                index_min = j;
            }
        }
        if (index_min != i){
            for_swap = students[i];
            students[i] = students[index_min];
            students[index_min] = for_swap;
        }
    }
}