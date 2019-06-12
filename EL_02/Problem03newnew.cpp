#include<iostream>
#include<vector>
using namespace std;



class Condition {
public:
	int here_point;/////////////////��ǰ�ĵ��ֵ
	bool searched[200007];//��¼

	bool gotoNextPoint(int value, bool);//������
};


class Map {
public:
	vector<int>next_one;//��ǰ��� ���� ��һ��
	bool win;
	bool lose;
};

class Tree {
public:
	int this_value;
	int front_tree_ptr;

	Tree(int value,int front) {
		this->this_value = value;
		this->front_tree_ptr = front;
	}
};

//ȫ�ֱ�������

bool draw = 0;//�Ƿ��ѭ��

vector<Condition>lose_condition;
vector<Condition>win_condition;

Map map_point[200007];

vector<Tree>big_tree;

vector<int>output_result;
//

bool Condition::gotoNextPoint(int value, bool win_Or_lose) {//������ɵ�ֵ��������ɵ�״̬
	{

		here_point = value;														//���� ����ֵ

		bool should_push = true;											//���ظ������� �����Ƿ�������

		if (searched[value] == true) {										//������Ѿ�����������
			draw = true;																//���Ծ�һ��ѭ����
			if ((map_point[value].win&&win_Or_lose) || (map_point[value].lose && !win_Or_lose)) {//�������������ڹ���״̬ Ҳ�ͼ�����ɵ�״̬һ��
				should_push = false;											//���Ծ�û��Ҫ�ƽ�ȥ�ˣ���Ȼ����ԩ��·
			}
		}
		else {																			//״̬��һ�£������б�Ҫ�Ƶģ�Ҳ����������Ӯ����
			searched[value] = true;
		}

		if (win_Or_lose) {														//������map�������Ժ���ظ���·
			map_point[value].win = true;
		}
		else {
			map_point[value].lose = true;
		}///////////////////////////////////////////////////////��������

		return should_push;

	}
}



bool debugging = false;				//************************************************/////		��������

int main() {
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
			}
			if (debugging)cout << "	 Ŷ���ð�" << endl << endl;
		}
		//********************************************************���һ����������
		
			int first_point;//����
			cin >> first_point;
			Condition condition;
			condition.here_point = first_point;
			condition.searched[first_point] = true;

			map_point[first_point].lose = 1;

			lose_condition.push_back(condition);

			big_tree.push_back(*new Tree(first_point, 0) );
		
		//********************************************************�㶨���е�������

		//*******************************************************************************************************************************************

		int tree_ptr = 0;
		while (lose_condition.size() != 0) {

			for (unsigned i = 0; i < lose_condition.size(); i++,tree_ptr++)
			{

				unsigned len = map_point[lose_condition[i].here_point].next_one.size();
				int this_point_value = lose_condition[i].here_point;

				for (unsigned j = 0; j < len; j++)
				{
					int next_point_value = map_point[this_point_value].next_one[j];

					Condition temp_condition = lose_condition[i];		//��ʱֵ

					if (temp_condition.gotoNextPoint(next_point_value, true)) {
						big_tree.push_back(*new Tree(next_point_value, tree_ptr));
						win_condition.push_back(temp_condition);
					}

				}
			}
			lose_condition.clear();

			//***************************************************************************************************************************
			if (win_condition.size() == 0) {
				break;
			}

			for (unsigned i = 0; i < win_condition.size(); i++,tree_ptr++)
			{
				Condition temp_condition;
				unsigned len = map_point[win_condition[i].here_point].next_one.size();

				if (len == 0) {////////////////////////////////////////////////////////////////////////����Ӯ��,���
					cout << "Win" << endl;
	
					Tree temp_tree = big_tree[tree_ptr];
					output_result.push_back(temp_tree.this_value);

					do{
						temp_tree = big_tree[temp_tree.front_tree_ptr];
						output_result.push_back(temp_tree.this_value);
					} while (temp_tree.front_tree_ptr!=0);

					output_result.push_back(first_point);
					
					for (int i =(int)output_result.size() - 1; i >= 0; i--) {
						cout << output_result[i]<<" ";
					}
					goto hmb;///////////////////////////////////////////////////////////////////////Ӯ��Ӯ��hhhhhh
				}

				for (unsigned j = 0; j < len; j++)
				{
					temp_condition = win_condition[i];

					int next_point_value = map_point[win_condition[i].here_point].next_one[j];

					if (temp_condition.gotoNextPoint(next_point_value, false)) {
						big_tree.push_back(*new Tree(next_point_value, tree_ptr ));
						lose_condition.push_back(temp_condition);
					}

				}
			}
			win_condition.clear();
		}
		//******************************************************************************************************************************************************
		if (draw == true) {
			cout << "Draw" << endl;
		}
		else {
			cout << "Lose" << endl;
		}

hmb:	if (debugging) {
		cout << endl << endl << "point         win              lose" << endl << endl;
		for (int i = 1; i <= n; i++) {
			cout << i << ":             " << map_point[i].win << "                " << map_point[i].lose << endl;
		}
		cout << endl << "draw=" << draw << endl;
	}


	}
	catch (exception e) {															//��֪����ʲô��
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