#include<iostream>
#include"Tourism.h"
using namespace std;
#pragma warning( disable : 4996)

int main()
{
	int flag = 0;
	while (true)
	{
		//输出界面
		cout << "****景区信息管理系统****" << endl;
		cout << "   1.创建景区景点图" << endl;
		cout << "   2.查询景点信息" << endl;
		cout << "   3.旅游景点导航" << endl;
		cout << "   4.搜索最短路径" << endl;
		cout << "   5.铺设电路规划" << endl;
		cout << "   0.退出" << endl;
		cout << "************************" << endl;
		int a;
		cout << "输入操作编号<0-5>:\n ";
		cin >> a;
		
		switch (a)
		{
		case 1:
		{
			flag = 1;

			CreateGraph();
			break;
		}
		case 2:
		{
		int b;
		do {
			if (flag == 1)
				GetSpotInfo();
			else
				cout << "还未创建景点图！" << endl;

			cout << "输入操作编号1-继续查找，0-返回上一级:";
			cin >> b;
		} while (b == 1);
		break;
		}
		case 3:
		{
			int b;
			do {
				if (flag == 1)
					TravelPath();
				else
					cout << "还未创建景点图！" << endl;
				
				cout << "输入操作编号1-继续查找，0-返回上一级:";
				cin >> b;
			} while (b == 1);
			break;
		}
		case 4:
		{
			int b;
			do {
				if (flag == 1)
					FindShortPath();
				else
					cout << "还未创建景点图！" << endl;

				cout << "输入操作编号1-继续查找，0-返回上一级:";
				cin >> b;
			} while (b == 1);
			break;
		}
		case 5:
		{
			int b;
			do {
				if (flag == 1)
					DesignPath();
				else
					cout << "还未创建景点图！" << endl;

				cout << "输入操作编号1-继续查找，0-返回上一级:";
				cin >> b;
			} while (b == 1);
			break;
			
			break;
		}
		case 0:
		{
			cout << "退出系统!" << endl;
			exit(0);
		}
		default:
		{
			cout << "输入错误，请输入操作编号<0-5>: \n";
			break;
		}
		}

	}
	return 0;
}
