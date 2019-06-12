#include<iostream>
#include<vector>
using namespace std;

class Condition{
public:
	vector <short> front_points;//它的来源的路径
	int here_point;/////////////////当前的点的值
	bool win_or_lose;
	bool searched[200007];//记录

};

class Map {
public:
	vector<short>front_one;//当前点的 所有 前一个
	vector<short>next_one;//当前点的 所有 下一个
	bool win;
	bool lose;

};


//全局变量区：

bool draw = 0;//是否可循环

Map map_point[200007];

vector<Condition>lose_condition;
vector<Condition>win_condition;


bool debugging = true;				//************************************************用来测试

int main(){
	try {

		int n, m;
		if (debugging)cout << "几个点？";
		cin >> n;
		if (debugging)cout << "几条边？（随便输就行，反正也没用）";
		cin >> m;

		for (int i = 1; i <= n; i++) {//第i 个点,共n 个，1-n

			if (debugging)cout << "第" << i << "个点的出口数量是：";
			int point_number;//临时值
			cin >> point_number;//有那么多个出口
			if (debugging)cout << "哦" << endl;
			if (debugging)cout << "它们分别为：";
			for (int j = 0; j < point_number; j++)
			{
				short temp;//也是临时值
				cin >> temp;//下一个
				map_point[i].next_one.push_back(temp);//通向下一个
				map_point[temp].front_one.push_back(i);//记录上个
			}
			if (debugging)cout << "	 哦，好吧" << endl << endl;
		}
		//********************************************************完成一部分输入了
		//int lose_len;
		//int win_len;
		{
			int first_point;//如题
			cin >> first_point;
			Condition condition;
			condition.here_point = first_point;
			condition.searched[first_point] = true;

			lose_condition.push_back(condition);
		}
		//********************************************************搞定所有的输入了

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

				if (len == 0) {////////////////////////////////////////////////////////////////////////终于赢了
					cout << "Win:" << endl;
					for (unsigned i = 0; i < i_condition.front_points.size(); i++) {
						cout << i_condition.front_points[i] << " ";
					}
					cout << i_condition.here_point << endl;
					goto hmb;///////////////////////////////////////////////////////////////////////赢了赢了hhhhhh
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