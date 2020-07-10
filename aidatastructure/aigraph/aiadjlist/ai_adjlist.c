/*
 * =============================================================================
 *
 *       Filename:  ai_adjlist.c
 *
 *    Description: 无向图的邻接表的创建 
 *
 *        Version:  1.0
 *        Created:  2020年07月10日 06时17分35秒
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

#define MAX_VERTEXES 20
#define INIFINITY 65535

typedef char vertex_t;
typedef int edge_t;

typedef struct edge_node {
    int adjvex;     // 邻接顶点域，用于存储邻接顶点的下标
    edge_t weight;
    struct edge_node *next;
} edge_node_t;

typedef struct vertex_node {
    vertex_t data;
    edge_node_t *first_edge;
} vertex_node_t;

typedef struct {
    vertex_node_t adjlist[MAX_VERTEXES];
    int num_vertexes;
    int num_edges;
} graph_adjlist_t;

void  ai_adjlist_create(graph_adjlist_t *g)
{
    int i, m, n, w;
    edge_node_t *edge;

    printf("请输入顶点数和边数，格式为: 顶点数,边数\n");
    scanf("%d, %d", &g->num_vertexes, &g->num_edges);
    getchar();

    printf("请输入顶点数据[连续输入单个字符]:\n");
    for (i = 0; i < g->num_vertexes; i++) {
        scanf("%c", &g->adjlist[i].data);
        g->adjlist[i].first_edge = NULL;
    }
    getchar();

    printf("请输入边(Vm,Vn)上的顶点序号和权值，格式为连续的(m, n, weight):\n");
    for (i = 0; i < g->num_edges; i++) {
        scanf("(%d, %d, %d)", &m, &n, &w);
        edge = (edge_node_t *)malloc(sizeof(edge_node_t));
        edge->adjvex = n;
        edge->weight = w;
        edge->next = g->adjlist[m].first_edge;
        g->adjlist[m].first_edge = edge;

        edge = NULL;
        edge = (edge_node_t *)malloc(sizeof(edge_node_t));
        edge->adjvex = m;
        edge->weight = w;
        edge->next = g->adjlist[n].first_edge;
        g->adjlist[n].first_edge = edge;
    }
}

void ai_adjlist_print(graph_adjlist_t g)
{
    int i;
    edge_node_t *temp = NULL;

    printf("\n\n########## graph ##########\n");
    for (i = 0; i < g.num_vertexes; i++) {
        printf("%c ", g.adjlist[i].data);
    }
    printf("\n");

    for (i = 0; i < g.num_vertexes; i++) {
        printf("V%d: ", i);
        temp = g.adjlist[i].first_edge;
        while (temp != NULL) {
            printf("%d<%d> ", temp->adjvex, temp->weight);
            temp = temp->next;
        }
        printf("\n");
    }
    printf("###########################\n");
}

/************************************ main ************************************/
int main(int argc, char *argv[])
{
    graph_adjlist_t g;
    ai_adjlist_create(&g);
    ai_adjlist_print(g);

    return EXIT_SUCCESS;
}
