#include<iostream>
#include<vector>
using namespace std;

class Condition{
public:
	vector <short> front_points;//������Դ��·��
	int here_point;/////////////////��ǰ�ĵ��ֵ
	bool win_or_lose;
	bool searched[200007];//��¼

};

class Map {
public:
	vector<short>front_one;//��ǰ��� ���� ǰһ��
	vector<short>next_one;//��ǰ��� ���� ��һ��
	bool win;
	bool lose;

};


//ȫ�ֱ�������

bool draw = 0;//�Ƿ��ѭ��

Map map_point[200007];

vector<Condition>lose_condition;
vector<Condition>win_condition;


bool debugging = true;				//************************************************��������

int main(){
	try {

		int n, m;
		if (debugging)cout << "�����㣿";
		cin >> n;
		if (debugging)cout << "�����ߣ����������У�����Ҳû�ã�";
		cin >> m;

		for (int i = 1; i <= n; i++) {//��i ����,��n ����1-n

			if (debugging)cout << "��" << i << "����ĳ��������ǣ�";
			int point_number;//��ʱֵ
			cin >> point_number;//����ô�������
			if (debugging)cout << "Ŷ" << endl;
			if (debugging)cout << "���Ƿֱ�Ϊ��";
			for (int j = 0; j < point_number; j++)
			{
				short temp;//Ҳ����ʱֵ
				cin >> temp;//��һ��
				map_point[i].next_one.push_back(temp);//ͨ����һ��
				map_point[temp].front_one.push_back(i);//��¼�ϸ�
			}
			if (debugging)cout << "	 Ŷ���ð�" << endl << endl;
		}
		//********************************************************���һ����������
		//int lose_len;
		//int win_len;
		{
			int first_point;//����
			cin >> first_point;
			Condition condition;
			condition.here_point = first_point;
			condition.searched[first_point] = true;

			lose_condition.push_back(condition);
		}
		//********************************************************�㶨���е�������

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		while (lose_condition.size() != 0) {

			for (unsigned i = 0; i < lose_condition.size(); i++)
			{

				Condition temp_condition;
				Condition i_condition = lose_condition[i];
				unsigned len = map_point[i_condition.here_point].next_one.size();

				int this_point_value = i_condition.here_point;

				for (unsigned j = 0; j < len; j++)
				{
					int next_point_value = map_point[this_point_value].next_one[j];
					temp_condition = i_condition;

					temp_condition.here_point = next_point_value;

					bool should_push = true;
					if (temp_condition.searched[next_point_value] == true) {
						draw = 1;
						if (map_point[next_point_value].win == true) {
							should_push = false;
						}
					}
					else {
						temp_condition.searched[next_point_value] = true;
					}

					temp_condition.win_or_lose = true;
					temp_condition.front_points.push_back(lose_condition[i].here_point);

					if (should_push) {
						win_condition.push_back(temp_condition);
					}

					map_point[next_point_value].win = true;
				}
			}
			lose_condition.clear();

			//////////////////////////////////////////////////////////////////////////////////////////////////
			if (win_condition.size() == 0) {
				break;
			}
			for (unsigned i = 0; i < win_condition.size(); i++)
			{
				Condition temp_condition;
				Condition i_condition = win_condition[i];
				unsigned len = map_point[i_condition.here_point].next_one.size();

				if (len == 0) {////////////////////////////////////////////////////////////////////////����Ӯ��
					cout << "Win:" << endl;
					for (unsigned i = 0; i < i_condition.front_points.size(); i++) {
						cout << i_condition.front_points[i] << " ";
					}
					cout << i_condition.here_point << endl;
					goto hmb;///////////////////////////////////////////////////////////////////////Ӯ��Ӯ��hhhhhh
				}

				int this_point_value = i_condition.here_point;

				for (unsigned j = 0; j < len; j++)
				{
					temp_condition = i_condition;
					int next_point_value = map_point[this_point_value].next_one[j];

					temp_condition.here_point = next_point_value;

					bool should_push = true;
					if (temp_condition.searched[next_point_value] == true) {
						draw = true;
						if (map_point[next_point_value].lose == true) {
							should_push = false;
						}
					}
					else {
						temp_condition.searched[next_point_value] = true;
					}

					temp_condition.win_or_lose = false;
					temp_condition.front_points.push_back(win_condition[i].here_point);

					if (should_push) {
						lose_condition.push_back(temp_condition);
					}

					map_point[next_point_value].lose = true;
				}
			}
			win_condition.clear();
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if (draw == true) {
		cout << "Draw" << endl;
	}
	else {
		cout << "Lose" << endl;
	}

hmb:	if (debugging) {
				cout <<endl<<endl<< "point         win              lose" << endl << endl;
				for (int i = 1; i <= n; i++) {
					cout << i<<":             "<<map_point[i].win << "                " << map_point[i].lose << endl;
				}
				cout << endl << "draw=" << draw<<endl;
			}


	}catch (exception e) {
				if (draw == true) {
					cout << "Draw" << endl;
				}
				else {
					cout << "Lose" << endl;
				}
				return 0;
	}

	return 0;
}