#include<iostream>
#define elif else if
using namespace std;

	int m, n, t;//如题，行数，列数,  自己手下。输入后不改动
	bool map[200][200] = { 0 };//地图，输入后不改动。0表示通路，1表示有对方手下
	short row_end=2, column_end=2;//终点，输入后不改动。2,2 用来测试。实际是第3行 第3列

	short condition[200][200][11];//记录每点状态, 可改动。
									//最后一个记录打败特定数量手下(下标)，来到这点时的最少步数（值）
									 //记得要初始化为一个比较大的数！！！否则它一直不会被修改


	short answer(int i,int j) {//获得最终答案 
		short answer=6666;
		for (int k = 0; k < 11; k++) {
			if (condition[i][j][k]<answer) { answer = condition[i][j][k]; }
		}
		return answer;
	}

	class problem03 {

	public:
		short row=0, column=0;//当前位置点
		short step = 0;//步数
		short used = 0;//打败手下的个数

		void inputMap(void) {//m,n,t输入，地图初始化输入，并设置起点终点
			cin >> m >> n >> t;
			char tem;
			for (int i = 0; i < m; i++)
				for (int j = 0; j < n; j++) {
					cin >> tem;
					if  (tem == '@' || tem == '2') { row = i;		column = j; }
					elif(tem == '+' || tem == '3') { row_end = i;	column_end = j; }
					elif(tem == '#' || tem == '1') { map[i][j] = 1; }
					elif(tem == '*' || tem == '0') { map[i][j] = 0; }//可省略 
				}//测试时可以用 2 3 代表 起点 终点
		}

		bool effective_move(int a) {//看小键盘，8246分别对应上下左右. 并返回一个bool值表示是否为有效移动
			switch (a)
			{
			case 8:	row--; break;//上
			case 4:	column--; break;//左
			case 6:	column++; break;//右
			case 2:	row++; break;//下
			default:	cout << "move-error" << endl;	 break;
			}

			if (row < 0 || column < 0 || row >= m || column >= n) { return 0; }//跑出地图
			else {
				step++;
				used += map[row][column];//等价于if (map[row][column] == 1) { used++; }

				if (used > t) { return 0; }//手下不足
				elif(step < condition[row][column][used]) { 
					condition[row][column][used] = step;
					return 1;
				}
				else { return 0; }

			}
		}//end effective_move

	};

	problem03 hmb[160000];
	problem03 tem[160000];
int main() {
	for(int i=0;i<200;i++)
		for(int j=0;j<200;j++)
			for (int k = 0; k < 11; k++) {
				condition[i][j][k] = 6666;
			}


	hmb[0].inputMap();
	problem03 tem8,tem2,tem4,tem6;
	int before_len = 1;
	int ptr=666;///记得ptr初始化为非零

	bool flat = 0;
	while (flat== 0&&ptr!=0) {///未到终点，且有路可走

		ptr = 0;
		for (int i = 0; i < before_len; i++) {
			tem8 = tem2 = tem4 = tem6 = hmb[i];
			if (tem8.effective_move(8)) { tem[ptr] = tem8; ptr++; }
			if (tem2.effective_move(2)) { tem[ptr] = tem2; ptr++; }
			if (tem4.effective_move(4)) { tem[ptr] = tem4; ptr++; }
			if (tem6.effective_move(6)) { tem[ptr] = tem6; ptr++; }
		}//end for

		for (int i = 0; i < ptr; i++) {
			hmb[i] = tem[i];
			if (tem[i].row == row_end && tem[i].column == column_end) {//到终点
				flat = 1;
				break;
			}
		}

		before_len = ptr;

	}//end while

	if (flat == 0) { cout << -1; }
	elif(flat == 1) { cout << answer(row_end,column_end); }

	return 0;
}
