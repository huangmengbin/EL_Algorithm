#include<iostream>
#include<stdio.h>
#include<functional>
#define elif else if
const int MAX_STEP = 27;
using namespace std;

class problem2 {
private:
	uint8_t clock[3][3] = { 0 };//相当于8位char，记录时钟状态

public:
	short int len_step = 0;//记录总操作数，即step[]长度
	uint8_t step[MAX_STEP] = { 0 };//相当于8位char，记录操作

	void input(void) {//接受输入
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				cin >> clock[i][j];
				clock[i][j] -= 48;	//额
			}
		}
	}
	void output(void) {//输出时钟
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				cout << int(this->clock[i][j]) << ' ';//额
			}
			cout << endl;
		}
		cout << endl;
	}
	void outputStep(void) {//输出执行过的操作
		cout << (int)step[0];//
		for (int i = 1; i < len_step; i++) {
			cout << ' ' << int(step[i]);//
		}
		//cout << endl;//
	}
	bool isRedundance(void) {//step[]长度大于3，且最后4个相等时，返回1
		int hmb = len_step;
		if (hmb >= 4)
			return (step[hmb - 1] == step[hmb - 2] && step[hmb - 2] == step[hmb - 3] && step[hmb - 3] == step[hmb - 4]);
		else return 0;
	}
	bool isZero(void) {//clock[][]全为零时，返回1
		bool flat = 1;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				flat = flat & (!(clock[i][j]));
		return flat;
	}

	void setClocks(int operation) {//修改clock的值，并记录于step[]中

		if (operation > 0) {
			step[len_step] = operation;
			len_step++;
			if (len_step > MAX_STEP)cout << "step-error :" << step << endl;
		}					//记录操作

		switch (operation)//修改clock[][]
		{
		case 0:break;
		case 1:++clock[0][0] %= 4; ++clock[0][1] %= 4; ++clock[1][0] %= 4; ++clock[1][1] %= 4; break;
		case 2:++clock[0][0] %= 4; ++clock[0][1] %= 4; ++clock[0][2] %= 4; break;
		case 3:++clock[0][1] %= 4; ++clock[0][2] %= 4; ++clock[1][1] %= 4; ++clock[1][2] %= 4; break;
		case 4:++clock[0][0] %= 4; ++clock[1][0] %= 4; ++clock[2][0] %= 4; break;
		case 5:++clock[0][1] %= 4; ++clock[1][0] %= 4; ++clock[1][1] %= 4; ++clock[1][2] %= 4; ++clock[2][1] %= 4; break;
		case 6:++clock[0][2] %= 4; ++clock[1][2] %= 4; ++clock[2][2] %= 4; break;
		case 7:++clock[1][0] %= 4; ++clock[1][1] %= 4; ++clock[2][0] %= 4; ++clock[2][1] %= 4; break;
		case 8:++clock[2][0] %= 4; ++clock[2][1] %= 4; ++clock[2][2] %= 4; break;
		case 9:++clock[1][1] %= 4; ++clock[1][2] %= 4; ++clock[2][1] %= 4; ++clock[2][2] %= 4; break;
		default:cout << "switch-error	:" << operation << endl;
		}
	}

	bool operator==(problem2 &i) {//重载==，相当于clock[][]完全一致，后面没用到
		return (clock[0][0] == i.clock[0][0] && clock[0][1] == i.clock[0][1] && clock[0][2] == i.clock[0][2] && clock[1][0] == i.clock[1][0] && clock[1][1] == i.clock[1][1] && clock[1][2] == i.clock[1][2] && clock[2][0] == i.clock[2][0] && clock[2][1] == i.clock[2][1] && clock[2][2] == i.clock[2][2]);
	}
};


problem2 clocks[262144];//防止main不够

int main() {
	clocks[0].input();
	int total_len = 1;
	int before_len = 0;
	int ptr = 1;
	bool flat = 0;

	while (!clocks[0].isZero()) {

		for (int i = before_len; i < total_len; i++) {
			for (int j = ((clocks[i].len_step) == 0) ? 1 : clocks[i].step[(clocks[i].len_step) - 1]; j <= 9; j++) {
				clocks[ptr] = clocks[i];
				clocks[ptr].setClocks(j);

				{
					//判断新生成的是否重复，即是否有4个相同的操作,是否有必要添加入列
					if (!clocks[ptr].isRedundance()) {
						ptr++;
						//cout << "1 :";	
						//cout << "     len_step=" << clocks[ptr].len_step << "        ";
						//clocks[ptr].outputStep();
					}
					//else { cout << "0 :"; cout << "     len_step=" << clocks[ptr].len_step << "        "; clocks[ptr].outputStep(); }
				}

				{
					//判断是否完成，完成则输出再跳出
					if (clocks[ptr - 1].isZero()) {
						clocks[ptr - 1].outputStep();
						//cout << total_len << "~" << ptr << endl;
						flat = 1;
					}
				}

				if (flat) { break; }
			}
			if (flat) { break; }
		}
		if (flat) { break; }
		before_len = total_len;
		total_len = ptr;

		//cout << before_len << '-' << ptr << endl;
	}

	/*
	cout << endl;
	problem2 hmb;
	for (int i = 1; i <= 9;i++)hmb.setClocks(i);
	if(!hmb.isRedundance())hmb.output();
	if(!hmb.isZero())hmb.outputStep();
	*/

	return 0;
}