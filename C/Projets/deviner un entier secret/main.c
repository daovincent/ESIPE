/*
Auteur : Vincent DAO
Classe : INFO 1 à l'ESIPE
But : TP
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

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
    printf("Bienvenue dans le jeu où il faut deviner un entier secret !\n");
    printf("Veuillez commencer par entrer un entier positif qui déterminera la limite maximale de l'entier\n");
    printf("Notez que tout input incorrect vous obligera à entrer une nouvelle valeur jusqu'à ce qu'elle soit correcte...\n");

    int max=0;
    while (max<1) max=secureInput();
    printf("Bien ! Une valeur x a ete generee aleatoirement entre 0 et %d, bonne chance pour la trouver\n",max);
    printf("Vous pouvez entrer 0 ou autre chose qu'un nombre pour abandonner.\n");
    int x=rand()%max;
    int guess =-2;
    int try=0;
    while (guess !=x){
        if(guess==-1){
            printf("Vous avez abandonne ! Nombre d'essais sans trouver : %d",try-1);
            return 0;
        }
        if(try!=0)printf("Mauvaise réponse ! reessayez ! (Ou entrez -1 pour quitter)");
        try++;
        guess = secureInput();
    }
    printf("Bravo, vous avez trouve ! %d essais ont ete nécessaires . \n",try);

    return 0;
}
