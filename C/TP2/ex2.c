/*
Auteur : Vincent DAO
Classe : INFO 1 à l'ESIPE
But : TP
*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int main(int argc, char const *argv[])
{
    printf("Le but de ce programme est d'additionner les 2 entiers passés par ligne de commande lors de l'appel.\nS'ils n'y sont pas, le programme ne demandera pas d'input.\n");



    if(argc==3){
            char* remaining;
    /*reset errno to 0 before each call*/
    errno=0;
    int a=strtol(argv[1], &remaining,10);
    if (argv[1]==remaining) {
        printf("The first argument is not a number. Terminating program.\n");
        return 0;
    }
    else if (errno==ERANGE && a== INT_MIN) {
        printf("Invalid number : underflow occured \n");
        return 0;
    }
    else if (errno==ERANGE && a== INT_MAX) {
        printf("Invalid number : overflow occured (number : %d) \n",a);
        return 0;
    }
    else if (errno ==0 && argv[1] && *remaining != 0) printf("Additionnal characters were ignored.\n");

    errno=0;
    int b=strtol(argv[2], &remaining,10);
    if (argv[2]==remaining) {
        printf("The second argument is not a number. Terminating program.\n");
        return 0;
    }
    else if (errno==ERANGE && b== INT_MIN) {
        printf("Invalid number : underflow occured \n");
        return 0;
    }
    else if (errno==ERANGE && b== INT_MAX) {
        printf("Invalid number : overflow occured (number : %d) \n",a);
        return 0;
    }
    else if (errno ==0 && argv[2] && *remaining != 0) printf("Additionnal characters were ignored.\n");
    printf("%d + %d = %d\n",a,b,a+b);
    }
    else if (argc>3) printf("Number of arguments: %d. This program will ignore all arguments except the first 2, which should be numbers.\n",argc);
    else printf("You didn't enter a number / not enough numbers so nothing is gonna happen. (need 2 numbers to perform addition)\n");
   
    return 0;
}
