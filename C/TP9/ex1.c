/*
Auteur : Vincent DAO
Classe : INFO 1 à l'ESIPE
But : TP
*/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {

int sizeTab;
char buf[1024]; /*char buffer*/
do{
  printf("Veuillez entrer un entier positif inférieur à 2 000 000 000\n");
  fgets(buf,1024,stdin);
  sizeTab=atoi(buf);
}while (sizeTab<=0 || sizeTab>=2000000000);

int* tab;
tab = malloc(sizeof(int)*sizeTab); /* Allocation de la mémoire*/
   if (tab == NULL)
   {
       printf("Erreur d'allocation de mémoire, fin du programme.\n");
       exit(0); /*erreur allocation echouée*/
   }
int i;
for (i = 0; i < sizeTab; i++) {
  tab[i]=i+1;
  printf("%d ",tab[i] ); /*affichage du tableau*/
}
printf("\n");
free (tab); /* Libération de la mémoire allouée*/
return 0;
}
