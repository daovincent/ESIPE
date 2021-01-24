/*
Auteur : Vincent DAO
Classe : INFO 1 à l'ESIPE
But : TP
*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <limits.h>


/*Fonction de comparaison pour le quicksort*/
int compare (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}
/*Fonction pour un input sécurisé, objectif : entier positif non nul*/
int secureInput(){ 
    char* remaining;
    errno=0;
    char number[1024];
    printf("Veuillez entrer un entier\n");
    if(!fgets(number,1024,stdin)) return 0; /*input failed*/

    int a=strtol(number, &remaining,10);
    if (number==remaining) {
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
    
    return a;
}
/*Fonction de recherche dichotomique*/
int binarySearch(int t[],int size, int cible){
    /*Début de la recherche dichotomique*/
    int deb=0;
    int fin=size-1;
    int mid=(deb+fin)/2;
    while(deb<=fin){
        if(t[mid]<cible)deb=mid+1;
        else if (t[mid]==cible){
            return mid+1;
        }
        else fin=mid -1;
        mid = (deb+fin)/2;
    }
    return 0;
}
int main(int argc, char const *argv[])
{
    srand(time(NULL));
    printf("Entrez le nombre d'éléments que doit contenir le tableau trié.\n");
    int size=-1;
    while(size<1) {
        printf("Il faut que la valeur soit positive.\n");
        size=secureInput();

    }
    printf("Taille du tableau : %d\n",size);
    int i;
    /*Allocation du tableau qui a la taille indiquée par l'utilisateur*/
    int* t = (int*) malloc(size * sizeof(int));	
	if(t == NULL) {
		printf("Problème allocation mémoire\n");
		exit(EXIT_FAILURE);
	}
    /*Remplit le tableau avec des valeurs aléatoires*/
    for(i=0; i<size; i++) t[i] = rand()%9999; /*Valeur maximale, juste pour ne pas avoir un affichage horrible*/
    /*Trie le tableau avec une fonction de tri native*/
    qsort(t,size,sizeof(int),compare);
    
    printf("Entrez l'entier qu'il faut chercher dans le tableau (autre chose qu'un entrer sera automatiquement 0)\n");
    int cible=secureInput();
    printf("La valeur est : %d\n",cible);
    int res=binarySearch(t,size,cible);
    if(res>0) printf("La position de la valeur est : %d",res);
    else printf("La valeur n'est pas dans le tableau\n");

    free(t);
    return 0;
}
