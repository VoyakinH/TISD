#ifndef ARRAY_STRUCTS_H
#define ARRAY_STRUCTS_H

typedef struct queue
{
    float* data_store;   //хранение заявок
    int front;           //индекс последнего элемента очереди
    int max_size;        //максимальный размер массива
    int num_of_elems;    //количество элементов в очереди в данный момент
    int summ_of_elems;   //общее количество элементов в очереди
} queue_t;

typedef struct alarm
{
    float time;
}alarm_t;

typedef struct automat
{
    float now;
    float work_time;
    int left1;
    float downtime;
    float work;
    int diferent_elems;
} automat;

typedef struct qnode
{
    struct qnode *next; //указатель на следующий элемент списка
    float time;         //время обработки
} node_t;

typedef struct automat_list
{
    node_t *now;
    float work_time;
    int left1;
    float downtime;
    float work;
    int diferent_elems;
} automat_list;

typedef struct queue_list
{
    struct qnode *pin;   //указатель на конец списка
    struct qnode *pout;  //указатель на начало списка
    int num_of_elems;    //количество элементов в очереди в данный момент
    int summ_of_elems;   //сумма элементов в очереди в целом
} queue_t_list;

#endif //ARRAY_STRUCTS_H
