#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "msortchain.h"

int main(int argc, char const *argv[]) {
  srand(time(NULL));
  link* l= create_link(10);
  int i;
  for(i=0;i<29;i++){
    l=insert_first(l,rand()%1000);
  }
  print_list(l);
  printf("Sorting ...\n");
  l=msort(l);

  printf("Sorting finished. Here's the result. \n");
  print_list(l);
  return 0;
}
