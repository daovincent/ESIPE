#include <stdio.h>

#include "sudoku.h"

int check_row(Board grid, int row, int nb) {
    int i;
    for (i = 0; i < 9; i++) 
        if (grid[row][i] == nb)  return 0; 
    return 1;
}
int check_col(Board grid, int col, int nb) {
    int i;
    for (i = 0; i < 9; i++)
        if (grid[i][col] == nb)  return 0; 
    return 1;
}
int check_zone(Board grid, int row, int col, int nb) {
    int i, j;

    row -= row % 3;
    col -= col % 3;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) 
            if (grid[row + i][col + j] == nb)  return 0; 
    }
    return 1;
}
int check_nb(Board grid, int row, int col, int nb) {
    return check_row(grid, row, nb) &&
           check_col(grid, col, nb) &&
           check_zone(grid, row, col, nb);
}
int check_empty(Board grid, int *row, int *col, int max) {
    int i, j;
    for (i = 0; i < max; i++) {
        for (j = 0; j < max; j++) {
            if (grid[i][j] == 0) {
                *row = i;
                *col = j;
                return 1;
            }
        }
    }
    return 0;
}
void solve_grid(Board grid, int nb) {
    int i, row, col;
    if (check_empty(grid, &row, &col, nb) == 0) {
        print_board(grid);
        return;
    }
    for (i = 1; i <= nb; i++) {
        if (check_nb(grid, row, col, i)) {
            grid[row][col] = i;
            solve_grid(grid, nb);
            grid[row][col] = 0;
        }
    }
}
void nb_solution(Board grid, int max, int *nb) {
    int i, row, col;
    if (check_empty(grid, &row, &col, max) == 0) {
        *nb += 1;
        return;
    }
    for (i = 1; i <= max; i++) {
        if (check_nb(grid, row, col, i)) {
            grid[row][col] = i;
            nb_solution(grid, max, nb);
            grid[row][col] = 0;
        }
    }
}

void print_board(Board grid) {
    int i, j;
    printf("Sudoku grid:\n");
    for (i = 0; i < 9; i++) {
        printf("_____________________________________\n");
        for (j = 0; j < 9; j++) {
            if (j != 8) printf("| %d ", grid[i][j]);
            else printf("| %d |\n", grid[i][j]);
        }
    }
    printf("_____________________________________\n\n");
}