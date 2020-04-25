/*
 * =============================================================================
 *
 *       Filename:  ai_stack.c
 *
 *    Description: Full stack的顺序存储方式实现
 *
 *        Version:  1.0
 *        Created:  04/06/2020 09:07:08 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  takeno (takeno2020), takeno2020@163.com
 *   Organization:  
 *
 * =============================================================================
 */
#include "stdio.h"


#define MAXSIZE 10


typedef int data_type_t;
typedef struct {
    data_type_t data[MAXSIZE];
    int top;                 // 指向栈顶，top = -1
}seq_stack_t;


// Full stack
int seq_stack_init(seq_stack_t *s)
{
    s->top = -1;

    return 0;
}

static int seq_stack_is_full(seq_stack_t s)
{
   if (s.top == (MAXSIZE - 1))
       return 0;
   return -1;
}

static int seq_stack_is_empty(seq_stack_t s)
{
    if (s.top == -1)
        return 0;
    return -1;
}

int seq_stack_push(seq_stack_t *s, data_type_t data)
{
    if (0 == seq_stack_is_full(*s))
        return -1;

    s->top++;
    s->data[s->top] = data;

    return 0;
}

int seq_stack_pop(seq_stack_t *s, data_type_t *data)
{
    if (0 == seq_stack_is_empty(*s))
        return -1;
    *data = s->data[s->top];
    s->top--;
    return 0;
}

int seq_stack_get_length(seq_stack_t s)
{
    return s.top + 1;
}

void seq_stack_printf(seq_stack_t s)
{
    int i, len;

    len = seq_stack_get_length(s);
    printf("stack:");
    for (i = 0; i < len; i++) {
        printf("%d ", s.data[i]);
    }
    printf("\n");
}


/************************************ main ************************************/
int main(int argc, char *argv[])
{
    seq_stack_t s;
    data_type_t data;

    seq_stack_init(&s);

    seq_stack_push(&s, 2);
    seq_stack_push(&s, 53);
    seq_stack_push(&s, 34);
    seq_stack_push(&s, 93);
    seq_stack_printf(s);

    seq_stack_pop(&s, &data);
    printf("pop: %d\n", data);
    seq_stack_printf(s);
    return 0;
}
