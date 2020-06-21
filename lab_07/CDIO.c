#include <stdio.h>
#include "func.h"
#include "defines.h"

unsigned long long int tick(void)
{
    unsigned long long int time = 0;
    __asm__ __volatile__ ("rdtsc" : "=A" (time));
    return time;
}

int scan_choise()
{
    int rc, num;
    char tmp;
    while(((rc = scanf("%d%c", &num, &tmp)) != 2 && rc != EOF) || tmp != '\n')
    {
        do
        {
            rc = scanf("%c", &tmp);
        }
        while(rc != EOF && tmp != '\n');
    }
    return num;
}

void output_graph_to_png(const matrix_t *a)
{
    if (a == NULL)
    {
        return;
    }
    FILE *f = fopen("output.gv", "w");
    fprintf(f, "digraph My_graph {\n");
    for (int i = 0; i < a->size; i++)
    {
        for (int j = 0; j < a->size; j++)
        {
            if (a->data[i][j] < INF && a->data[i][j] != 0)
                fprintf(f, "%d -> %d [label=\"%d (%d)\"];\n", i, j, a->data[i][j], a->cost[i][j]);
        }
    }
    fprintf(f, "}\n");
    fclose(f);
    system("dot -Tpng ./output.gv -oINIT_GRAPH.png");
    system("open INIT_GRAPH.png");
}

void output_got_to_png(const matrix_t *a, int mat[], int k_mat, int ito)
{
    int is_green = 0;
    if (a == NULL)
    {
        return;
    }
    FILE *f = fopen("output_2.gv", "w");
    fprintf(f, "digraph My_graph {\n");
    for (int i = 0; i < a->size; i++)
    {
        for (int j = 0; j < a->size; j++)
        {
            if (a->data[i][j] < INF && a->data[i][j] != 0)
            {
                is_green = 0;
                for (int l = k_mat - 1; l >= 0; l--)
                {
                    if (mat[l] == i && mat[l - 1] == j)
                        is_green = 1;
                    if (l == 0 && mat[0] == i && ito == j)
                        is_green = 1;
                }
                if (is_green == 0)
                    fprintf(f, "%d -> %d [label=\"%d (%d)\"];\n", i, j, a->data[i][j], a->cost[i][j]);
                else
                    fprintf(f, "%d -> %d [label=\"%d (%d)\", color=green];\n", i, j, a->data[i][j], a->cost[i][j]);
            }
        }
    }
    fprintf(f, "}\n");
    fclose(f);
    system("dot -Tpng ./output_2.gv -oINIT_GRAPH.png");
    system("open INIT_GRAPH.png");
}
