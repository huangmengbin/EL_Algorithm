#include<bits\stdc++.h>
using namespace std;

struct problem01 {
	short value=1;
	uint16_t step=1;
};


const int MAX = 100000;
unsigned maps[MAX] = {0,1};

int need[90002];
int adds[90002];

bool you_are_debugging = 0;

int main(){//																						main

	int lines;
	int destination;
	cin >> lines >> destination;
	if (destination == 1) {
		cout << 1 << endl;
		return 0;
	}

	for (int i = 0; i < lines; i++)
	{
		cin >> need[i] >> adds[i];
		adds[i] -= need[i];
	}
	
	vector<problem01>conditions;
	vector<problem01>templist;

	problem01 temp1,temp2;

	conditions.push_back(temp1);

	unsigned operation = 0;
	while (operation<10000)//			operation的总数
	{
		operation++;
		unsigned tempsize = conditions.size();
		for (unsigned i = 0; i < tempsize ; i++)
		{
			temp1 = conditions[i];
			for (int j = 0; j < lines; j++)
			{
				temp2 = temp1;
				if (temp2.value >= need[j])
				{
					temp2.value += adds[j];
					temp2.step++;
					if (temp2.value == destination) {//捕捉相等，打断，直接输出
						cout << temp2.step << endl;
						return 0;
					}//end if
					if (maps[temp2.value]==0) {//筛选有意义的操作
						if(you_are_debugging) cout << "(value,step)=" << temp2.value << ',' << temp2.step << endl;
						templist.push_back(temp2);
						maps[temp2.value] = 1;
					}//end if
				}
			}
			conditions= templist;
			templist.clear();//					否则无法去除以前操作过的东东
			if (you_are_debugging)cout << endl;
		}
	}
	cout << -1 << endl;

	return 0;
}