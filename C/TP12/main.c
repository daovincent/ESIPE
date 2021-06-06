#include "hash.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{

    if(argc<2){
        printf("Please input a text file as argument\n");
        return 1;
    }
    printf("You gave the file %s as input.\n",argv[1]);
    FILE* f=fopen(argv[1],"r");
    if (f == NULL) {
        fprintf(stderr, "Error opening file for reading: %s\n", argv[1]);
        return 1;
    }
    
    table* hash=file_to_hashtable(f);

    printf("The given file contains %d distinct words.\nTotal number of words : %d \n", 
        count_distinct(hash), hash->size);

    free_table(hash);
    fclose(f);
    return 0;
}
