/*
 * =============================================================================
 *
 *       Filename:  aiseququeue.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/15/2020 10:32:42 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  takeno (takeno2020), takeno2020@163.com
 *   Organization:  
 *
 * =============================================================================
 */
#include <stdio.h>
#include <string.h>


#define MAXSIZE 5


typedef int data_type_t;
typedef struct {
    data_type_t data[MAXSIZE];
    int front;
    int rear;
} seq_queue_t;


int seq_queue_init(seq_queue_t *q)
{
    memset(q->data, 0, sizeof(q->data));
    q->front = 0;
    q->rear = 0;

    return 0;
}

int seq_queue_is_empty(seq_queue_t q)
{
    if (q.front == q.rear)
        return 0;
    return -1;
}

int seq_queue_is_full(seq_queue_t q)
{
    if ((q.rear + 1) % MAXSIZE == q.front)
        return 0;
    return -1;
}

int seq_queue_enqueue(seq_queue_t *q, data_type_t data)
{
    if (0 == seq_queue_is_full(*q))
        return -1;

    q->data[q->rear] = data;
    q->rear = (q->rear + 1) % MAXSIZE;

    return 0;
}

int seq_queue_dequeue(seq_queue_t *q, data_type_t *data)
{
    if (0 == seq_queue_is_empty(*q))
        return -1;

    *data = q->data[q->front];
    q->front = (q->front + 1) % MAXSIZE;

    return 0;
}

int seq_queue_get_length(seq_queue_t q)
{
    return (q.rear - q.front + MAXSIZE) % MAXSIZE;
}

void seq_queue_print(seq_queue_t q)
{
    int i, len;

    printf("now: ");
    len = seq_queue_get_length(q);
    if (0 == len) {
        printf("empty!");
    } else {
        for (i = q.front; (i % MAXSIZE) != q.rear; i++) {
            printf("%d ", q.data[i % MAXSIZE]);
        }

    }
    printf("\n");
}


/************************************ main ************************************/
int main(int argc, char *argv[])
{
    seq_queue_t queue;
    data_type_t data;

    seq_queue_init(&queue);
    seq_queue_print(queue);

    seq_queue_enqueue(&queue, 30);
    seq_queue_enqueue(&queue, 34);
    seq_queue_enqueue(&queue, 38);
    seq_queue_enqueue(&queue, 39);
    seq_queue_print(queue);

    seq_queue_dequeue(&queue, &data);
    seq_queue_dequeue(&queue, &data);
    seq_queue_enqueue(&queue, 40);
    printf("data = %d\n", data);
    seq_queue_print(queue);
    return 0;
}
