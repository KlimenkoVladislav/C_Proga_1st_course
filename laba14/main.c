#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Student sStudent;
typedef struct Node sNode;

struct Student{
    int group;
    int srball;
    char *f;
    char *name;
};

struct Node{
    sStudent data;
    struct Node *prev;
    struct Node *next;
    struct Node *down;
    struct Node *up;
};

void AddNewNodeInEnd(sNode *new_node, char *names[], char *surnames[]){
    new_node->data.name = names[rand()%10];
    new_node->data.f = surnames[rand()%11];
    new_node->data.group = rand()%1000;
    new_node->data.srball = rand()%100;
    new_node->prev = NULL;
    new_node->next = NULL;
    new_node->down = NULL;
    new_node->up = NULL;
}

void PrintOneNode(sNode *here){
    printf("Имя - %s; Фамилия - %s; Группа - %d; Средний балл - %d\n", here->data.name, here->data.f, here->data.group, here->data.srball);
}

void Prohodochka(sNode *here){
    printf("\nНачальная позиция:\n");
    PrintOneNode(here);
    
    while (1){
        int a;
        printf("\n2 - вниз; 4 - назад; 6 - вперед; 8 - вверх; 0 - выход: ");
        scanf("%d", &a);
        
        if (a == 2 && here->down != NULL){ 
            here = here->down; 
            PrintOneNode(here); 
        }
        else if (a == 4 && here->prev != NULL){ 
            here = here->prev; 
            PrintOneNode(here); 
        }
        else if (a == 6 && here->next != NULL){ 
            here = here->next; 
            PrintOneNode(here); 
        }
        else if (a == 8 && here->up != NULL){ 
            here = here->up; 
            PrintOneNode(here); 
        }
        else if (a == 0) { 
            break; 
        }
        else { 
            printf("Некорректное направление\n"); 
        }
    }
}

int main(){
    srand(time(NULL));
    char *names[] = {"Иван", "Петр", "Сидор", "Алексей", "Дмитрий", "Сергей", "Андрей", "Михаил", "Николай", "Александр"};
    char *surnames[] = {"Соколов", "Зайцев", "Соловьёв", "Фролов", "Максимов", "Тимофеев", "Баранов", "Быков", "Денисов", "Фомин", "Гончаров"};
    
    int n, k;
    printf("Введите количество студентов в первом списке: ");
    scanf("%d", &n);
    printf("Введите количество студентов во втором списке: ");
    scanf("%d", &k);

    sNode *head1 = NULL;
    sNode *tail1 = NULL;
    sNode *prev = NULL;
    
    for (int i = 0; i < n; i++){
        sNode *newNode = (sNode*)malloc(sizeof(sNode));
        AddNewNodeInEnd(newNode, names, surnames);
        
        if (head1 == NULL) {
            head1 = newNode;
            tail1 = newNode;
            prev = newNode;
        } else {
            tail1->next = newNode;
            newNode->prev = tail1;
            tail1 = newNode;
        }
    }
    
    sNode *head2 = NULL;
    sNode *current1 = head1;
    
    for (int i = 0; i < k; i++){
        sNode *newNode = (sNode*)malloc(sizeof(sNode));
        AddNewNodeInEnd(newNode, names, surnames);
        if (head2 == NULL) {
            head2 = newNode;
        } else {
            sNode *last = head2;
            while (last->next != NULL) {
                last = last->next;
            }
            last->next = newNode;
            newNode->prev = last;
        }
        
        if (current1 != NULL) {
            current1->down = newNode;
            newNode->up = current1;
            current1 = current1->next;
        }
    }
    Prohodochka(head1);
}