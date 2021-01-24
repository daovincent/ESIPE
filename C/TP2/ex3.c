/*
Auteur : Vincent DAO
Classe : INFO 1 à l'ESIPE
But : TP
*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int printNumbersMont(int n, int i){
    if (i>n || i<=0) return 0;
    printf("%d ",i);
    return printNumbersMont(n,i+1);
}

int printNumbersDesc(int n, int i){
    if (i<=0 ||i>n) return 0;
    printf("%d ",i);
    if (i==1)return printNumbersMont(n,i);
    return printNumbersDesc(n,i-1);
}


int main(int argc, char const *argv[])
{
    char* remaining;
    /*reset errno to 0 before each call*/
    errno=0;
    int n=strtol(argv[1], &remaining,10);
    if ( argc<2 ||argv[1]==NULL){
        printf("Il faut entrer un entier positif en argument lors de l'exec. \n");
        return 0;
    }
    if (argv[1]==remaining) {
        printf("The first argument doesn't contain a number. Terminating program.\n");
        return 0;
    }
    else if (errno==ERANGE && n== INT_MIN) {
        printf("Invalid number : underflow occured \n");
        return 0;
    }
    else if (errno==ERANGE && n== INT_MAX) {
        printf("Invalid number : overflow occured (number : %d) \n",n);
        return 0;
    }
    else if (errno ==0 && argv[1] && *remaining != 0) printf("Additionnal characters were ignored. %s\n",remaining);

    printf("Non recursive ver : \n");
    int i;
    for (i=n; i>0; i--){
        printf("%d ",i);
    }

    for (i=1; i<=n; i++){
        printf("%d ",i);
    }
    printf("\nRecursive ver : \n");
    printNumbersDesc(n,n);
    printf("\n");
    return 0;
}
