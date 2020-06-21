#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "defines.h"
#include "func.h"

matrix_t *read_matrix(FILE *f)
{
    rewind(f);
    unsigned int n;
    if (fscanf(f, "%u", &n) != 1)
    {
        printf("Invalid file content!\n");
        return NULL;
    }
    
    matrix_t *res = create_matrix(n);
    int distance = 0;
    int cost = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (fscanf(f, "%d", &distance) != 1)
            {
                printf("Invalid file content!\n");
                return NULL;
            }
            res->data[i][j] = distance;
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (fscanf(f, "%d", &cost) != 1)
            {
                printf("Invalid file content!\n");
                return NULL;
            }
            if (res->data[i][j] == 0 && cost != 0)
            {
                printf("Invalid file content!\n");
                return NULL;
            }
            res->cost[i][j] = cost;
        }
    }
    return res;
}

void print_matrix(FILE *f, const matrix_t *mtr)
{
    if (mtr != NULL)
    {
        printf("Distances:\n");
        for (int i = 0; i < mtr->size; i++)
        {
            for (int j = 0; j < mtr->size; j++)
            {
                fprintf(f, "%5d ", mtr->data[i][j]);
            }
            putc('\n', f);
        }
        printf("\nCosts:\n");
        for (int i = 0; i < mtr->size; i++)
        {
            for (int j = 0; j < mtr->size; j++)
            {
                fprintf(f, "%5d ", mtr->cost[i][j]);
            }
            putc('\n', f);
        }
    }
}

void free_matrix(matrix_t *matrix)
{
    if (matrix != NULL)
    {
        free_matrix_rows(matrix->data, matrix->size);
        free_matrix_rows(matrix->cost, matrix->size);
        free(matrix);
    }
}

void free_matrix_rows(int **data, int n)
{
    for (int i = 0; i < n; i++)
    {
        free(data[i]);
    }

    free(data);
}

matrix_t *create_matrix(unsigned int n)
{
    matrix_t *res = malloc(sizeof(matrix_t));
    res->data = allocate_matrix_rows(n);
    res->cost = allocate_matrix_rows(n);
    res->size = n;
    return res;
}

int **allocate_matrix_rows(size_t n)
{
    int **data = calloc(n, sizeof(int*));

    for (int i = 0; i < n; i++)
    {
        data[i] = calloc(n, sizeof(int));
    }

    return data;
}

int deiksrt(const matrix_t *matrix, int ifrom, int ito, int ver[], int *k)
{
    int minindex = 0;
    int min = 0;
    int buff = 0;
    int d[matrix->size];
    int v[matrix->size];
    for (int i = 0; i< matrix->size; i++)
    {
        d[i] = INF;
        v[i] = 1;
    }
    d[ifrom] = 0;
    // Шаг алгоритма
    do {
        minindex = INF;
        min = INF;
        for (int i = 0; i < matrix->size; i++)
        {
            if ((v[i] == 1) && (d[i]<min))
            {
                min = d[i];
                minindex = i;
            }
        }
        if (minindex != INF)
        {
            for (int i = 0; i<matrix->size; i++)
            {
                if (matrix->data[minindex][i] > 0)
                {
                    buff = min + matrix->data[minindex][i] + matrix->cost[minindex][i];
                    if (buff < d[i])
                    {
                        d[i] = buff;
                    }
                }
            }
            v[minindex] = 0;
        }
    } while (minindex < INF);
    
    int end = ito; // индекс конечной вершины = 5 - 1
    ver[0] = end; // начальный элемент - конечная вершина
    *k = 0; // индекс предыдущей вершины
    int weight = d[end]; // вес конечной вершины
    int noway = 0;
    while (end != ifrom) // пока не дошли до начальной вершины
    {
        for (int i = 0; i<matrix->size; i++) // просматриваем все вершины
            if (matrix->data[i][end] != 0)   // если связь есть
            {
                int temp = weight - matrix->data[i][end] - matrix->cost[i][end]; // определяем вес пути из предыдущей вершины
                if (temp == d[i]) // если вес совпал с рассчитанным
                {                 // значит из этой вершины и был переход
                    weight = temp; // сохраняем новый вес
                    end = i;       // сохраняем предыдущую вершину
                    ver[*k] = i; // и записываем ее в массив
                    (*k)++;
                }
              }
        noway++;
        if (noway > matrix->size * 3)
        {
            printf("\nNo way!\n\n");
            return -1;
        }
    }

    printf("\nThe shortest way: ");
    int f_dis = 0;
    int f_cos = 0;
    for (int i = *k - 1; i >= 0; i--)
    {
        printf("%d -> ", ver[i]);
        if (i != 0)
        {
            f_dis += matrix->data[ver[i]][ver[i - 1]];
            f_cos += matrix->cost[ver[i]][ver[i - 1]];
        }
    }
    printf("%d\n", ito);
    f_dis += matrix->data[ver[0]][ito];
    f_cos += matrix->cost[ver[0]][ito];
    
    printf("Full distance: %d\n", f_dis);
    printf("Full cost: %d\n", f_cos);
    printf("\n");
    return 0;
}
