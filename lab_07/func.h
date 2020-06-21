#ifndef func_h
#define func_h

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <math.h>

typedef struct matrix_t
{
    unsigned int size;
    int **data;
    int **cost;
}matrix_t;

//arr_func
int deiksrt(const matrix_t *matrix, int ifrom, int ito, int ver[], int *k);
matrix_t *create_matrix(unsigned int n);
void free_matrix(matrix_t *matrix);
matrix_t *read_matrix(FILE *f);
void print_matrix(FILE *f, const matrix_t *mtr);
void free_matrix_rows(int **data, int n);
int **allocate_matrix_rows(size_t n);

//gvedit
void output_graph_to_png(const matrix_t *a);
void output_got_to_png(const matrix_t *a, int mat[], int k_mat, int ito);

//scan_int
int scan_choise(void);

//time
int menu_value(void);
unsigned long long int tick(void);

#endif // func_h
