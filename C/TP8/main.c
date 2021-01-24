/*
Auteur : Vincent DAO
Classe : INFO 1 à l'ESIPE
But : TP
*/
#include <stdio.h>
#include <stdlib.h>

#define SIZE 200000

/*Si l'entrée est pair retourne val/2 sinon retourne 3*val+1*/
unsigned long int siPair (unsigned long int  val){
    if(val%2==0) return val/2;
    return (3*val)+1;
}

/*Fonction de calcul de la distance de vol + affichage*/
unsigned long int syrInput(unsigned long int val){
    /*printf("Entrez la valeur ici svp (entiers positifs only et max 200 000 000\n");
    int syracuse=-1;
    while(syracuse<1 || syracuse>200000000) syracuse=secureInput();*/
    printf("Affichage de la suite syracuse avec le nombre que vous avez entre...\n");
    unsigned long int i=1;
    printf("%ld ",val);
    while(val!=1){
        val=siPair(val);
        printf("%ld ",val);
        i++;
    }
    printf("\n\n");
    return i-1;
}

int dejaVu (unsigned long int val, unsigned long int* tab){
    if(tab[val]==-1) return 0;
    return 1;
}

/*Calcule la longueur de vol avec la methode memoisation*/
unsigned long int memoisation(unsigned long int val, unsigned long int* tab){
    if(val==1) return 0;
    if(dejaVu(val,tab)) return tab[val];
    return 1+ memoisation(siPair(val),tab);

}

int main(int argc, char const *argv[])
{

    unsigned long int i,vol,max=0;
    int pos;

    /*int i;*/
    unsigned long int tab[SIZE];
    for(i=0;i<=SIZE;i++) tab[i]=-1;

    for (i=1;i<=30;i++){
        vol=memoisation(i,tab);
        if(vol>max){
            max=vol;
            pos=i;
        }
        printf("%ld\n",i);
        printf("Distance de vol : %ld\n", vol);
        tab[i]=vol;
    }

    printf("Plus longue distance de vol : %ld pour la valeur %d\n",max,pos);
    /*
    unsigned long int test=27;
    printf("Test value : %ld\n",test);
    printf("Longueur de vol : %ld\n",memoisation(test,tab));
    printf("Longueur de vol : %ld\n",syrInput(test));
    */
    return 0;
}