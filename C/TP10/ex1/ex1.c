/*
Auteur : Vincent DAO
Classe : INFO 1 à l'ESIPE
But : TP
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap_mem(void* z1, void* z2, size_t size){
    char tmp, *a=(char*)z1, *b=(char*)z2;
    while (size>0)
    {
        size--;
        tmp=a[size],a[size]=b[size],b[size]=tmp;
    }
    

}

int main(int argc, char const *argv[])
{
    char tab1[8]={',','g','4','y','n','$','+'};
    char tab2[8]={'7','a','c','?','9','3','l','-'};
    int tab3[5]={1,2,3,4},tab4[5]={5,4,7,8};
    int a=1,b=5;
    double c=1.0,d=3.14;
    swap_mem(tab1,tab2,sizeof(tab1)-1);
    int length=strlen(tab1);
    printf("\nSur des chaines de caractères :\n");
    printf("première chaine de caractères : ");
    int i;
    
    for(i=0;i<length;i++) {
        printf("%c ",tab1[i]);
    }
    printf("\ndeuxième chaine de caractères : ");
    for(i=0;i<length;i++) {
        printf("%c ",tab2[i]);
    }
    printf("\nSur des ints :");
    swap_mem(&a,&b,sizeof(a));
    printf("\nItem a= %d, Item b= %d\n",a, b);

    printf("\nSur des float :");
    swap_mem(&a,&b,sizeof(a));
    printf("\nItem c= %f, Item d= %f\n",c, d);

    printf("\nSur des tableau d'int :");
    swap_mem(tab3,tab4,sizeof(tab3));
    printf("\nTab3 :");
    for(i=0;i<4;i++) {
        printf("%d ",tab3[i]);
    }
    printf("\nTab4 :");
    for(i=0;i<4;i++) {
        printf("%d ",tab4[i]);
    }

    return 0;
}
