#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "msortchain.h"


/* allocates memory for a link and returns a pointer to the new link */
link* create_link(int data){
  link* l=(link*) malloc(sizeof(link));
  l->data=data;
  l->next=NULL;
  return l;
}
/* creates a new link and inserts it at the head of the list */
link* insert_first(link* first, int data){
  link* new=create_link(data);
  new->next=first;
  return new;
}

/* free the memory for the linked list*/
void free_list(link* list){
  link*ptr=list;
  while(ptr!=NULL){
    ptr=ptr->next;
    free(list);
    list=ptr;
  }
}

/* splits the list in the middle and returns the second half */
link* split_middle(link* first){
  if(first==NULL) return NULL;
  link* ptr=first;
  link* mid=first;
  while(ptr!=NULL && ptr->next!=NULL){
    ptr=ptr->next;
    if(ptr->next !=NULL) {
      ptr=ptr->next;
      mid=mid->next;
    }
  }
  link* tmp=mid;
  mid=mid->next;
  tmp->next=NULL;
  return mid;
}

/*prints the linked list*/
void print_list(link* first){
  link* ptr=first;
  while(ptr!=NULL){
    printf("%d ",ptr->data);
    ptr=ptr->next;
  }
  printf("\n");
}
/* takes two links and returns a linked list composed of the same links but in order */
link* fuse_back(link* a,link* b){
  if(a==NULL) return b;
  else if(b==NULL) return a;
  link* res;
  if (a->data < b->data){
    res=a;
    res->next=fuse_back(a->next,b);
  }
  else{
    res=b;
    res->next=fuse_back(a,b->next);
  }
  return res;
}

/* Splits the list until only single elements remains then fuses all of it back together in the right order */
link* msort(link* first){
  if(first==NULL || first->next==NULL) return first;
  link* first_half=first;
  link* sec_half=split_middle(first);

  first_half=msort(first_half);
  sec_half=msort(sec_half);

  first=fuse_back(first_half,sec_half);
  return first;
}
