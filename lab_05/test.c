#include "init_automat.h"
#include "queue.h"
#include "time.h"
#include "structs.h"

int main()
{
    automat* a;
    a = init_auto();
    queue_t *q1 = new_queue(5, T1);

    srand(time(NULL));
    /*Enqueue(q1, 2.3, T1);
    Enqueue(q1, 5.5, T1);
    Enqueue(q1, 7.8, T1);
    add_elem(q1, 4.2, T1);*/

    queue_t *q2 = new_queue(5, T2);
    add_elem(q2, 4.2, T2);
    /*Enqueue(q2, 5.3, T2);
    Enqueue(q2, 8.9, T2);
    add_elem(q2, 7.1, T2);*/

    refresh_automat(q1, q2, a);

    //get_time(q1, q2, a);

    return 0;
}

