#ifndef __HASH_H__
#define __HASH_H__

#define SEAUX 8096
#define MAXLENGTH 80
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
typedef struct node {
    char *word;
    struct node *next;
} node;
typedef struct list{
    node* first;
    int size;
}list;

typedef struct _table {
    list *bucket[SEAUX] ;
    int size; /* nombre de mots dans la table */
} table;

/**
 * Create a node representing an occurence of "word"
 * return said node
 */
node *create_link(char word[]);

/**
 * Create an empty list
 * return said list
 */
list* create_list();

/**
 * Create a table
 * return said table
 */
table* create_table();

/**
 * Free functions.
 */
void free_link(node *lnk);
void free_list(list *list);
void free_table(table* t);

/**
 * return a hash value for a given word
 */
int hash(char* word);
/**
 * finds the node for the given word in the table 
 * if not present return null
 */
node* find(list* l, char* word);
/**
 * insert a node with the given word at the head of the list
 */
list* insert_head(list* l, char*word);
/**
 * insert a word in the table
 */
void insert_table(table* t, char* word);
/**
 * return the number of distinct words in the table
 */
int count_distinct(table* t);
/**
 * return a hashtable with words from a given file as input
 */
table* file_to_hashtable(FILE* f);
#endif