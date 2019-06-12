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
	//������ο��Բ��ÿ�
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
	//������δ���ɲ���

	if(debug)cout << fasttime << ' ' << slowtime << ' ' << addtime <<' '<<needtime<< endl;

	fasttime *= 4;
	slowtime *= 4;
	addtime *= 4;
	needtime *= 4;

	unsigned long long looptime = fasttime + slowtime / 2;
	unsigned long long time = needtime/ looptime;//time �� ����
	unsigned long long result = time*addtime;							//���
	unsigned long long lefttime = needtime - time * looptime;//ʣ�µ�ʱ�䣨��֤������looptime��

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