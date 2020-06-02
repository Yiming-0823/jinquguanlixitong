#include"Tourism.h"
#include"Graph.h"
#include<iostream>
using namespace std;
extern Graph graph;
extern int EdgeNum;
extern Edge aEdge[100];

#pragma warning (disable : 4996)


void CreateGraph(void)
{
	Init();
	FILE* fp = NULL;
	fp = fopen("D:\Vex.txt", "r");
	if (!fp)
	{
		printf("Failed to open the file!");
		exit(-1);
	}
	int num;
	Vex sVex;
	fscanf(fp, "%d", &num);
	cout << "**** ������������ͼ ****" << endl;
	cout << "������Ŀ��" << num << endl;
	cout << "----- ���� -----" << endl;
	for (int i = 0; i < num; i++)
	{
		fscanf(fp, "%d", &sVex.num);
		fscanf(fp, "%s", &sVex.name);
		fscanf(fp, "%s", &sVex.desc);
		cout << sVex.num << "-" << sVex.name << endl;
		InsertVex(sVex);
	}
	fclose(fp);
	fp = fopen("D:\Edge.txt", "r");
	if (!fp)
	{
		printf("Failed to open this file!");
		exit(-1);
	}
	Edge sEdge;
	cout << "----- �� -----" << endl;
	EdgeNum = 0;
	while (!feof(fp))
	{
		fscanf(fp, "%d", &sEdge.vex1);
		fscanf(fp, "%d", &sEdge.vex2);
		fscanf(fp, "%d", &sEdge.weight);
		printf("<v%d,v%d> %d\n", sEdge.vex1, sEdge.vex2, sEdge.weight);
		InsertEdge(sEdge);
		aEdge[EdgeNum++] = sEdge;
	}
	fclose(fp);
	cout << endl << endl;
}


void GetSpotInfo(void)
{
	cout << "**** ��ѯ������Ϣ ****" << endl;
	for (int i = 0; i < graph.m_nVexNum; i++)
	{
		cout << graph.m_aVexs[i].num << "-" << graph.m_aVexs[i].name << endl;
	}
	int nVex;
	cout << "������Ҫ��ѯ�ľ�����: ";
	cin >> nVex;
	Vex sVex = GetVex(nVex);
	printf("%s\n%s\n", sVex.name, sVex.desc);
	cout << "----- �ܱ߾��� -----" << endl;
	int k = FindEdge(nVex, aEdge);
	for (int i = 0; i < k; i++)
	{
		cout << graph.m_aVexs[aEdge[i].vex1].name << "->" << graph.m_aVexs[aEdge[i].vex2].name << " " << aEdge[i].weight << "m" << endl;
	}
	cout << endl << endl;
}

void TravelPath(void)
{
	PathList pList;
	pList = (Path*)malloc(sizeof(Path));
	PathList PHead;
	PHead = pList;
	cout << "===== ���ξ��㵼�� =====" << endl;
	for (int i = 0; i < graph.m_nVexNum; i++)
	{
		cout << graph.m_aVexs[i].num << "-" << graph.m_aVexs[i].name << endl;
	}
	cout << "��������ʼ���ţ�";
	int nVex;
	cin >> nVex;
	int nIndex = 0;
	bool isVisited[MAXNUM] = { false };
	DFS(nVex, isVisited, nIndex, pList);
	cout << "����·��Ϊ: " << endl;
	pList = PHead;
	int i = 1;
	while (pList->next)
	{
		Vex sVex = GetVex(pList->vexs[0]);
		cout << "·��" << i++ << ":" << sVex.name;
		for (int j = 1; j < graph.m_nVexNum; j++)
		{
			printf(" -> %s", graph.m_aVexs[pList->vexs[j]].name);
		}
		cout << endl;
		Path* temp = pList;
		pList = pList->next;
		free(temp);
	}
	free(pList);
	pList = NULL;
	PHead = NULL;
	cout << endl << endl << endl;

}


void FindShortPath(void)
{
	cout << "===== �������·�� =====" << endl;
	for (int i = 0; i < graph.m_nVexNum; i++)
	{
		cout << graph.m_aVexs[i].num << "-" << graph.m_aVexs[i].name << endl;
	}
	int nVexStart;
	int nVexEnd;
	cout << "���������ı��: ";
	cin >> nVexStart;
	cout << "�������յ�ı��: ";
	cin >> nVexEnd;
	int aPath[MAXNUM];
	int nNum = FindShortPathDj(nVexStart, nVexEnd, aPath);
	int i, t, aLength = 0;
	cout << "���·��Ϊ��";
	for (i = nNum; i >= 0; i--)//�������·������
	{
		if (i != 0)
		{
			cout << graph.m_aVexs[aPath[i]].name << "->";
			t = i - 1;
			aLength += graph.m_aAdjMatrix[aPath[i]][aPath[t]];
		}
		else
		{
			cout << graph.m_aVexs[aPath[i]].name;
		}

	}
	cout << endl;
	cout << "��̾���Ϊ�� " << aLength << endl;
	cout << endl << endl;
}

void DesignPath(void)
{
	cout << "===== �����·�滮 =====" << endl;
	cout << "��������������֮�������·��" << endl;
	Edge aPath[MAXNUM];
	FindMinTreePrim(aPath);
	int sum = 0;
	for (int i = 0; i < graph.m_nVexNum - 1; i++)
	{
		cout << graph.m_aVexs[aPath[i].vex1].name << " - " << graph.m_aVexs[aPath[i].vex2].name << "\t" << aPath[i].weight << endl;
		sum += aPath[i].weight;
	}
	cout << "�����·���ܳ���Ϊ��" << sum;
	cout << endl << endl << endl;
}