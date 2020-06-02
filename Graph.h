#ifndef GRAPH_H
#define GRAPH_H
#define MAXNUM 20

struct Vex
{
	int num;//������
	char name[20];//��������
	char desc[1024];//�������
};
struct Edge
{
	int vex1;//�ߵĵ�һ������
	int vex2;//�ߵĵڶ�������
	int weight;//Ȩֵ
};
struct Graph
{
	int m_aAdjMatrix[MAXNUM][MAXNUM];//�ڽӾ���
	Vex m_aVexs[MAXNUM];//������Ϣ��
	int m_nVexNum;//��ǰͼ�Ķ������
};
typedef struct Path
{
	int vexs[MAXNUM];//����һ��·��
	Path* next;
}*PathList;//��������·��

void Init(void);
bool InsertVex(Vex sVex);
bool InsertEdge(Edge sEdge);
Vex GetVex(int nVex);
int FindEdge(int nVex, Edge aEdge[]);
int GetVexnum(void);
void DFS(int nVex, bool isVisited[], int& nIndex, PathList& pList);
void DFSTraverse(int nVex, PathList& pList);
int FindShortPathDj(int nVexStart, int nVexEnd, int aPath[]);
int FindMinTreePrim(Edge aPath[]);
#endif GRAPH_H