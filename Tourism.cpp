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
	cout << "**** 创建景区景点图 ****" << endl;
	cout << "顶点数目：" << num << endl;
	cout << "----- 顶点 -----" << endl;
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
	cout << "----- 边 -----" << endl;
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
	cout << "**** 查询景点信息 ****" << endl;
	for (int i = 0; i < graph.m_nVexNum; i++)
	{
		cout << graph.m_aVexs[i].num << "-" << graph.m_aVexs[i].name << endl;
	}
	int nVex;
	cout << "输入想要查询的景点编号: ";
	cin >> nVex;
	Vex sVex = GetVex(nVex);
	printf("%s\n%s\n", sVex.name, sVex.desc);
	cout << "----- 周边景区 -----" << endl;
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
	cout << "===== 旅游景点导航 =====" << endl;
	for (int i = 0; i < graph.m_nVexNum; i++)
	{
		cout << graph.m_aVexs[i].num << "-" << graph.m_aVexs[i].name << endl;
	}
	cout << "请输入起始点编号：";
	int nVex;
	cin >> nVex;
	int nIndex = 0;
	bool isVisited[MAXNUM] = { false };
	DFS(nVex, isVisited, nIndex, pList);
	cout << "导航路线为: " << endl;
	pList = PHead;
	int i = 1;
	while (pList->next)
	{
		Vex sVex = GetVex(pList->vexs[0]);
		cout << "路线" << i++ << ":" << sVex.name;
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
	cout << "===== 搜索最短路径 =====" << endl;
	for (int i = 0; i < graph.m_nVexNum; i++)
	{
		cout << graph.m_aVexs[i].num << "-" << graph.m_aVexs[i].name << endl;
	}
	int nVexStart;
	int nVexEnd;
	cout << "请输入起点的编号: ";
	cin >> nVexStart;
	cout << "请输入终点的编号: ";
	cin >> nVexEnd;
	int aPath[MAXNUM];
	int nNum = FindShortPathDj(nVexStart, nVexEnd, aPath);
	int i, t, aLength = 0;
	cout << "最短路线为：";
	for (i = nNum; i >= 0; i--)//倒序输出路径数组
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
	cout << "最短距离为： " << aLength << endl;
	cout << endl << endl;
}

void DesignPath(void)
{
	cout << "===== 铺设电路规划 =====" << endl;
	cout << "在以下两个景点之间铺设电路：" << endl;
	Edge aPath[MAXNUM];
	FindMinTreePrim(aPath);
	int sum = 0;
	for (int i = 0; i < graph.m_nVexNum - 1; i++)
	{
		cout << graph.m_aVexs[aPath[i].vex1].name << " - " << graph.m_aVexs[aPath[i].vex2].name << "\t" << aPath[i].weight << endl;
		sum += aPath[i].weight;
	}
	cout << "铺设电路的总长度为：" << sum;
	cout << endl << endl << endl;
}