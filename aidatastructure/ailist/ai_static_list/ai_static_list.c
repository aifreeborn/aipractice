/*
 * =============================================================================
 *
 *       Filename:  ai_static_list.c
 *
 *    Description:  静态链表
 *
 *        Version:  1.0
 *        Created:  04/05/2020 12:33:35 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  takeno (takeno2020), takeno2020@163.com
 *   Organization:  
 *
 * =============================================================================
 */
#include "stdio.h"

#define    AI_OK      1
#define    AI_ERROR   0
#define    AI_TRUE    1
#define    AI_FALSE   0
// 存储空间的初始分配值
#define    MAXSIZE    10


typedef int status_t;
typedef int data_type_t;
typedef struct node {
    data_type_t data;
    int cur;             // 相当于顺序表的游标，为0时表示无指向
}static_list_node_t;
// 使用位置0来表示可用空间的起始位置，使用MAXSIZE-1位置来指示链表的开始
typedef static_list_node_t static_list_t[MAXSIZE];


status_t static_list_init(static_list_t list)
{
    int i;
    for (i = 0; i < MAXSIZE - 1; i++)
        list[i].cur = i + 1;
    list[MAXSIZE - 1].cur = 0;
    return AI_OK;
}

int static_list_malloc_node(static_list_t list)
{
    int i = list[0].cur;

    if (list[0].cur)
        list[0].cur = list[i].cur;

    return i;
}

status_t static_list_free_node(static_list_t list, int n)
{
    if (n < 1 || n > MAXSIZE - 2)
        return AI_ERROR;

    list[n].data = 0;
    list[n].cur = list[0].cur;
    list[0].cur = n;

    return AI_OK;
}

int static_list_get_length(static_list_t list)
{
    int i = 0;
    int cur = list[MAXSIZE - 1].cur;

    while (cur) {
        cur = list[cur].cur;
        i++;
    }

    return i;
}

// 在第n个位置之前插入元素，包括第n+1个位置
status_t static_list_insert_elem(static_list_t list, int n, data_type_t data)
{
    int i, j, k;

    if (n < 1 || n > static_list_get_length(list) + 1)
        return AI_ERROR;

    k = MAXSIZE - 1;
    i = static_list_malloc_node(list);
    if (i) {
        list[i].data = data;
        for (j = 1; j <= n - 1; j++) {
           k = list[k].cur;  
        }
        list[i].cur = list[k].cur;
        list[k].cur = i;
        return AI_OK;
    }

    return AI_ERROR;
}

status_t static_list_del_elem(static_list_t list, int n)
{
    int i, j;

    if (n < 1 || n > static_list_get_length(list))
        return AI_ERROR;

    i = MAXSIZE - 1;
    // 取得要删除的元素n的前一个元素的位置n-1
    for (j = 1; j <= n - 1; j++) {
        i = list[i].cur;
    }
    j = list[i].cur;
    list[i].cur = list[j].cur;
    static_list_free_node(list, j);

    return AI_OK;
}

void static_list_print(const char *preface, static_list_t list)
{
    int i;

    i = list[MAXSIZE - 1].cur;
    printf("%s", preface);
    if (i == 0) {
        printf("empty!\n");
    } else {
        while (i) {
            printf("%d ", list[i].data);
            i = list[i].cur;
        }
        printf("\n");
    }
}


/************************************ main ************************************/
int main(int argc, char *argv[])
{
    static_list_t list;

    static_list_init(list);
    static_list_print("list: ", list);


    static_list_insert_elem(list, 1, 23);
    static_list_insert_elem(list, 1, 34);
    static_list_insert_elem(list, 1, 6524);
    static_list_insert_elem(list, 1, 53);
    static_list_print("list: ", list);

    static_list_del_elem(list, 3);
    static_list_print("list: ", list);

    return 0;
}

