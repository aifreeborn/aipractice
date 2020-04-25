/*
 * =============================================================================
 *
 *       Filename:  ai_seq_tree.c
 *
 *    Description:  二叉树的顺序存储结构  
 *
 *        Version:  1.0
 *        Created:  04/25/2020 05:25:43 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  takeno (takeno2020), takeno2020@163.com
 *   Organization:  
 *
 * =============================================================================
 */
#include <stdio.h>
#include <stdlib.h>


#define MAX_TREE_SIZE 100


typedef char elem_t;
typedef elem_t seq_bitree_t[MAX_TREE_SIZE]; //seq_bitree[0]存放根节点
typedef struct {
    int level, order; // level:结点的层，order:本层的序号(按照满二叉树计算)
} position_t;


static elem_t Nil = '#';  // 整数为0表示空


void seq_bitree_print(seq_bitree_t t, int cnt)
{
    int i;

    printf("bitree: ");
    for (i = 0; i < cnt; i++)
        printf("%c ", t[i]);
    printf("\n");
}

int seq_bitree_init(seq_bitree_t t)
{
    int i;

    for (i = 0; i < MAX_TREE_SIZE; i++)
        t[i] = Nil;
    return 0;
}

int seq_bitree_create(seq_bitree_t t)
{
    int i = 0, cnt = 0;
    char ch = '#';

    printf("请按层序输入结点的值(字母或者数字), #表示空结点，输入回车结束, 结点数<=%d\n",
            MAX_TREE_SIZE);
    while ('\n' != (ch = getchar())) {
        t[i] = ch;
        if (i != 0 && t[(i + 1) / 2 - 1] == Nil && t[i] != Nil) {
           printf("出现无双亲的非根结点%d\n", t[i]);
           exit(0);
        }
        i++;
    }

    cnt = i;
    while (i < MAX_TREE_SIZE) {
        t[i] = Nil;
        i++;
    }

    return cnt;
}

/************************************ main ************************************/
int main(int argc, char *argv[])
{
    seq_bitree_t t;
    int cnt = 0;

    seq_bitree_init(t);
    cnt = seq_bitree_create(t);
    seq_bitree_print(t, cnt);
    return 0;
}
