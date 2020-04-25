/*
 * =============================================================================
 *
 *       Filename:  ai_link_stack.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/11/2020 05:01:58 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  takeno (takeno2020), takeno2020@163.com
 *   Organization:  
 *
 * =============================================================================
 */
#include "stdio.h"
#include "stdlib.h"
#include "time.h"


typedef int data_type_t;
typedef struct node{
    data_type_t data;
    struct node *next;
} link_stack_node_t;

typedef struct {
    link_stack_node_t *top;
    int cnt;
} link_stack_t;



int link_stack_init(link_stack_t *s)
{
    s->top = NULL;
    s->cnt = 0;

    return 0;
}

int link_stack_is_empty(link_stack_t s)
{
    if (0 == s.cnt)
        return 0;
    return -1;
}

int link_stack_push(link_stack_t *s, data_type_t data)
{
    link_stack_node_t *tmp = NULL;

    tmp = (link_stack_node_t *)malloc(sizeof(link_stack_node_t));
    if (NULL == tmp)
        return -1;
    tmp->data = data;
    tmp->next = s->top;

    s->top = tmp;
    s->cnt++;

    return 0;
}

int link_stack_pop(link_stack_t *s, data_type_t *data)
{
    link_stack_node_t *tmp = NULL;

    if (0 == link_stack_is_empty(*s))
        return -1;

    tmp = s->top;
    *data = tmp->data;
    s->top = s->top->next;
    s->cnt--;
    free(tmp);
    tmp = NULL;

    return 0;
}

void link_stack_print(link_stack_t s)
{
    int i;
    link_stack_node_t *tmp = NULL;

    tmp = s.top;
    printf("now: ");
    for (i = 0; i < s.cnt; i++) {
       printf("%d ", tmp->data); 
       tmp = tmp->next;
    }
    printf("\n");
}


/************************************ main ************************************/
int main(int argc, char *argv[])
{
    int i, j;
    link_stack_t stack;
    data_type_t data;

    srand(time(NULL));
    link_stack_init(&stack);

    link_stack_print(stack);
    printf("push data: ");
    for (i = 0; i < 5; i++) {
        j = rand() % 100 + 1;
        printf("%d ", j);
        link_stack_push(&stack, j);
    }
    printf("\n");
    link_stack_print(stack);

    printf("pop data: ");
    for (i = 0; i < 5; i++) {
        link_stack_pop(&stack, &data);
        printf("%d ", data);
    }
    printf("\n");
    link_stack_print(stack);

    return 0;
}
