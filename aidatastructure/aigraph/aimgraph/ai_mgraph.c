/*
 * =============================================================================
 *
 *       Filename:  ai_mgraph.c
 *
 *    Description: 图的邻接矩阵创建
 *
 *        Version:  1.0
 *        Created:  2020年07月09日 22时59分52秒
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

#define MAX_VERTEX 20
// 代表无穷大的距离
#define INFINITY   65536U

typedef char vertex_t;
typedef int edge_t;
typedef struct {
    vertex_t vexs[MAX_VERTEX];
    edge_t arc[MAX_VERTEX][MAX_VERTEX];
    int num_vertexs;
    int num_edges;
} mgraph_t;

typedef enum {
    AI_TRUE,
    AI_FALSE
} boolean_t;


boolean_t visited[MAX_VERTEX];

void ai_DFS(mgraph_t g, int i)
{
    int j;
    visited[i] = AI_TRUE;
    printf("%c ", g.vexs[i]);
    for (j = 0; j < g.num_vertexs; j++) {
        if (g.arc[i][j] == 1 && AI_FALSE == visited[j])
            ai_DFS(g, j);
    }
}

void ai_DFS_travers(mgraph_t g)
{
    int i;
    for (i = 0; i < g.num_vertexs; i++)
        visited[i] = AI_FALSE;
    for (i = 0; i < g.num_vertexs; i++)
        if (AI_FALSE == visited[i])
            ai_DFS(g, i);
}

void ai_mgraph_created(mgraph_t *graph)
{
    int i, j, k;
    int n;

    printf("请输入顶点数和边数[不超过%d], 格式为(顶点数, 边数):", MAX_VERTEX);
    scanf("(%d, %d)", &graph->num_vertexs, &graph->num_edges);
    getchar();
    printf("请输入顶点值[字符]:\n");
    for (i = 0; i < graph->num_vertexs; i++) {
        scanf("%c", &graph->vexs[i]);
    }
    getchar();
    for (i = 0; i < graph->num_vertexs; i++)
        for (j = 0; j < graph->num_vertexs; j++) {
            graph->arc[i][j] = INFINITY;
        }
    for (k = 0; k < graph->num_edges; k++) {
        printf("输入边(Vi, Vj)的下标i, j和权值n, 格式为(i, j, n):\n");
        scanf("(%d, %d, %d)", &i, &j, &n);
        graph->arc[i][j] = n;
        graph->arc[j][i] = n;
    }
    getchar();
}

void ai_mgraph_print(mgraph_t graph)
{
    int i, j;

    printf("\n\n########## graph ##########\n");
    printf("顶点为: ");
    for (i = 0; i < graph.num_vertexs; i++)
        printf("%c ", graph.vexs[i]);
    printf("\n");

    printf("边数组为: \n");
    for (i = 0; i < graph.num_vertexs; i++) {
        for (j = 0; j < graph.num_vertexs; j++)
            printf("%5d ", graph.arc[i][j]);
        printf("\n");
    }
    printf("###########################\n");
}


/************************************ main ************************************/
int main(int argc, char *argv[])
{
    mgraph_t g;

    ai_mgraph_created(&g);
    ai_mgraph_print(g);

    printf("\n深度遍历：");
    ai_DFS_travers(g);
    printf("\n");
    return EXIT_SUCCESS;
}
