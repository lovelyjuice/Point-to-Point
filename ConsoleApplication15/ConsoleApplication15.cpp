// ConsoleApplication2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "stdlib.h"
#define MAX 1000
#define MAXV 11
#define InfoType int
#define Vertex int

int visited[MAXV];
typedef struct
{
	int no;				//顶点编号
	InfoType info;			//顶点其他信息
} VertexType;			//顶点类型
typedef struct  			//图的定义
{
	int edges[MAXV][MAXV]; 	//邻接矩阵
	int n, e;  			//顶点数,弧数
	VertexType vexs[MAXV];	//存放顶点信息
} MGraph;


typedef struct ANode
{
	int adjvex;			//该边的终点编号
	struct ANode *nextarc;	//指向下一条边的指针
	InfoType info;			//该边的相关信息
} ArcNode;				//边表节点类型
typedef struct Vnode
{
	Vertex data;			//顶点信息
	ArcNode *firstarc;		//指向第一条边
} VNode;				//邻接表头节点类型
typedef VNode AdjList[MAXV];	//AdjList是邻接表类型
typedef struct
{
	AdjList adjlist;		//邻接表
	int n, e;				//图中顶点数n和边数e
} ALGraph;				//完整的图邻接表类型

typedef struct
{
	int data[MAX];
	int top;
}SqStack;


void initStack(SqStack *&s)
{
	s = (SqStack *)malloc(sizeof(SqStack*));
	s->top = -1;
}

bool push(SqStack *s, int data)
{
	s->data[++s->top] = data;
	return true;
}

bool pop(SqStack *s)
{
	if (s->top == -1)return false;
	else s->top--;
	return true;
}

void path(SqStack *s, ALGraph *g, int start, int end, int length)
{
	push(s, start);

		ArcNode *p = g->adjlist[start].firstarc;
		while (p != NULL)
		{
			if (p->adjvex == end)  												 //start的一个相邻节点为end
			{
				for (int i = 0; i < length; i++)
				{
					printf("%d ", s->data[i]);	
				}
				printf("%d\n", end);
				p = p->nextarc;
				continue;
			}
			visited[start] = 1;													
			if(visited[p->adjvex]!=1)path(s, g, p->adjvex, end, length + 1);
			p = p->nextarc;
			
		}
	
	visited[s->data[s->top]] = 0;
	pop(s);
	return;
}

void MatToList(MGraph g, ALGraph *&G)
//将邻接矩阵g转换成邻接表G
{
	int i, j, n = g.n; ArcNode *p; //n为顶点数
	G = (ALGraph *)malloc(sizeof(ALGraph));
	for (i = 0; i < n; i++)     //给所有头节点的指针域置初值
		G->adjlist[i].firstarc = NULL;
	for (i = 0; i<n; i++)	 //检查邻接矩阵中每个元素
		for (j = n - 1; j >= 0; j--)
			if (g.edges[i][j] != 0)
			{
				p = (ArcNode *)malloc(sizeof(ArcNode));
				//创建节点*p
				p->adjvex = j;
				p->nextarc = G->adjlist[i].firstarc;
				//将*p链到链表头
				G->adjlist[i].firstarc = p;
			}
	G->n = n; G->e = g.e;
}
int main()
{
	MGraph g;
	ALGraph *G;
	SqStack *s;
	initStack(s);
	printf("请输入邻接矩阵：\n");
	for (int i = 0; i < MAXV; i++)
		for (int j = 0; j < MAXV; j++)scanf_s("%d", &g.edges[i][j]);
	g.n = MAXV;
	MatToList(g, G);
	for (int i = 0; i < MAXV; i++)visited[i] = 0;
	visited[0] = 1;
	int num;
	scanf_s("%d", &num);
	path(s, G, 0, 5, 1);
	return 0;
}


