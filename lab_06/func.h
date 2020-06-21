#ifndef FUNC_H
#define FUNC_H

#include "defines.h"

//tree.c
typedef struct tnode
{
    int value;
    int balance;
    struct tnode *left;
    struct tnode *right;
}t_node;

t_node *create_node(int val);
void freemem(t_node *tree);
void count_node(t_node *tree, int *sum);
t_node *ord_add_node(t_node *tree, t_node *node);

//hash.c
typedef struct node_table
{
    int value;
    struct node_table *next;
}t_hash;

int len_list(t_hash *head);
int next_prime_number(int number);
t_hash* add_end(t_hash *head, t_hash *elem);
t_hash* create_hash_node(int val);
int what_index(int val, int len_table, int k);
t_hash **insert_in_hash_table(t_hash **table, int *len_table, t_hash *node, int max_len, int *k);
void print_table(FILE *f, t_hash **table, int len_table, int is_search, int search_val);
int count_node_table(t_hash **table, int len_table);
t_hash **create_table(FILE *f, int *len_table, int *k, int max_len);
int check_int(int *number, int min, int max);

//search.c
t_node * search_in_tree(t_node *tree, int val, int *amount, int *flag);
t_hash *looking_in_list(t_hash *head, int searh_int, int *amount);
int search_in_hash(t_hash **table, int searh_int, int table_len, int *amount, int k);
int search_in_file(FILE *f, int val, int *amount_file);

//read_file.h
t_node *read_file(FILE *f, t_node *root);

//export.c
void export_to_dot(FILE *f, const char *tree_name, t_node *tree, int is_search, int search_val);
void apply_pre(t_node *tree, FILE *f, int is_search, int search_val);
void to_dot(t_node *tree, FILE *f, int is_search, int search_val);

//efficiency.c
void efficiency(void);

//balance.c
t_node* rotateleft(t_node* q);
t_node* rotateright(t_node* p);
void fixheight(t_node* p);
t_node* bal_add_node(t_node *root, t_node *node);
t_node* balance(t_node* p);
t_node* read_file_balanced(t_node *root, FILE *f);
int height(t_node* p);
int bfactor(t_node* p);

#endif //FUNC_H
