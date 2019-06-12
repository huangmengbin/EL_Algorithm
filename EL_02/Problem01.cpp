#include<iostream>
using namespace std;

inline unsigned long long max(unsigned long long a, unsigned long long b) {
	return (((a) > (b)) ? (a) : (b));
}
inline unsigned long long min(unsigned long long a, unsigned  long long b) {
	return (((a) > (b)) ? (b) : (a));
}

bool debug = 1;

int main() {
	//下面这段可以不用看
	unsigned long long fasttime, slowtime, needtime,addtime;
	cin >> fasttime >> slowtime >> needtime;

	unsigned long long temp = fasttime/slowtime;
	temp = slowtime * temp;
	if (temp < fasttime) {
		slowtime = temp + slowtime;
		addtime = slowtime;
		slowtime = addtime - fasttime;
	}
	else {
		slowtime = temp;
		addtime = slowtime;
		slowtime = addtime - fasttime;
	}
	//以上这段代码可不看

	if(debug)cout << fasttime << ' ' << slowtime << ' ' << addtime <<' '<<needtime<< endl;

	fasttime *= 4;
	slowtime *= 4;
	addtime *= 4;
	needtime *= 4;

	unsigned long long looptime = fasttime + slowtime / 2;
	unsigned long long time = needtime/ looptime;//time 是 次数
	unsigned long long result = time*addtime;							//结果
	unsigned long long lefttime = needtime - time * looptime;//剩下的时间（保证不超过looptime）

	result += ( min(lefttime, fasttime));

	if (lefttime > fasttime) {
		result += (lefttime - fasttime) / 2;
	}

	cout << result/4;
	
	switch (result & 3) {
		case 0:cout << ".000000000"<<endl; break;
		case 1:cout << ".250000000" << endl;break;
		case 2:cout << ".500000000"   << endl; break;
		case 3:cout << ".750000000" << endl; break;
	}
	return 0;
}