/*
 * =============================================================================
 *
 *       Filename:  ai_link_tree.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/28/2020 10:00:42 PM
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


typedef char data_t;
typedef struct node {
    data_t data;
    struct node *lchild;
    struct node *rchild;
} link_bitree_t;


link_bitree_t* link_bitree_create()
{
    data_t ch;

    link_bitree_t *bitree = (link_bitree_t *)malloc(sizeof(link_bitree_t));
    if (bitree == NULL)
        return NULL;

    scanf("%c", &ch);
    if (ch == '#')
        return NULL;
    bitree->data = ch;
    bitree->lchild = link_bitree_create();
    bitree->rchild = link_bitree_create();

    return bitree;
}

int link_bitree_get_depth(link_bitree_t *t)
{
    int i = 0, j = 0;

    if (t == NULL)
        return 0;
    if (t->lchild == NULL)
        i = 0;
    else
        i = link_bitree_get_depth(t->lchild);
    if (t->rchild == NULL)
        j = 0;
    else
        j = link_bitree_get_depth(t->rchild);

    return i > j ? ++i : ++j; 
}

void link_bitree_pre_traverse(link_bitree_t *t)
{
    if (t == NULL)
        return;
    printf("%c", t->data);
    link_bitree_pre_traverse(t->lchild);
    link_bitree_pre_traverse(t->rchild);
}

void link_bitree_mid_traverse(link_bitree_t *t)
{
    if (t == NULL)
        return;

    link_bitree_pre_traverse(t->lchild);
    printf("%c", t->data);
    link_bitree_pre_traverse(t->rchild);
}


void link_bitree_post_traverse(link_bitree_t *t)
{
    if (t == NULL)
        return;

    link_bitree_post_traverse(t->lchild);
    link_bitree_post_traverse(t->rchild);
    printf("%c", t->data);
}

void link_bitree_destroy(link_bitree_t **t)
{
    if ((*t) == NULL)
        return;
    link_bitree_destroy(&(*t)->lchild);
    link_bitree_destroy(&(*t)->rchild);
    free((*t));
    *t=NULL;
}
/************************************ main ************************************/
/* 
 *                  A
 *                /   \
 *               B     C
 *                \
 *                 D
 *                / \
 *               E   F
 *                    \
 *                     G
 *         AB#DE##F#G##C##
 *
 */
int main(int argc, char *argv[])
{
    link_bitree_t *bitree = NULL;

    bitree = link_bitree_create();
    if (bitree == NULL) {
        printf("link_bitree_create failed!\n");
        return 0;
    }

    printf("二叉树的深度为：%d\n", link_bitree_get_depth(bitree));
    printf("\n前序遍历结果为:");
    link_bitree_pre_traverse(bitree);
    printf("\n中序遍历结果为:");
    link_bitree_mid_traverse(bitree);
    printf("\n后序遍历结果为:");
    link_bitree_post_traverse(bitree);
    printf("\n");

    link_bitree_destroy(&bitree);
    printf("\n清除二叉树后,树空否？%d(1:是 0:否) 树的深度=%d\n", 
                    bitree == NULL ? 1 : 0, link_bitree_get_depth(bitree));
    return 0;
}

