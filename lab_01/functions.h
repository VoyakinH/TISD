#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

int float_input(FILE *f_in, char *str_fl, int *len_fl, int *minus, int *order);
int int_input(FILE *f_in, char *str_int, int *len_int, int *minus);
//void init_array(char *arr, int n);
//void round_answer(char *str, int *first_sym, int *zeros, int *order);
//int generate_answer(char *str_ans, char *str_prev, int order,
                    //int minus, int *n, int first_sym, int zeros);
//int multiplication (char *str_fl, char *str_int, int len_fl, int len_int,
                    //char *str_ans, int *order, int minus, int *n);
void ans_out(FILE *f_out, char *str_answer, int n);
void ans_text(void);
int get_ans(char *str_fl, char *str_int, int len_fl, int len_int,
            char *str_ans, int *order, int minus, int *n);

#endif
