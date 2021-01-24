/*
Auteur : Vincent DAO
Classe : INFO 1 à l'ESIPE
But : TP
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*pour chaine de caractères uniquement*/
void affichage2d( char ** tabchaine, int nblines){
  int i=0;
  for (i = 0; i < nblines; i++) {
    printf("%s\n",tabchaine[i]);
  }
}


int main(int argc, char *argv[]) {

  printf("Ce programme affiche les arguments qui ont été entrés en ligne de commande à l'exécution\n");
  if (argc <=1){
    printf("Won't do anything if you don't give any args\n");
    return 0;
  }


  char** tabchaine;
  if ((tabchaine= malloc(argc*sizeof(char*)))==NULL){
    printf("Memory allocation error, terminating execution.\n");
    exit(0); /*erreur allocation echouée*/
  }
  /*print_info_zone(tabchaine);*/
  int i;
  for (i=0;i<argc;i++){
    if ((tabchaine[i]= malloc( (strlen(argv[i])+1)*sizeof(char) ) )==NULL){
      printf("Memory allocation error, terminating execution.\n");
      exit(0); /*erreur allocation echouée*/
    }
    strcpy(tabchaine[i],argv[i]);
  }
  affichage2d(tabchaine, argc);

  for (i=0; i<argc;i++){
    free(tabchaine[i]);
  }
  free(tabchaine);




  return 0;
}
