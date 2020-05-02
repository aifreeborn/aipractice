/*
 * =============================================================================
 *
 *       Filename:  ai_thread_tree.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/29/2020 10:52:13 PM
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

typedef enum {
    LINK = 0,
    THREAD
} pointer_tag_t;

typedef char data_t;
typedef struct node {
    data_t data;
    struct node *lchild;
    struct node *rchild;
    pointer_tag_t ltag;
    pointer_tag_t rtag;
} thread_bitree_t;

// 按照前序输入二叉树中的结点值，构造二叉树
thread_bitree_t* thread_bitree_create()
{
    data_t ch;
    thread_bitree_t *tmp = NULL;

    scanf("%c", &ch);
    if (ch == '#')
        return NULL;

    tmp = (thread_bitree_t *)malloc(sizeof(thread_bitree_t));
    if (tmp == NULL)
        return NULL;
    tmp->data = ch;
    tmp->lchild = thread_bitree_create();
    if (tmp->lchild != NULL)
        tmp->ltag = LINK;
    tmp->rchild = thread_bitree_create();
    if (tmp->rchild != NULL)
        tmp->rtag = LINK;

    return tmp;
}

thread_bitree_t *prev = NULL;
// 中序遍历进行中序线索化
void thread_bitree_inthreading(thread_bitree_t *root)
{
    if (root != NULL) {
        thread_bitree_inthreading(root->lchild);
        if (root->lchild == NULL) {
            root->ltag = THREAD;
            root->lchild = prev;
        }
        if (prev->rchild == NULL) {
            prev->rtag = THREAD;
            prev->rchild = root;
        }
        prev = root;
        thread_bitree_inthreading(root->rchild);
    }
}

// head指向头结点，root为二叉树的根
int thread_bitree_mid_threading(thread_bitree_t **head, thread_bitree_t *root)
{
    (*head) = (thread_bitree_t *)malloc(sizeof(thread_bitree_t));
    if ((*head) == NULL)
        return -1;
    (*head)->data = '#';
    (*head)->ltag = LINK;
    (*head)->rtag = THREAD;
    (*head)->rchild = (*head);
    if (root == NULL) {
        (*head)->lchild = *head;
    } else {
        (*head)->lchild = root;
        prev = (*head);
        thread_bitree_inthreading(root);
        prev->rchild = *head;
        prev->rtag = THREAD;
        (*head)->rchild = prev;
    }
    return 0;
}

int thread_bitree_mid_threading_thr(thread_bitree_t *root)
{
    thread_bitree_t *tmp;

    tmp = root->lchild;
    while (tmp != root) {
        while (tmp->ltag == LINK)
            tmp = tmp->lchild;
        printf("%c", tmp->data);
        while (tmp->rtag == THREAD && tmp->rchild != root) {
            tmp = tmp->rchild;
            printf("%c", tmp->data);
        }
        tmp = tmp->rchild;
    }

    return 0;
}


/************************************ main ************************************/
int main(int argc, char *argv[])
{
    thread_bitree_t *head = NULL, *root = NULL;

    printf("请按前序输入二叉树(如:'AB#DE##F#G##C##')\n");
    root = thread_bitree_create();
    if (root == NULL) {
        printf("thread_bitree_create failed!\n");
        return 0;
    }
    thread_bitree_mid_threading(&head, root);
    printf("中序遍历(输出)二叉线索树:\n");
    thread_bitree_mid_threading_thr(head);
    printf("\n");

    return 0;
}
