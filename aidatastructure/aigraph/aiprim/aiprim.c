/*
 * =============================================================================
 *
 *       Filename:  aiprim.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2020年07月18日 09时16分28秒
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

#define AI_MAXVEX   20
#define AI_MAXEGDE  20
#define AI_INFINITY 65536

typedef struct {
    int arc[AI_MAXVEX][AI_MAXVEX];
    int num_vertexes;
    int num_edges;
} ai_mgraph_t;

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

// 查早从V0开始的最小生成树
void ai_mini_span_tree_prim(ai_mgraph_t g)
{
    // k用来存储某一顶点关联的最小权值边的顶点
    int i, j, k;
    int min;
    /* 
     * 存储各个顶点关联的边的前驱顶点的下标值,在这里初始化
     * 隐含表示都初始化为V0顶点的下标
     */
    int adjvex[AI_MAXVEX] = {0};
    /* 存储各个顶点[索引值代表的顶点]到某个共同顶点k的权值 */
    int low_cost[AI_MAXVEX] = {0};

    // 首先需要用第0行的数据进行算法初始化操作
    for (i = 0; i < g.num_vertexes; i++) {
        low_cost[i] = g.arc[0][i];
    }
    // 在low_cost中找最小的权值
    for (i = 1; i < g.num_vertexes; i++) {
        min = AI_INFINITY;
        k = 0;
        for (j = 1; j < g.num_vertexes; j++) {
            if (low_cost[j] != 0 && low_cost[j] < min) {
                min = low_cost[j];
                k = j;
            }
        }

        // 处理当前顶点
        printf(" (%d, %d) ", adjvex[k], k);
        // 将当前顶点的权值设为0，表示此顶点已经完成查找
        low_cost[k] = 0;
        // 把下一组要用的点的数据放入adjvex和low_cost中进行下一轮查找
        for (j = 1; j < g.num_vertexes; j++) {
            if (low_cost[j] != 0 && g.arc[k][j] < low_cost[j]) {
                low_cost[j] = g.arc[k][j];
                adjvex[j] = k;
            }
        }
    }
}

/************************************ main ************************************/
int main()
{
    ai_mgraph_t graph;

    create_mgraph(&graph);
    print_mgraph(graph);
    printf("\nprim:\n");
    ai_mini_span_tree_prim(graph);
    printf("\n");

    return EXIT_SUCCESS;
}
