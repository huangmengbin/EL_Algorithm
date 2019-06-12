#include<iostream>
#include<vector>
using namespace std;



class Condition {
public:
	int here_point;/////////////////当前的点的值
	bool searched[200007];//记录

	bool gotoNextPoint(int value, bool);//先声明
};


class Map {
public:
	vector<int>next_one;//当前点的 所有 下一个
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

//全局变量区：

bool draw = 0;//是否可循环

vector<Condition>lose_condition;
vector<Condition>win_condition;

Map map_point[200007];

vector<Tree>big_tree;

vector<int>output_result;
//

bool Condition::gotoNextPoint(int value, bool win_Or_lose) {//即将变成的值，即将变成的状态
	{

		here_point = value;														//更新 这点的值

		bool should_push = true;											//返回给调用者 决定是否将它推入

		if (searched[value] == true) {										//这个点已经被经历过了
			draw = true;																//所以就一定循环了
			if ((map_point[value].win&&win_Or_lose) || (map_point[value].lose && !win_Or_lose)) {//而且它曾经存在过的状态 也和即将变成的状态一致
				should_push = false;											//所以就没必要推进去了，不然会走冤枉路
			}
		}
		else {																			//状态不一致，还是有必要推的，也就是这个点可赢可输
			searched[value] = true;
		}

		if (win_Or_lose) {														//反馈给map，以免以后的重复走路
			map_point[value].win = true;
		}
		else {
			map_point[value].lose = true;
		}///////////////////////////////////////////////////////反馈好了

		return should_push;

	}
}



bool debugging = false;				//************************************************/////		用来测试

int main() {
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
			}
			if (debugging)cout << "	 哦，好吧" << endl << endl;
		}
		//********************************************************完成一部分输入了
		
			int first_point;//如题
			cin >> first_point;
			Condition condition;
			condition.here_point = first_point;
			condition.searched[first_point] = true;

			map_point[first_point].lose = 1;

			lose_condition.push_back(condition);

			big_tree.push_back(*new Tree(first_point, 0) );
		
		//********************************************************搞定所有的输入了

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

					Condition temp_condition = lose_condition[i];		//临时值

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

				if (len == 0) {////////////////////////////////////////////////////////////////////////终于赢了,输出
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
					goto hmb;///////////////////////////////////////////////////////////////////////赢了赢了hhhhhh
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
	catch (exception e) {															//不知道有什么用
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