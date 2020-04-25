/*
 * =============================================================================
 *
 *       Filename:  ai_share_stack.c
 *
 *    Description:  数据类型相同的栈以共享栈空间的方式实现
 *
 *        Version:  1.0
 *        Created:  04/11/2020 03:22:08 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  takeno (takeno2020), takeno2020@163.com
 *   Organization:  
 *
 * =============================================================================
 */
#include "stdio.h"
#include "string.h"


#define MAXSIZE 20

typedef int data_type_t;
typedef struct {
    data_type_t data[MAXSIZE];
    int top1;
    int top2;
}share_stack_t;

int share_stack_init(share_stack_t *s)
{
    memset((void *)s->data, 0, sizeof(s->data));
    s->top1 = -1;
    s->top2 = MAXSIZE;

    return 0;
}

int share_stack_is_empty(share_stack_t s)
{
    if (s.top1 == -1 && s.top2 == MAXSIZE)
        return 0;
    return -1;
}

int share_stack_is_full(share_stack_t s)
{
    if (s.top1 + 1 == s.top2)
        return 0;

    return -1;
}

int share_stack_push(share_stack_t *s, int stack_num, data_type_t data)
{
    if (0 == share_stack_is_full(*s))
        return -1;
    if (1 == stack_num && s->top1 < MAXSIZE - 1)
        s->data[++s->top1] = data;
    else if(2 == stack_num && s->top2 > 0)
        s->data[--s->top2] = data;
    else
        return -1;
    return 0;
}

int share_stack_pop(share_stack_t *s, int stack_num, data_type_t *data)
{
    if (1 == stack_num) {
        if (s->top1 == -1)
            return -1;
        *data = s->data[s->top1--];
    } else if (2 == stack_num){
        if (s->top2 == MAXSIZE)
            return -1;
        *data = s->data[s->top2++];
    } else {
        return -1;
    }

    return 0;
}

void share_stack_print(share_stack_t *s)
{
    int i;

    printf("stack1: ");
    for (i = 0; i <= (s->top1); i++) {
        printf("%d ", s->data[i]);
    }
    printf("\n");

    printf("stack2: ");
    for (i = MAXSIZE - 1; i >= (s->top2); i--) {
        printf("%d ", s->data[i]);
    }
    printf("\n");
}

/************************************ main ************************************/
int main(int argc, char *argv[])
{
    share_stack_t stack;
    data_type_t data = 999;

    share_stack_init(&stack);
    share_stack_print(&stack);

    share_stack_push(&stack, 1, 23);
    share_stack_push(&stack, 1, 24);
    share_stack_push(&stack, 1, 25);
    share_stack_push(&stack, 1, 26);

    share_stack_push(&stack, 2, 31);
    share_stack_push(&stack, 2, 32);
    share_stack_push(&stack, 2, 33);
    share_stack_push(&stack, 2, 34);
    share_stack_print(&stack);

    share_stack_pop(&stack, 1, &data);
    printf("pop1: %d\n", data);
    share_stack_pop(&stack, 2, &data);
    printf("pop2: %d\n", data);

    return 0;
}
