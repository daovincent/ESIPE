/*
Auteur : Vincent DAO
Classe : INFO 1 à l'ESIPE
But : TP
*/
#include <stdio.h>
#include <stdlib.h>
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

/* Allocate memory for an array which can contain `size`
   integers. The returned C array has memory for an extra last
   integer labelling the end of the array. */
int* allocate_integer_array(int size){
  int* new_tab;

  new_tab = (int*)malloc((size+1)*sizeof(int));
  if (new_tab == NULL){
    fprintf(stderr, "Memory allocation error\n");
    return NULL;
  }
  return new_tab;
}

/* Free an integer array */
void free_integer_array(int* tab){
  free(tab);
}
/*Fonction pour retourner la longueur d'un tableau d'entiers*/
int array_size(int* array){
    int i=0;
    while(array[i]!=-1)i++;
    return i;
}

/*Fonction qui vérifie si les 2 tableaux ont le même contenu (1 oui / 0 non)*/
int are_arrays_equal(int* first, int* second){
    int i,size=array_size(first);
    if (size!=array_size(second))return 0;
    for(i=0;i<size;i++) if(first[i]!=second[i]) return 0;
    return 1;
}

/*Fonction qui copie le contenu du tableau 1 dans le tableau 2 et retourne le tableau 2*/
int* copy_array(int* array){
    int size=array_size(array);
    int* tab=allocate_integer_array(size);
    int i;
    for(i=0;i<size;i++) tab[i]=array[i];
    tab[size]=-1;
    return tab;
}

/*Fonction pour afficher le tableau*/
void print_array(int* array) {
	int i;
    int size=array_size(array);
	printf("[");
	for(i=0;i<size-1;i++) {
		printf("%d, ",array[i]);	
	}
	if(size>0)
		printf("%d",array[size-1]);
	printf("]\n");
	
}

/*Fonction qui permet à l'utilisateur de remplir un tableau de la longueur qu'il souhaite*/
int* fill_array(void){
    int size=-1,i;
    printf("Veuillez entrer la taille du tableau. (<100)\n");
    while(size<1 ||size>100) {
        if(size>100)printf("Ce serait peut être un peu long de remplir %d valeurs à la main...\n",size);
        if(size<1) printf("La valeur doit être positive\n");
        size=secureInput();
    }
    printf("La taille du tableau est de : %d.\n",size);
    int* tab=allocate_integer_array(size);
    printf("Veuillez maintenant remplir le tableau avec %d valeurs.\n",size);
    for(i=0;i<size;i++) tab[i]=secureInput();
    tab[size]=-1;
    return tab;
}

/*Fonction qui remplit le tableau avec size entiers positifs compris entre 0 et max_entry*/
int* random_array(int size,int max_entry){
    int i;
    int* tab=allocate_integer_array(size);
    for(i=0; i<size; i++) tab[i] = rand()%max_entry; 
    tab[size]=-1;
    return tab;
}
/*Fonction qui concat 2 tableaux*/
int* concat_array(int* first, int* second){
    int i;
    int size1=array_size(first);
    int size2=array_size(second);
    /*int* tab=allocate_integer_array(size1+size2);*/
    int* tab= allocate_integer_array(size1+size2);
    for(i=0;i<size1;i++) tab[i]=first[i];
    for(i=size1;i<size1+size2;i++) tab[i]=second[i-size1];
    tab[size1+size2]=-1;
    
    return tab;
}

int* merge_sorted_arrays(int* first, int* second){
    int size1=array_size(first);
    int size2=array_size(second);
    int* tab= allocate_integer_array(size1+size2);
    int i,j=0,k=0;
    for(i=0;i<size1+size2 && j<size1 && k<size2;i++){
        if(first[j]<second[k]){
            tab[i]=first[j];
            j++;
        }
        else{
            tab[i]=second[k];
            k++;
        }
    }
    for(;j<size1;j++){
        tab[i]=first[j];
        i++;
    }
    for(;k<size2;k++){
        tab[i]=second[k];
        i++;
    }
    tab[size1+size2]=-1;
    return tab;

}

void split_arrays(int* array, int**first, int** second){
    int size=array_size(array);
    int siz1,siz2=size/2;

    if(size%2 !=0) siz1=(size/2) +1;
    else siz1=siz2;

    *first=allocate_integer_array(siz1);
    *second=allocate_integer_array(siz2);
    *(first[0]+siz1)=-1;
    *(second[0]+siz2)=-1;

    int i;
    for(i=0;i<size;i++){
        if (i<siz1) *(first[0]+i)=array[i];
        else *(second[0]+i-siz1) =array[i];
    }
}

int* merge_sort(int* array){
    int size=array_size(array);
    if(size<2) return array;

    int* tab1;
    int* tab2;

    split_arrays(array,&tab1,&tab2);
    printf("Split array in two part : \n");
    print_array(tab1);
    print_array(tab2);
    tab1=merge_sort(tab1);
    tab2=merge_sort(tab2);

    printf("Merge the two following ones : \n");
    print_array(tab1);
    print_array(tab2);
    return merge_sorted_arrays(tab1,tab2);
}
/* An empty main to test the compilation of the allocation and free
   functions. */
int main(int argc, char* argv[]){
    /*TESTS POUR EX 1 ET EX 2
    int* tab=random_array(10,100);
    printf("Size is : %d\n",array_size(tab));
    print_array(tab);
    int* tab2=fill_array();
    print_array(tab2);
    printf("Concatenation des 2 tableaux ...\n Resultat :\n");
    int* tab3=concat_array(tab,tab2);
    print_array(tab3);
    printf("Test de la copie du tableau 2 (celui avec les valeurs input utilisateur)\n");
    int* tab4=copy_array(tab2);
    printf("La copie a t-elle été réussie ? 1 : oui, 0 : non \n%d\n",are_arrays_equal(tab2,tab4));
    print_array(tab4);
    free_integer_array(tab);
    free_integer_array(tab2);
    free_integer_array(tab3);
    free_integer_array(tab4);

    FIN DES TESTS POUR EX 1 ET 2*/
    /*TESTS POUR EX 3 */
    int* t=random_array(20,100);
    printf("Size is : %d\n",array_size(t));
    printf("Tableau de base : \n");
    print_array(t);
    printf("Using a merge sort we get : \n");
    t=merge_sort(t);
    printf("Here is the sorted array : n");
    print_array(t);

    free_integer_array(t);
    /*FIN DES TESTS POUR EX 3*/
    return 0;
}