#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
    char ch;
    int c=0;
    int w=0;
    int l=0;

    while ((ch = fgetc(f)) != EOF) {
        c++;

        if(ch == ' ' || ch == '\t' || ch == '\0' || ch == '\n') {
            w++;
        }
        if(ch == '\0' || ch == '\n') l++;
    }
    printf("The given file contains %d characters, %d words and %d lines.\n",c,w,l+1);

    fclose(f);
    return 0;
}
