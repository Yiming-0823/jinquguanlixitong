#include<iostream>
#include"Tourism.h"
using namespace std;
#pragma warning( disable : 4996)

int main()
{
	int flag = 0;
	while (true)
	{
		//�������
		cout << "****������Ϣ����ϵͳ****" << endl;
		cout << "   1.������������ͼ" << endl;
		cout << "   2.��ѯ������Ϣ" << endl;
		cout << "   3.���ξ��㵼��" << endl;
		cout << "   4.�������·��" << endl;
		cout << "   5.�����·�滮" << endl;
		cout << "   0.�˳�" << endl;
		cout << "************************" << endl;
		int a;
		cout << "����������<0-5>:\n ";
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
				cout << "��δ��������ͼ��" << endl;

			cout << "����������1-�������ң�0-������һ��:";
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
					cout << "��δ��������ͼ��" << endl;
				
				cout << "����������1-�������ң�0-������һ��:";
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
					cout << "��δ��������ͼ��" << endl;

				cout << "����������1-�������ң�0-������һ��:";
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
					cout << "��δ��������ͼ��" << endl;

				cout << "����������1-�������ң�0-������һ��:";
				cin >> b;
			} while (b == 1);
			break;
			
			break;
		}
		case 0:
		{
			cout << "�˳�ϵͳ!" << endl;
			exit(0);
		}
		default:
		{
			cout << "�������������������<0-5>: \n";
			break;
		}
		}

	}
	return 0;
}
