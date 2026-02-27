#include "head.h"

int main(){
    srand(time(NULL));

    int n;
    printf("Введите количество студентов: ");
    scanf("%d%*c", &n);
    struct Student students[n];
    for (int i = 0; i<n; i++){
        struct Student student;
        // zapolnenie(&student);
        ZapolnenieForTest(&student);
        students[i] = student;
    }
    print(students, n);
    long long start = get_time_usec();
    sort(students, n, sravnenie_grupp);
    long long end = get_time_usec();
    print(students, n);

    start = get_time_usec();
    sort(students, n, sravnenie_ballov);
    end = get_time_usec();
    print(students, n);

    printf("\nВремя сортировки: %lld микросекунд\n", end - start);
    printf("Время сортировки: %.3f миллисекунд\n", (end - start) / 1000.0);

    size_t bytes = n * sizeof(int);
    double kilobytes = bytes / 1024.0;
    double megabytes = kilobytes / 1024.0;
    
    printf("\nРазмер массива: %d элементов\n", n);
    printf("Объем памяти: \n");
    printf("  %zu байт\n", bytes);
    printf("  %.2f килобайт\n", kilobytes);
    printf("  %.3f мегабайт\n", megabytes);
}