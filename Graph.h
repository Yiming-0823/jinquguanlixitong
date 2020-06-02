#ifndef GRAPH_H
#define GRAPH_H
#define MAXNUM 20

struct Vex
{
	int num;//景点编号
	char name[20];//景点名字
	char desc[1024];//景点介绍
};
struct Edge
{
	int vex1;//边的第一个顶点
	int vex2;//边的第二个顶点
	int weight;//权值
};
struct Graph
{
	int m_aAdjMatrix[MAXNUM][MAXNUM];//邻接矩阵
	Vex m_aVexs[MAXNUM];//顶点信息组
	int m_nVexNum;//当前图的顶点个数
};
typedef struct Path
{
	int vexs[MAXNUM];//保存一条路径
	Path* next;
}*PathList;//保存所有路径

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