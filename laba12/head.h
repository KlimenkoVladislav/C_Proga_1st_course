#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

struct Student{
    int group;
    float srball;
    char *f;
    char *name;  
};

long long get_time_usec();
void ZapolnenieForTest(struct Student *student);
void zapolnenie(struct Student *student);
void print(const struct Student *students, int n);
int sravnenie_grupp(const struct Student *A, const struct Student *B);
int sravnenie_ballov(const struct Student *A, const struct Student *B);
void sort(struct Student *students, int n, int (*sravnenie)(const struct Student *A, const struct Student *B));