/*
 * =============================================================================
 *
 *       Filename:  ai_seq_tree.c
 *
 *    Description:  二叉树的顺序存储结构  
 *                      1.结点的编号从1开始;
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
#include <math.h>


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
           printf("出现无双亲的非根结点%c\n", t[i]);
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

#define seq_bitree_clear seq_bitree_init


int seq_bitree_is_empty(seq_bitree_t t)
{
    if (Nil == t[0])
        return 1;
    else
        return 0;
}

int seq_bitree_get_depth(seq_bitree_t t)
{
    int i, j = -1;

    for (i = MAX_TREE_SIZE - 1; i >= 0; i--) {
        if (Nil != t[i])
            break;
    }
    i++;
    do {
        j++;
    } while(i >= powl(2, j));

    return j;
}

int seq_bitree_get_root(seq_bitree_t t, elem_t *e)
{
    if (1 == seq_bitree_is_empty(t)) {
        return -1;
    } else {
        *e = t[0];
        return 0;
    }
}

elem_t seq_bitree_get_value(seq_bitree_t t, position_t pos)
{
    int i = 0;

    i = (int)powl(2, pos.level - 1) -1 + pos.order;
    return t[i - 1];
}

elem_t seq_bitree_get_parent(seq_bitree_t t, elem_t e)
{
    int i;

    if (t[0] == Nil)
        return Nil;
    for (i = 1; i < MAX_TREE_SIZE; i++)
        if (t[i] == e)
            return t[(i + 1) / 2 - 1];
    return Nil;
}

elem_t seq_bitree_get_left_child(seq_bitree_t t, elem_t e)
{
    int i;

    if (t[0] == Nil)
        return Nil;
    for (i = 1; i < MAX_TREE_SIZE; i++)
        if (t[i] == e && (2 * i + 1) < MAX_TREE_SIZE)
            return t[2 * i + 1];
    return Nil;
}

elem_t seq_bitree_get_right_child(seq_bitree_t t, elem_t e)
{
    int i;

    if (t[0] == Nil)
        return Nil;
    for (i = 1; i < MAX_TREE_SIZE; i++)
        if (t[i] == e && (2 * i + 2) < MAX_TREE_SIZE)
            return t[2 * i + 2];
    return Nil;
}

elem_t seq_bitree_get_left_sibling(seq_bitree_t t, elem_t e)
{
    int i;

    if (t[0] == Nil)
        return Nil;
    for (i = 1; i < MAX_TREE_SIZE; i++)
        if (t[i] == e && i % 2 == 0)
            return t[i - 1];
    return Nil;
}

elem_t seq_bitree_get_right_sibling(seq_bitree_t t, elem_t e)
{
    int i;

    if (t[0] == Nil)
        return Nil;
    for (i = 1; i < MAX_TREE_SIZE; i++)
        if (t[i] == e && i % 2 == 1 && (i + 1) < MAX_TREE_SIZE)
            return t[i + 1];
    return Nil;
}

void seq_bitree_pre_traverse(seq_bitree_t t, int i)
{
    if (t[i] == Nil)
        return;
    printf("%c", t[i]);
    if (t[2 * i + 1] != Nil)
        seq_bitree_pre_traverse(t, 2 * i + 1);
    if (t[2 * i + 2] != Nil)
        seq_bitree_pre_traverse(t, 2 * i + 2);
}

void seq_bitree_mid_traverse(seq_bitree_t t, int i)
{
    if (t[i] == Nil)
        return;
    if (t[2 * i + 1] != Nil)
        seq_bitree_mid_traverse(t, 2 * i + 1);
    printf("%c", t[i]);
    if (t[2 * i + 2] != Nil)
        seq_bitree_mid_traverse(t, 2 * i + 2);
}

void seq_bitree_post_traverse(seq_bitree_t t, int i)
{
    if (t[i] == Nil)
        return;
    if (t[2 * i + 1] != Nil)
        seq_bitree_post_traverse(t, 2 * i + 1);
    if (t[2 * i + 2] != Nil)
        seq_bitree_post_traverse(t, 2 * i + 2);
    printf("%c", t[i]);
}

void seq_bitree_level_traverse(seq_bitree_t t)
{
    int i = MAX_TREE_SIZE - 1, j;

    while (t[i] != Nil)
        i--;
    for (j = 0; j <= i; j++) {
        if (t[j] != Nil)
            printf("%c", t[j]);
    }
}
/************************************ main ************************************/
/*   
 *  使用的树为:
 *                A
 *             /     \
 *            B       C
 *          /   \    / \
 *         #     D  E   #
 *        / \   /
 *       #   # F
 *  按层序创建bitree的输入为: ABC#DE###F
 */
int main(int argc, char *argv[])
{
    seq_bitree_t t;
    int cnt = 0;

    seq_bitree_init(t);
    cnt = seq_bitree_create(t);
    seq_bitree_print(t, cnt);
    printf("树的深度depth = %d\n", seq_bitree_get_depth(t));

    position_t pos = {
        .level = 3,
        .order = 3
    };
    printf("第3层第3个节点的值为: %c\n", seq_bitree_get_value(t, pos));
    printf("结点D的父结点值为: %c\n", seq_bitree_get_parent(t, 'D'));
    printf("结点B的左孩子为: %c\n", seq_bitree_get_left_child(t, 'B'));
    printf("结点B的右孩子为: %c\n", seq_bitree_get_right_child(t, 'B'));
    printf("结点C的左兄弟为: %c\n", seq_bitree_get_left_sibling(t, 'C'));
    printf("结点B的右兄弟为: %c\n", seq_bitree_get_right_sibling(t, 'B'));

    printf("前序遍历:");
    seq_bitree_pre_traverse(t, 0);
    printf("\n");
    printf("中序遍历:");
    seq_bitree_mid_traverse(t, 0);
    printf("\n");
    printf("后序遍历:");
    seq_bitree_post_traverse(t, 0);
    printf("\n");
    printf("层序遍历:");
    seq_bitree_level_traverse(t);
    printf("\n");
    
    return 0;
}
