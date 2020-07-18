/*
 * =============================================================================
 *
 *       Filename:  aikruskal.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2020年07月18日 13时16分12秒
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
#include <string.h>

#define AI_MAXVEX   20
#define AI_MAXEGDE  20
#define AI_INFINITY 65536

typedef struct {
    int arc[AI_MAXVEX][AI_MAXVEX];
    int num_vertexes;
    int num_edges;
} ai_mgraph_t;

typedef struct {
    int begin;
    int end;
    int weight;
} ai_edge_t;

static void create_mgraph(ai_mgraph_t *g)
{
    int i, j;

    g->num_edges = 15;
    g->num_vertexes = 9;

    for (i = 0; i < g->num_vertexes; i++) {
        for (j = i; j < g->num_vertexes; j++) {
            if (i == j)
                g->arc[i][j] = 0;
            else
                g->arc[i][j] = g->arc[j][i] = AI_INFINITY;
        }
    }
    g->arc[0][1] = 10;
    g->arc[0][5] = 11; 
    g->arc[1][2] = 18; 
    g->arc[1][8] = 12; 
    g->arc[1][6] = 16; 
    g->arc[2][8] = 8; 
    g->arc[2][3] = 22; 
    g->arc[3][8] = 21; 
    g->arc[3][6] = 24; 
    g->arc[3][7] = 16;
    g->arc[3][4] = 20;
    g->arc[4][7] = 7; 
    g->arc[4][5] = 26; 
    g->arc[5][6] = 17; 
    g->arc[6][7] = 19;

    for (i = 0; i < g->num_vertexes; i++) {
        for (j = i; j < g->num_vertexes; j++) {
            g->arc[j][i] = g->arc[i][j];
        }
    }
}

static void print_mgraph(ai_mgraph_t g)
{
    int i, j;

    printf("\nmgraph:\n");
    for (i = 0; i < g.num_vertexes; i++) {
        printf("\t");
        for (j = 0; j < g.num_vertexes; j++)
            printf("%5d  ", g.arc[i][j]);
        printf("\n");
    }
    printf("\n");
}

static void get_edges_array(ai_mgraph_t g, ai_edge_t *edges)
{
    int i, j;
    int k = 0;

    for (i = 0; i < g.num_vertexes - 1; i++)
        for (j = i + 1; j < g.num_vertexes; j++)
            if (g.arc[i][j] < AI_INFINITY) {
                edges[k].begin = i;
                edges[k].end = j;
                edges[k].weight = g.arc[i][j];
                k++;
            }
}

static void print_edges_array(ai_edge_t *edges, int n)
{
    int i;

    printf("edges: \n");
    for (i = 0; i < n; i++)
        printf("\tedges[%2d] %5d %5d %5d\n", i,
                edges[i].begin, edges[i].end, edges[i].weight);
}

static void sort_edges_array(ai_edge_t *edges, int n)
{
    int i, j;
    ai_edge_t temp;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++)
            if (edges[j].weight > edges[j + 1].weight) {
                memcpy(&temp, &edges[j], sizeof(temp));
                memcpy(&edges[j], &edges[j + 1], sizeof(edges[j]));
                memcpy(&edges[j + 1], &temp, sizeof(edges[j + 1]));
            }
    }
}

static int find_tail_idx(int *parent, int f)
{
    while (parent[f] > 0)
        f = parent[f];

    return f;
}

void ai_mini_span_tree_kruskal(ai_mgraph_t g)
{
    int i, m = 0, n = 0;
    ai_edge_t edges[AI_MAXEGDE];  // 边集数组
    /*
     * 用来判断边与边之间是否形成环路;每个索引是一个点的下标，对应存储的是按顺序
     * 找到的最小生成树上的点，因为多个边会共用一个点，所以不能用一个元素代表一条
     * 边，但是重点在存储节点，不在边，这样可以将点按顺序串起来，如果查找的边关联
     * 的点已经有了，肯定会形成环，那就丢掉.
     * 即T={V, {}}
     */
    int parent[AI_MAXVEX] = {0};

    // 由图获取边集数组并排序
    get_edges_array(g, edges);
    print_edges_array(edges, g.num_edges);
    sort_edges_array(edges, g.num_edges);
    print_edges_array(edges, g.num_edges);

    printf("最小生成树为：\n");
    for (i = 0; i < g.num_edges; i++) {
        m = find_tail_idx(parent, edges[i].begin);
        n = find_tail_idx(parent, edges[i].end);
        if (m != n) {
            parent[m] = n;
            printf("\t(%d, %d) %2d\n", 
                    edges[i].begin, edges[i].end, edges[i].weight);
        }
    }
    printf("\n");
}


/************************************ main ************************************/
int main()
{
    ai_mgraph_t graph;

    create_mgraph(&graph);
    print_mgraph(graph);
    ai_mini_span_tree_kruskal(graph);

    return EXIT_SUCCESS;
}
