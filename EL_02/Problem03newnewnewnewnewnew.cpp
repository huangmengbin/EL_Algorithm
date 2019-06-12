#include<iostream>
#include<vector>
using namespace std;


class Map {
public:
	vector<int>next_one;//当前点的 所有 下一个   用整数表达算了map[int_list.back()].next_one.back()]  或者用迭代器？
	bool win;					//我记得好像默认为false??
	bool lose;
	bool is_end;

	Map(){
		win = false;
		lose = false;
		is_end = false;
	}
};



//全局变量区：
Map map_point[200007];
//

//由于空间问题，不得不放全局区

vector<int>int_list;										//当前的搜索
bool searched[200007];								//search[0]作废，记录当前的搜索  存在了哪些整数  感觉有点像一个监控器？
//
//

int is_draw(int first, Map* map) {			//////这个子函数是，深度优先搜索，可是我不会呀。。。。。
																		//还有它貌似和Map类相关不大，写到外面应该也是可以的
	bool draw = false;										//记录是否可循环

	int_list.push_back(first);								//放第一个进去

	while (int_list.size() != 1 || map[int_list.back()].next_one.size() != 0)//只要长度不是1，或者还能深入延申,都继续循环
	{
		while (map[int_list.back()].next_one.size() != 0)							//能延申就。。。再进入循环
		{

			searched[int_list.back()] = true;												//记录
			if ((int_list.size() & 1) == 0) {													//长度为偶数，可能可以赢
				map[int_list.back()].win = true;											//反馈给map的win
			}
			else {
				map[int_list.back()].lose = true;											//不解释
			}

			int_list.push_back(map[int_list.back()].next_one.back());			//下一个也推进去


			if (searched[int_list.back()] == true) {										//新的这个在以前那里已经存在过了
				draw = true;																		//嗯

				if (((int_list.size() & 1) == 0) && (map[int_list.back()].win == true)) {			//以前已经搜过这种状态了
					int_list.pop_back();
					map[int_list.back()].next_one.pop_back();
				}
				else if (((int_list.size() & 1) == 1) && (map[int_list.back()].lose == true)) {	//以前已经搜过这种状态了
					int_list.pop_back();
					map[int_list.back()].next_one.pop_back();
				}

			}//end if

		}//end 内层 while

		//不能延申了，，

		if ((int_list.size() & 1) == 0 && (map[int_list.back()].is_end)) {//长度是双数，那就赢了
			cout << "Win" << endl;
			for (unsigned i = 0; i < int_list.size(); i++) {
				cout << int_list[i] << " ";
			}
			cout << endl;
			return 2;																			//win
		}

		//由于不能延申，所以要回退
		int_list.pop_back();																//回去一个
		searched[map[int_list.back()].next_one.back()] = false;		//记录它的也清除一个，不然很可能gg
		map[int_list.back()].next_one.pop_back();							//子节点也删除了，就再也没有这条路径了，否则无限循环
	}
	//end while

	//只剩下了开始的那个first,什么都没有了，还是没有赢

	if (draw)return 1;																		//draw
	else return 0;																			//lose
}

//************************************************************************************************************************************************************************




bool debugging = false;				//************************************************/////		用来测试

int main() {

	int n, m;
	if (debugging)cout << "几个点？";
	cin >> n;
	if (debugging)cout << "几条边？（随便输就行，反正也没用）";
	cin >> m;

	for (int i = 1; i <= n; i++) {//第i 个点,共n 个，1-n

		if (debugging)cout << "第" << i << "个点的出口数量是：";
		int point_number;				//临时值
		cin >> point_number;		//有那么多个出口
		if (debugging)cout << "哦" << endl;
		map_point[i].is_end = (point_number == 0);
		if (debugging)cout << "它们分别为：";
		for (int j = 0; j < point_number; j++)
		{
			int temp;//也是临时值
			cin >> temp;//下一个
			map_point[i].next_one.push_back(temp);//通向下一个
		}
		if (debugging)cout << "	 哦，好吧" << endl << endl;
	}
	//********************************************************完成一部分输入了

	int first_point;//如题
	cin >> first_point;

	//********************************************************搞定所有的输入了


		int win2_draw1_lose0 = is_draw(first_point, map_point);
		if (win2_draw1_lose0 == 2) {
			//已经输出了
		}
		else if (win2_draw1_lose0 ==1) {
			cout << "Draw" << endl;
		}
		else if(win2_draw1_lose0==0){
			cout << "Lose" << endl;
		}
		if (debugging) {
			for (int i = 1; i <= n; i++) {
				cout << i << ":" << map_point[i].win << "," << map_point[i].lose << endl;
			}
		}
		return 0;
}