#define _DEFAULT_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXSIZESTR 30

typedef struct Cell{
  char* first_name;
  char* last_name;
  int age;
  struct Cell *next;
}Cell, *List;

Cell* allocate_cell(char* first,char* last, int age){
  Cell* c= (Cell*)malloc(sizeof(Cell));
  c->first_name=strdup(first);
  c->last_name=strdup(last);
  c->age= age;
  c->next=NULL;
  return c;
}
int age_order(Cell* p1, Cell* p2){
  if(p1==NULL || p2==NULL) return 0;
  if(p1->age == p2->age) return 0;
  else if(p1->age <p2->age) return -1;
  else return 1;
}
int name_order(Cell *p1, Cell *p2){
  if(p1 ==NULL || p2 == NULL) return 0;
  else return strcmp(p1->first_name,p2->first_name);
}
void ordered_insertion(List* l, Cell* new, int order_func(Cell*, Cell*)){
  if (new==NULL) return;
  Cell* ptr=*l;
  if(*l==NULL || order_func(ptr,new)==1){
      new->next=ptr;
      *l=new;
  }
  else{
    /* Recursive method */
    ordered_insertion(&((*l)->next),new, order_func);
    /* Iterative method */
    /*
    Cell* prev=ptr;
    ptr=ptr->next;
    while(ptr!=NULL && order_func(ptr,new)!=1){
      ptr=ptr->next;
      prev=prev->next;
    }
    prev->next=new;
    new->next=ptr;
    */
  }
}
void print_list(List l){
  Cell* ptr=l;
  while(ptr != NULL){
    printf("First name : %s, Last name : %s, age : %d \n",
    ptr->first_name,ptr->last_name,ptr->age);
    ptr=ptr->next;
  }
}
void free_list(List l){
  Cell* ptr=l;
  Cell* ptr2;
  while(ptr!=NULL){
    ptr2=ptr;
    ptr=ptr->next;
    free(ptr2->first_name);
    free(ptr2->last_name);
    free(ptr2);
  }

}
int main(){
  FILE *f=fopen("liste_nom.txt","r");
  char firstn[30];
  char lastn[30];
  int age;
  Cell* c=NULL;
  List l=NULL;
  char choice;

  while(choice!='a' && choice!='n'){
    printf("Type 'a' for age order or 'n' for name order.\n");
    scanf("%c",&choice);
  }
  if(choice=='a'){
    printf("You chose the age order\n");
    while(fscanf(f,"%s %s %d",firstn, lastn, &age)==3){
      c=allocate_cell(firstn,lastn,age);
      ordered_insertion(&l,c,age_order);

    }
  }
  else if(choice=='n'){
    printf("You chose the name order\n");
    while(fscanf(f,"%s %s %d",firstn, lastn, &age)==3){
      c=allocate_cell(firstn,lastn,age);
      ordered_insertion(&l,c,name_order);
    }
  }

  fclose(f);
  print_list(l);
  free_list(l);
  return 0;
}
