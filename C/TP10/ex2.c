/*
Auteur : Vincent DAO
Classe : INFO 1 à l'ESIPE
But : TP
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cell{
    char* first_name;
    char* last_name;
    int age;
    struct cell* next;
}Cell, *List;

Cell* allocate_cell(char* first,char* last, int age){
    Cell* c=(Cell*) malloc(sizeof(Cell));
    if (c== NULL){
        printf("Failed to allocate, not enough memory. Terminating program.\n ");
        exit(1);
    }
    c->first_name=first;
    c->last_name=last;
    c->age=age;
}

int age_order(Cell* p1, Cell*p2){
    if(p1->age<p2->age)return -1;
    else if(p1->age==p2->age) return 0;
    return 1;

}

int name_order(Cell* p1, Cell* p2){
    int res=strcmp(p1->first_name,p2->first_name);
    if (res==0) res=strcmp(p1->last_name,p2->last_name);
    if (res==0) res=strcmp(p1->age,p2->age);
    return res;
}

void ordered_insertion(List* l,Cell* new, int order_func(Cell*, Cell*)){
    
}

void print_list(List l){
    printf("First name :%s, Last name : %s, Age : %d\n", l->first_name,l->last_name,l->age);
}

void free_list(List l){
    free(l);
}

int main(int argc, char const *argv[])
{

    return 0;
}
