/*
Auteur : Vincent DAO
Classe : INFO 1 à l'ESIPE
But : TP
*/
#include <stdio.h>

void print_var(int n){
    printf("Value of the variable : %d\n", n);
}

void print_pointer(int* p){
    printf("Pointer address : %p and Pointed value : %d\n", p, *p);
}

void set_pointer(int* p, int n){
    *p=n;
}

int main(int argc, char const *argv[])
{
    int a;   /*a n'a pas de valeur*/
    int*p = &a; /*on donne au pointeur p la même valeur que le pointeur de a donc p devient le pointeur de a*/
    print_var(a); /* a n'a toujours pas de valeur, pas initialisé*/
    a=53; /* a prend la valeur 53*/
    print_pointer(p); /* print le pointeur et la valeur pointée qui est maintenant 53*/
    set_pointer(p,42); /*change la destination du pointeur p à 42 donc a=42*/
    print_pointer(p);
    print_var(a);
    return 0;
}
