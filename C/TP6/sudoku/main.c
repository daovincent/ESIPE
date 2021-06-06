#include <stdio.h>
#include <stdlib.h>
#include "sudoku.h"
#include "in_out.h"

int main(int argc, char* argv[]){
  Board B;

  if(fread_board(argv[1], B)!=1) return 1;
  print_board(B);
  solve_grid(B,9);
  return 0;
}
