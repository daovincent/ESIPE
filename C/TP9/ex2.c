/*
Auteur : Vincent DAO
Classe : INFO 1 à l'ESIPE
But : TP
*/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {

int dimx,dimy;

do{
  printf("Donnez deux dimensions entières positives inférieurs à 100\n");
  if(scanf("%d %d",&dimx, &dimy)!=1) {
    scanf("%*[^\n]");
  }
}while (dimx<=0 || dimx >=100 || dimy <=0 || dimy >=100);
  char **tab = NULL;
  int i,j;

  if ((tab = malloc(dimx*sizeof(char*))) == NULL)
  {
      printf("Erreur d'allocation de mémoire, fin du programme.\n");
      exit(0); /*erreur allocation echouée*/
  }
  for (i=0 ;i<dimx ; i++){
/* Allocation de la mémoire*/
    if ((tab[i]= malloc(dimy*sizeof(char))) == NULL)
    {
      printf("Erreur d'allocation de mémoire, fin du programme.\n");
        exit(0); /*erreur allocation echouée*/
    }
    for (j=0; j<dimy ;j++) { /*stockage des lettres dans le tableau et affichage*/
      tab[i][j]=( (i+j)%26 + 'a' );
      printf("%c ", (i+j)%26 + 'a'  );
    }
    printf("\n");
  }
  for (i = 0; i < dimx; i++) { /* on libère chaque ligne du tableau*/
    free(tab[i]);
  }
  free(tab); /*on libère la première ligne du tableau*/
  return 0;
}
