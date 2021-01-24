#include <stdio.h>
int main(int argc, char* argv[]){
   if (argv[1]==NULL)return 0;
   printf("%s",argv[1]);
   if (argv[2]==NULL)return 0;
  printf("%s",argv[2]);
  if (argv[3]==NULL)return 0;
  printf("%s",argv[3]);
   return 0;
}