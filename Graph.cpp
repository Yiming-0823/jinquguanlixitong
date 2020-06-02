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
	{//��������
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
{//nIndex��¼���������

	isVisited[nVex] = true;
	pList->vexs[nIndex++] = nVex;
	//�ж��Ƿ����еĶ��㶼�ѱ����ʹ�
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
				DFS(i, isVisited, nIndex, pList);//�ݹ����DFS
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
		bool visit[MAXNUM] = {false};//�ж��Ƿ��Ѿ�������ö�������·��
		int numShort[MAXNUM];//����ӳ����㵽ĳһ����ľ���
		int numPath[MAXNUM];//���浽�±��ĵ����������·����ǰ���ڵ�

		//��ʼ��
		for (i = 0; i < graph.m_nVexNum; i++)
		{
			numShort[i] = graph.m_aAdjMatrix[nVexStart][i];//��ʼ��nVexStart����������v����̾���
			numPath[i] = nVexStart;//��ʼ����i������·����ǰ�����ΪnVexStart
		}
		visit[nVexStart] = true;
		numShort[nVexStart] = 0;

		//����graph.m_nVexNum-1�Σ�ÿ���ҳ�һ����������·��
		for (i = 1; i < graph.m_nVexNum; i++)
		{
			//�ҵ����·��
			min = 0xffff;
			for (j = 0; j < graph.m_nVexNum; j++)
			{
				if (visit[j] == false && numShort[j] < min)
				{
					min = numShort[j];
					minP = j;
				}
			}
			visit[minP] = true;//��õ�����minp�����·��

			//�����ҵ����·���Ķ���minp��Ϊ�м�㣬ȥ���㵽�����ж�������·��
			for (k = 0; k < graph.m_nVexNum; k++)
			{
				if (visit[k]==false && ((min + graph.m_aAdjMatrix[minP][k]) < numShort[k])&& graph.m_aAdjMatrix[minP][k]< 0xffff)//�ҵ����µ����·��
				{//����
					numShort[k] = min + graph.m_aAdjMatrix[minP][k];
					numPath[k] = minP;
				}
			}
		}

		//������·��
		int num = 0;
		int mp = nVexEnd;
		aPath[num] = nVexEnd;
		while (mp != nVexStart)
		{
            num++;
			aPath[num] = numPath[mp];//�������·��
			mp = numPath[mp];
		}
		return num;
	
}


int FindMinTreePrim(Edge aPath[])
{
	int start, end;//startΪǰһ���ѷ��ʵĵ㣬endΪ��һ����Ҫ���ʵĵ�
	bool visited[MAXNUM];//����ĳ���Ƿ��Ѿ�������
	int min;

	for (int i = 0; i < graph.m_nVexNum; i++)
	{
		visited[i] = 0;//���е㶼δ������
	}
	visited[0] = true;//0���ѱ�����
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
				{//�������·��
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


