/*
Auteur : Vincent DAO
Classe : INFO 1 à l'ESIPE
But : TP
*/
#include <stdio.h>
#include <stdlib.h>


int main()
{
    FILE *f= fopen("ex5.c","r");
    if (f==NULL){
        printf("Error, unable to open file. Terminating program. \n");
        return 0;
    }
    char c;
    while(!feof(f)){
        c=fgetc(f);
        printf("%c", c);
    }
    fclose(f);
    return 0;
}