/*
Auteur : Vincent DAO
Classe : INFO 1 à l'ESIPE
But : TP
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <limits.h>

void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void bubbleSort(int t[], int size){
    int i,j;
    for(i=0;i<size-1;i++){
        for(j=0;j<size-i-1;j++){
            if(t[j]>t[j+1]) swap(&t[j],&t[j+1]);
        }
    }
}
int* creaTableau(int size){
    /*Allocation du tableau qui a la taille indiquée par l'utilisateur*/
    int* t = (int*) malloc(size * sizeof(int));	
	if(t == NULL) {
		printf("Problème allocation mémoire\n");
		exit(EXIT_FAILURE);
	}
    return t;
}
/*Fonction pour remplir le tableau*/
/*Valeur maximale, juste pour ne pas avoir un affichage horrible*/
void fillTableau(int t[],int size,int max){
    int i;
    for(i=0; i<size; i++) t[i] = rand()%max; 
}
/*Fonction pour afficher le tableau*/
void printTab(int t[], int size) {
	int i;
	printf("[");
	for(i=0;i<size-1;i++) {
		printf("%d, ",t[i]);	
	}
	if(size>0)
		printf("%d",t[size-1]);
	printf("]\n");
	
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
int main(int argc, char const *argv[])
{
    srand(time(NULL));
    printf("Entrez le nombre d'éléments que doit contenir le tableau.\n");
    int size=-1;
    while(size<1) {
        printf("Il faut que la valeur soit positive.\n");
        size=secureInput();
    }
    printf("Taille du tableau : %d\n",size);
    int* t=creaTableau(size);
    /*Remplit le tableau avec des valeurs aléatoires*/
    /*Changer la valeur max pour un tableau avec des valeurs max plus petites ou grandes*/
    fillTableau(t,size,999);
    printf("Avant tri : \n");
    printTab(t,size);
    bubbleSort(t,size);
    printf("Post tri : \n");
    printTab(t,size);
    return 0;
}
