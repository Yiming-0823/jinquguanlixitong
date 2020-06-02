#include"Graph.h"
#include<iostream>
using namespace std;
Graph graph;
int EdgeNum;
Edge aEdge[100];
int allPath[MAXNUM][MAXNUM] = { 0 };
int PathNum = 0;



void Init(void)
{
	for (int i = 0; i < MAXNUM; i++)
	{
		for (int j = 0; j < MAXNUM; j++)
		{
			if (i == j)
				graph.m_aAdjMatrix[i][j] = 0;
			else
				graph.m_aAdjMatrix[i][j] = 0xffff;
		}
	}
	graph.m_nVexNum = 0;
}

bool InsertVex(Vex sVex)
{
	if (graph.m_nVexNum >= MAXNUM)
	{//顶点已满
		return false;
	}
	graph.m_aVexs[graph.m_nVexNum++] = sVex;
	return true;
}

bool InsertEdge(Edge sEdge)
{
	if (sEdge.vex1 == sEdge.vex2)
		return false;
	graph.m_aAdjMatrix[sEdge.vex1][sEdge.vex2] = sEdge.weight;
	graph.m_aAdjMatrix[sEdge.vex2][sEdge.vex1] = sEdge.weight;
	return true;
}

Vex GetVex(int nVex)
{
	return graph.m_aVexs[nVex];
}

int FindEdge(int nVex, Edge aEdge[])
{
	int k = 0;
	for (int i = 0; i < graph.m_nVexNum; i++)
	{
		if (graph.m_aAdjMatrix[i][nVex] > 0 && graph.m_aAdjMatrix[i][nVex] < 0xffff)
		{
			aEdge[k].vex1 = nVex;
			aEdge[k].vex2 = i;
			aEdge[k].weight = graph.m_aAdjMatrix[i][nVex];
			k++;
		}
	}
	return k;
}

int GetVexnum(void)
{
	return graph.m_nVexNum;
}

void DFS(int nVex, bool isVisited[], int& nIndex, PathList& pList)
{//nIndex记录遍历的深度

	isVisited[nVex] = true;
	pList->vexs[nIndex++] = nVex;
	//判断是否所有的顶点都已被访问过
	if (nIndex == graph.m_nVexNum)
	{
		pList->next = (PathList)malloc(sizeof(Path));
		for (int i = 0; i < graph.m_nVexNum; i++)
		{
			pList->next->vexs[i] = pList->vexs[i];
		}
		pList = pList->next;
		pList->next = NULL;
	}

	else
	{
		for (int i =0; i < graph.m_nVexNum; i++)
		{
			if (graph.m_aAdjMatrix[nVex][i] > 0 && graph.m_aAdjMatrix[nVex][i] < 0xffff && isVisited[i] == 0)
			{
				DFS(i, isVisited, nIndex, pList);//递归调用DFS
				isVisited[i] = false;//
				nIndex--;
			}
		}
	}

}

void DFSTraverse(int nVex, PathList& pList)
{
	int nIndex = 0;
	bool isVisited[MAXNUM] = { false };
	DFS(nVex, isVisited, nIndex, pList);
}

int FindShortPathDj(int nVexStart, int nVexEnd,int aPath[])
{
		int i,j, k, minP;
		int min;
		bool visit[MAXNUM] = {false};//判断是否已经求出到该顶点的最短路径
		int numShort[MAXNUM];//保存从出发点到某一顶点的距离
		int numPath[MAXNUM];//保存到下标点的到出发点最短路径的前驱节点

		//初始化
		for (i = 0; i < graph.m_nVexNum; i++)
		{
			numShort[i] = graph.m_aAdjMatrix[nVexStart][i];//初始化nVexStart到其他顶点v的最短距离
			numPath[i] = nVexStart;//初始化到i点的最短路径的前驱结点为nVexStart
		}
		visit[nVexStart] = true;
		numShort[nVexStart] = 0;

		//遍历graph.m_nVexNum-1次；每次找出一个顶点的最短路径
		for (i = 1; i < graph.m_nVexNum; i++)
		{
			//找到最短路径
			min = 0xffff;
			for (j = 0; j < graph.m_nVexNum; j++)
			{
				if (visit[j] == false && numShort[j] < min)
				{
					min = numShort[j];
					minP = j;
				}
			}
			visit[minP] = true;//求得到顶点minp的最短路径

			//将已找到最短路径的顶点minp作为中间点，去计算到达所有顶点的最短路径
			for (k = 0; k < graph.m_nVexNum; k++)
			{
				if (visit[k]==false && ((min + graph.m_aAdjMatrix[minP][k]) < numShort[k])&& graph.m_aAdjMatrix[minP][k]< 0xffff)//找到有新的最短路径
				{//更新
					numShort[k] = min + graph.m_aAdjMatrix[minP][k];
					numPath[k] = minP;
				}
			}
		}

		//输出最短路径
		int num = 0;
		int mp = nVexEnd;
		aPath[num] = nVexEnd;
		while (mp != nVexStart)
		{
            num++;
			aPath[num] = numPath[mp];//倒序加入路径
			mp = numPath[mp];
		}
		return num;
	
}


int FindMinTreePrim(Edge aPath[])
{
	int start, end;//start为前一个已访问的点，end为下一个将要访问的点
	bool visited[MAXNUM];//保存某点是否已经被访问
	int min;

	for (int i = 0; i < graph.m_nVexNum; i++)
	{
		visited[i] = 0;//所有点都未被访问
	}
	visited[0] = true;//0点已被访问
	start = 0;
	end = 0;
	for (int i = 0; i < graph.m_nVexNum - 1; i++)
	{
		min = 0xffff;
		for (int j = 0; j < graph.m_nVexNum; j++)
		{
			for (int k = 0; k < graph.m_nVexNum; k++)
			{
				if ((visited[j] == true) && (visited[k] ==false) && (graph.m_aAdjMatrix[j][k] < min))
				{//更新最短路径
					min = graph.m_aAdjMatrix[j][k];
					start = j;
					end = k;
				}
			}
		}
		visited[end] = true;
		aPath[i].vex1 = start;
		aPath[i].vex2 = end;
		aPath[i].weight = graph.m_aAdjMatrix[start][end];
	}
	return 0;
}


