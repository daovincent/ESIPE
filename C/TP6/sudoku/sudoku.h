#ifndef __SUDOKU__
#define __SUDOKU__

typedef int Board[9][9];
int check_row(Board grid, int row, int nb);
int check_col(Board grid, int col, int nb);
int check_zone(Board grid, int row, int col, int nb);
int check_nb(Board grid, int row, int col, int nb);
int check_empty(Board grid, int *row, int *col, int max);
void solve_grid(Board grid, int nb);
void nb_solution(Board grid, int max, int *nb);
void print_board(Board grid);
#endif /* __SUDOKU__ */
