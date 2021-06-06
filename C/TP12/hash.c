#include "hash.h"



/*  Functions doc is in .h file */



node *create_link(char word[]) {
    node *n = (node*) malloc(sizeof(node));
    n->word = malloc(strlen(word)+1);
    strcpy(n->word, word);
    n->next = NULL;
    return n;
}
list* create_list(){
    list *l = (list *) malloc(sizeof(list));
    l->size = 0;
    l->first = NULL;

    return l;
}

table* create_table(){
    int i;
    table* t=(table*) malloc(sizeof(table));
    for(i=0;i<SEAUX;i++) t->bucket[i]=NULL;
    t->size=0;
    return t;
}

void free_link(node *lnk) {
    node* tmp;
    while(lnk){
        tmp=lnk;
        lnk=lnk->next;
        free(tmp->word);
        free(tmp);
    }
}
void free_list(list *list) {
    free_link(list->first);
    free(list);
}

void free_table(table* t){
    int i;
    for (i = 0; i < SEAUX; i++) 
        if (t->bucket[i] != NULL) 
            free_list(t->bucket[i]);
    free(t);
}

int hash(char* word){
    int i;
    int h=0;
    for(i=0; word[i]!='\0';i++) h+=(i+1) * word[i];
    if (h<0) h++;
    return h%SEAUX; 
}

node* find(list* l, char* word){
    if(l==NULL) return NULL;
    
    node* ptr;
    for(ptr=l->first;ptr!=NULL;ptr=ptr->next){
        if(strcmp(ptr->word, word) == 0) return ptr;
    }
    return NULL;
}

list* insert_head(list* l, char*word){
    if(l==NULL) l=create_list();
    node* n=create_link(word);
    n->next=l->first;
    l->first=n;
    l->size++;
    return l;
}
void insert_table(table* t, char* word){
    node* n;
    int index=hash(word);
    n=find(t->bucket[index], word);
    if(n==NULL) t->bucket[index]=insert_head(t->bucket[index],word);
    t->size++;
}

int count_distinct(table* t){
    int i;
    int res=0;
    for(i=0;i<SEAUX; i++) 
        if (t->bucket[i]!=NULL) res+=t->bucket[i]->size;
    return res;
}

table* file_to_hashtable(FILE* f){
    table* t= create_table();
    char* word= (char*) malloc(MAXLENGTH * sizeof(char));
    while(fscanf(f,"%s",word)==1) insert_table(t,word);
    free(word);
    return t;
}