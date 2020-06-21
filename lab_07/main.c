#include <stdio.h>
#include "defines.h"
#include "func.h"

int main(void)
{
    int ifrom, ito;
    FILE *f = fopen(FILENAME, "r");
    if (!f)
    {
        printf("File not found!\n");
        return 0;
    }
    unsigned long long t1, t2;

    int menu = 0, flag = 1;
    int k_mat = 0;

    matrix_t *graph = read_matrix(f);
    if (graph == NULL)
    {
        return 0;
    }

    int ver[graph->size];

    while (flag)
    {
        printf(" ⟰  MENU: \n");
        printf(" ①  Build graph from file\n");
        printf(" ②  Show search performance\n");
        printf(" ③  Show matrix from file\n");
        printf(" ④  Show shortest way S+P\n");
        //printf(" ⑤  Build graph with shortest way S+P\n");
        printf(" ⓪  EXIT\n");
        printf(" ⟱  Choose menu item: ");

        menu = scan_choise();
        switch (menu)
        {
            case 1:
                output_graph_to_png(graph);
                break;
            case 2:
                t1 = tick();
                deiksrt(graph, 0, graph->size - 1, ver, &k_mat);
                t2 = tick();
                printf("Spend time: %d clocks\n", (int) (t2 - t1));
                printf("Necessary memory: %lu bytes\n\n", sizeof(int) * graph->size * graph->size * 2 + sizeof(unsigned int));
                break;
            case 3:
                print_matrix(stdout, graph);
                break;
            case 4:
                printf("Input begin and end points via space: ");
                scanf("%d%d", &ifrom, &ito);
                if (ifrom < 0 || ito < 0 || ifrom > graph->size - 1 || ito > graph->size - 1)
                {
                    printf("Incorrect input.\n");
                    free_matrix(graph);
                    return 0;
                }
                if (deiksrt(graph, ifrom, ito, ver, &k_mat) == 0)
                    output_got_to_png(graph, ver, k_mat, ito);
                break;
            case 0:
                flag = 0;
                break;
            default:
                printf("\nSuch item not founded in menu!\n\n");
                break;
        }
    }

    free_matrix(graph);
    //free_matrix(best);
    fclose(f);
    return 0;
}
