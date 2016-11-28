// ConsoleApplication2.cpp : �������̨Ӧ�ó������ڵ㡣
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
	int no;				//������
	InfoType info;			//����������Ϣ
} VertexType;			//��������
typedef struct  			//ͼ�Ķ���
{
	int edges[MAXV][MAXV]; 	//�ڽӾ���
	int n, e;  			//������,����
	VertexType vexs[MAXV];	//��Ŷ�����Ϣ
} MGraph;


typedef struct ANode
{
	int adjvex;			//�ñߵ��յ���
	struct ANode *nextarc;	//ָ����һ���ߵ�ָ��
	InfoType info;			//�ñߵ������Ϣ
} ArcNode;				//�߱�ڵ�����
typedef struct Vnode
{
	Vertex data;			//������Ϣ
	ArcNode *firstarc;		//ָ���һ����
} VNode;				//�ڽӱ�ͷ�ڵ�����
typedef VNode AdjList[MAXV];	//AdjList���ڽӱ�����
typedef struct
{
	AdjList adjlist;		//�ڽӱ�
	int n, e;				//ͼ�ж�����n�ͱ���e
} ALGraph;				//������ͼ�ڽӱ�����

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
	if (g->adjlist[start].firstarc!=NULL && g->adjlist[start].firstarc->adjvex == end)	   // endΪ��Ե�ڵ�
	{
		for (int i = 0; i < length; i++)
		{
			printf("%d ", s->data[i]);
		}
		printf("%d\n", end);
	}
	else
	{
		ArcNode *p = g->adjlist[start].firstarc;
		while (p != NULL)
		{
			if (p->adjvex == end)  												 //start��һ�����ڽڵ�Ϊend
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
	}
	visited[s->data[s->top]] = 0;
	pop(s);
	return;
}

void MatToList(MGraph g, ALGraph *&G)
//���ڽӾ���gת�����ڽӱ�G
{
	int i, j, n = g.n; ArcNode *p; //nΪ������
	G = (ALGraph *)malloc(sizeof(ALGraph));
	for (i = 0; i < n; i++)     //������ͷ�ڵ��ָ�����ó�ֵ
		G->adjlist[i].firstarc = NULL;
	for (i = 0; i<n; i++)	 //����ڽӾ�����ÿ��Ԫ��
		for (j = n - 1; j >= 0; j--)
			if (g.edges[i][j] != 0)
			{
				p = (ArcNode *)malloc(sizeof(ArcNode));
				//�����ڵ�*p
				p->adjvex = j;
				p->nextarc = G->adjlist[i].firstarc;
				//��*p��������ͷ
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
	printf("�������ڽӾ���\n");
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


