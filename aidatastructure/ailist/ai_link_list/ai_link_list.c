/*
 * =============================================================================
 *
 *       Filename:  ai_link_list.c
 *
 *    Description:  线性表的链式存储结构：注意传值和传址区别
 *
 *        Version:  1.0
 *        Created:  04/04/2020 08:47:29 AM
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


#define AI_OK       1
#define AI_ERROR    0
#define AI_TRUE     1
#define AI_FALSE    0


typedef int status_t;
typedef int data_type_t;
typedef struct node
{
    data_type_t data;
    struct node *next;
}link_list_node_t, *link_list_head_t;


/*
 * 不能使用下面的定义形式, 因为是"传值"调用，传的指针的值，所以init中改变了
 * head的值，不再指向list
 * struct node list;
 * main: link_list_init(&list);
 * status_t link_list_init(link_list_head_t *head)
 * {
 *     head = (link_list_node_t *)malloc(sizeof(link_list_node_t));
 *     return AI_OK
 * }
 *
 * */
status_t link_list_init(link_list_head_t *head)
{
    *head = (link_list_node_t *)malloc(sizeof(link_list_node_t));
    if (head  == NULL)
        return AI_ERROR;

    (*head)->data = -1;
    (*head)->next = NULL;
    return AI_OK;
}

/* 在第n个位置之前插入新的数据元素data */
status_t link_list_insert_elem(link_list_head_t *head, int n, data_type_t data)
{
    int i;
    link_list_node_t *node, *tmp;

    tmp = *head;
    for (i = 1; tmp && i < n; i++) {
        tmp = tmp->next;
    }
    if (!tmp)
        return AI_ERROR;

    node = (link_list_node_t *)malloc(sizeof(link_list_node_t));
    if (node == NULL)
        return AI_ERROR;
    node->data = data;
    node->next = tmp->next;
    tmp->next = node;

    return AI_OK;
}

status_t link_list_is_empty(link_list_head_t head)
{
    if (head->next == NULL)
        return AI_TRUE;
    else
        return AI_FALSE;
}

status_t link_list_del_elem(link_list_head_t *head, int n, data_type_t *data)
{
    int i;
    link_list_node_t *tmp, *node;

    if (link_list_is_empty(*head) == AI_TRUE)
        return AI_ERROR;

    tmp = *head;
    // 一直找到要插入的位置的前一个位置停止，tmp指向要插入位置的前一个位置,
    // 不然的话还得重新找上一个位子
    for (i = 1; tmp->next && i < n; i++) {
        tmp = tmp->next;
    }
    if (!tmp->next)
        return AI_ERROR;

    node = tmp->next;
    tmp->next = node->next;
    *data = node->data;
    free(node);

    return AI_OK;
}

status_t link_list_clear(link_list_head_t *head)
{
    link_list_node_t *tmp, *tmp1;

    tmp = (*head)->next;
    while (tmp != NULL) {
        tmp1 = tmp->next;
        free(tmp);
        tmp = NULL;
        tmp = tmp1;
    }
    (*head)->next = NULL;
    return AI_OK;
}

int link_list_get_length(link_list_head_t head)
{
    int i = 0;
    link_list_node_t *tmp;

    tmp = head->next;
    while (tmp) {
        i++;
        tmp = tmp->next;
    }
    return i;
}

// 返回第n个位置的数据元素的值
status_t link_list_get_elem(link_list_head_t head, int n, data_type_t *data)
{
    int i;
    link_list_node_t *tmp = head->next;

    for (i = 1; i < n; i++) {
        tmp = tmp->next;
    }
    *data = tmp->data;

    return AI_OK;
}

// 头插法创建线性列表
status_t link_list_create(link_list_head_t *head, int n)
{
    int i;
    link_list_node_t *tmp;

    srand(time(NULL));
    *head = (link_list_node_t *)malloc(sizeof(link_list_node_t));
    if (*head == NULL)
        return AI_ERROR;
    (*head)->data = 999; // 为了验证传参是否成功，没有数据意义
    (*head)->next = NULL;
    for (i = 0; i < n; i++) {
        tmp = (link_list_node_t *)malloc(sizeof(link_list_node_t));
        if (tmp == NULL)
            return AI_ERROR;
        tmp->data = rand() % 100 + 1;
        tmp->next = (*head)->next;
        (*head)->next = tmp;
    }
    return AI_OK;
}

status_t link_list_insert_tail(link_list_head_t *head, data_type_t data)
{
    link_list_node_t *node, *tmp;
    
    tmp = *head;
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }

    node = (link_list_node_t *)malloc(sizeof(link_list_node_t));
    if (node == NULL)
        return AI_FALSE;
    node->data = data;
    node->next = NULL;
    tmp->next = node;

    return AI_OK;
}

void link_list_print(const char *preface, link_list_head_t head)
{
    link_list_node_t *tmp;

    printf("%s", preface);
    if (link_list_is_empty(head) == AI_TRUE) {
        printf("empty!\n");
    } else {
        tmp = head->next;
        while (tmp != NULL) {
            printf("%d ", tmp->data);
            tmp = tmp->next;
        }
        printf("\n");
    }
}


/************************************ main ************************************/
int main(int argc, char *argv[])
{
    link_list_head_t list_head;
    link_list_head_t list_head2;
    data_type_t data;

    link_list_init(&list_head);
    printf("init head1 data: %d\n", list_head->data);
    link_list_print("list_head: ", list_head);
    link_list_insert_elem(&list_head, 1, 23);
    link_list_print("insert 23 into position 1: ", list_head);

    // 验证传参是否有效
    printf("\n");
    link_list_create(&list_head2, 10);
    printf("head data: %d\n", list_head2->data);
    link_list_print("init list: ", list_head2);
    printf("list_head2 length: %d\n", link_list_get_length(list_head2));

    link_list_insert_elem(&list_head2, 3, 2014);
    link_list_print("insert 2014 into position 3: ", list_head2);
    printf("list_head2 length: %d\n", link_list_get_length(list_head2));
    link_list_del_elem(&list_head2, 10, &data);
    printf("Deleted: %d\n", data);
    link_list_print("delete position 10: ", list_head2);
    printf("list_head2 length: %d\n", link_list_get_length(list_head2));

    link_list_get_elem(list_head2, 5, &data);
    printf("list_head2 pos 5: %d\n", data);

    link_list_insert_tail(&list_head2, 2020);
    link_list_insert_tail(&list_head2, 2021);
    link_list_insert_tail(&list_head2, 2022);
    link_list_print("after insert: ", list_head2);

    link_list_clear(&list_head2);
    link_list_print("cleared: ", list_head2);
    printf("list_head2 length: %d\n", link_list_get_length(list_head2));
    return 0;
}
