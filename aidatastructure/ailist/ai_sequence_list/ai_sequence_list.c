/*
 * =============================================================================
 *
 *       Filename:  ai_sequence_list.c
 *
 *    Description:  线性表的顺序存储
 *
 *        Version:  1.0
 *        Created:  04/01/2020 10:02:02 PM
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
#include "stdlib.h"
#include "time.h"

#define AI_OK        1
#define AI_ERROR     0
#define AI_TRUE      1
#define AI_FALSE     0
#define MAXSIZE      20


typedef int elem_type_t;
typedef struct
{
    elem_type_t data[MAXSIZE];
    int length;
    
}seq_list_t;

// 函数的返回值类型，其值是函数结果状态码
typedef int status_t;


status_t seq_list_init(seq_list_t *head)
{
    memset(head->data, 0, sizeof(head->data));
    head->length = 0;
    return AI_OK;
}

/*
 * 在第i个位置之前插入新的数据元素
 * 元素{a1, a2, a3, ... , an}, n即为length
 *
 */
status_t seq_list_insert_elem(seq_list_t *head, int i, elem_type_t data)
{
    int k;

    if (head->length == MAXSIZE)
        return AI_ERROR;
    // 最后一个位置的后一位可以直接出入数值
    if (i < 1 || i > head->length + 1)
        return AI_ERROR;

    if (i <= head->length) {
        for (k = head->length - 1; k >= i - 1; k--)
            head->data[k + 1] = head->data[k];
    }
    head->data[i - 1] = data;
    head->length++;

    return AI_OK;
}

/*
 * 删除第i个元素，并用data返回其值
 */
status_t seq_list_delete_elem(seq_list_t *head, int i, elem_type_t *data)
{
    int k;

    if (head->length == 0)
        return AI_ERROR;
    if (i < 1 || i > head->length)
        return AI_ERROR;

    *data = head->data[i - 1];
    if (i <= head->length) {
        for (k = i; k < head->length; k++)
            head->data[k - 1] = head->data[k];
    }
    head->length--;
    return AI_OK;
}

// 查看第一个与data相等的元素的位置序号
status_t seq_list_elem_exist(seq_list_t head, elem_type_t data)
{
    int i;

    if (head.length == 0)
        return 0;

    for (i = 0; i < head.length; i++) {
        if (head.data[i] == data)
            break;
    }
    if (i >= head.length)
        return 0;

    return i + 1;
}

status_t seq_list_is_empty(seq_list_t head)
{
    if (head.length == 0)
        return AI_TRUE;
    else
        return AI_FALSE;
}

status_t seq_list_cleared(seq_list_t *head)
{
    head->length = 0;
    return AI_OK;
}

status_t seq_list_get_elem(seq_list_t head, int i, elem_type_t *val)
{
    if (head.length == 0 || i < 1 || i > head.length)
        return AI_ERROR;

    *val = head.data[i - 1];
    return AI_OK;
}

int seq_list_get_length(seq_list_t head)
{
    return head.length;
}

void seq_list_union(seq_list_t *la, seq_list_t lb)
{
    int i, la_len, lb_len;
    elem_type_t elem;

    la_len = seq_list_get_length(*la);
    lb_len = seq_list_get_length(lb);
    for (i = 1; i <= lb_len; i++) {
        seq_list_get_elem(lb, i, &elem);
        if (!seq_list_elem_exist(*la, elem))
            seq_list_insert_elem(la, ++la_len, elem);
    }
}

void seq_list_print(const char *name, seq_list_t head)
{
    int i;

    if (seq_list_is_empty(head) == AI_TRUE) {
        printf("%s is empty!\n", name);
    } else {
        printf("%s", name);
        printf("[");
        for (i = 0; i < head.length - 1; i++)
            printf("%d ", head.data[i]);
        printf("%d", head.data[head.length - 1]);
        printf("]\n");
    }
}

/*************************************** main ***************************************/
int main()
{
    int i;
    int tmp;
    elem_type_t del_data;
    seq_list_t seq1, seq2;

    seq_list_init(&seq1);
    seq_list_init(&seq2);

    for (i = 0; i < 5; i++) {
        tmp = rand() % 100;
        seq_list_insert_elem(&seq1, 1, tmp);
        tmp = rand() % 100;
        seq_list_insert_elem(&seq2, 1, tmp);
    }
    seq_list_print("init seq1", seq1);
    seq_list_print("init seq2", seq2);
    printf("seq1 length %d\n", seq_list_get_length(seq1));
    printf("seq2 length %d\n", seq_list_get_length(seq2));

    seq_list_delete_elem(&seq1, 2, &del_data);
    printf("delete seq1[1] = %d\n", del_data);
    seq_list_delete_elem(&seq2, 3, &del_data);
    printf("delete seq2[2] = %d\n", del_data);
    seq_list_print("seq1", seq1);
    seq_list_print("seq2", seq2);

    seq_list_union(&seq1, seq2);
    seq_list_print("seq1 U seq2", seq1);
    seq_list_cleared(&seq2);
    seq_list_print("seq1", seq1);
    seq_list_print("seq2", seq2);
    return 0;
}
