/*
Auteur : Vincent DAO
Classe : INFO 1 à l'ESIPE
But : TP
*/
#include <stdio.h>

int puissance(int a, int n){
    if (n<1){
        printf("n doit être un entier positif non nul.\n");
        return 0;
    }
    int res=a,i;
    for(i=2;i<=n;i++){
        res=res*a;
    }
    return res;
}

int main(int argc, char const *argv[])
{
    /*Changer la valeur des 2 variables ci dessous pour obtenir des résultats différents*/
    int nbr = 2; /* Le nombre */
    int pui = 12; /* La puissance */
    printf("Nombre : %d Puissance : %d\n",nbr,pui);
    printf("Résultat : %d\n",puissance(nbr,pui));
    return 0;
}
