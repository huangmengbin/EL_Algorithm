#include<stdio.h>
#include<iostream>
#include<functional>
#include<algorithm>
#include<math.h>
#include<string>
#include<string.h>

#define elif else if
using namespace std;
/*
所用 string 操作有：
substr,用法为myString=yourString.substr(起始下标i,长度l);返回截取的那一段字符串
后面那个是长度而不是终点下标i

+连接；==判断相等

以及.length()	.pop_back()删除末尾	

.insert();	？？？

*/



class problem03 {
public:
	bool same = 0;
	string integer;
	string nonLoopDecimal;
	string LoopDecimal;

	void input(string yourString) {
		//bool dot = 0;
		int i = 0;//下标
		int j;//记录长度
		int iii ;//临时存之前的下标

		for (i = 0;		 yourString[i] != '\0'&&yourString[i] != '.'		; i++) {}
		if(i>0)integer=yourString.substr(0, i);
		iii= i;

		for (j=0;		yourString[i] != '\0'&&yourString[i] != '('		; i++,j++) {}
		if(i>iii)nonLoopDecimal = yourString.substr(iii+ 1, j-1);
		iii = i;
		
		for (j=0;		yourString[i] != '\0'&&yourString[i] != ')'		; i++,j++) {}
		if(i>iii)LoopDecimal = yourString.substr(iii+ 1, j-1);
		return;
	}


	void simplifyLoop() {//(12341234)-->(1234);	(99999)-->(9);	(00000)-->(0)-->();

		string sub;
		for (unsigned i = 1; i<LoopDecimal.length(); i++) {
			if (LoopDecimal.length() %i == 0) {
				sub=LoopDecimal.substr(0, i );
				//cout << "subString="<<sub<<endl;
				int tms = LoopDecimal.length() / i	 -1;

				bool isLoopSub = 1;
				for (int j = 1; j <= tms; j++) {
					if (sub != LoopDecimal.substr(i*j, i)) {
						isLoopSub = 0;
						break;
					}
				}

				if (isLoopSub == 1) {
					LoopDecimal = sub;
					//cout << "subString=" << sub << endl;
					break;
				}
			}
		}

		if (LoopDecimal == "0") {
			LoopDecimal = "";
		}
		return;
	}

	void simplifyNonloop() {//0.01234(1234)-->0.0123(4123)-->0.012(3412)-->0.01(2341)-->0.0(1234);	9.00()-->9.();		9.00(9)不变;
		while (LoopDecimal.length()>0 && nonLoopDecimal.length() > 0 && (nonLoopDecimal[nonLoopDecimal.length()-1] == LoopDecimal[LoopDecimal.length()-1]) ) {
			LoopDecimal = nonLoopDecimal[nonLoopDecimal.length() - 1] + LoopDecimal;//字符串连接？？？
			nonLoopDecimal.pop_back();
			LoopDecimal.pop_back();
		}

		if (LoopDecimal=="") {
			bool empty = 1;
			for (unsigned i = 0; i < nonLoopDecimal.length(); i++) {
				if (nonLoopDecimal[i] != '0') {
					empty = 0;
				}
			}
			if(empty)nonLoopDecimal = "";
		}
		return;
	}

	void upperBefore() {//0.6(9)-->0.7();	99.(9)-->100.();	
		if ((LoopDecimal.compare("9")) == 0) {
			if (nonLoopDecimal.length() == 0) {
				integer[integer.length() - 1] += 1;

				for (int i = integer.length() - 1; i >=1 ; i--) {
					if (integer[i] > '9') {
						integer[i] = '0';
						integer[i - 1] += 1;
					}
				}
				if (integer[0] > '9') {
					integer[0] = '0';
					integer = "1" + integer;
				}
				LoopDecimal = "";
				return;
			}
			else {
				nonLoopDecimal[nonLoopDecimal.length() - 1] += 1;
				LoopDecimal = "";
			}
		}
	}

	bool operator == (problem03 &i) {
		return ((integer.compare( i.integer) == 0) && (LoopDecimal.compare(i.LoopDecimal) == 0) && (nonLoopDecimal.compare(i.nonLoopDecimal) == 0));
	}
};


problem03 myObject[300];
int main() {

	bool you_are_testing_now = 1;

	int numb;//行
	cin >> numb;//行

	string temp ;
	for (int i = 0; i < numb; i++) {
		cin >> temp;

		myObject[i].input(temp);
		if (you_are_testing_now) {
			cout <<"integer: "<<myObject[i].integer << ";\t decimal: " << myObject[i].nonLoopDecimal << " and "<< myObject[i].LoopDecimal << endl;
		}

		myObject[i].simplifyLoop();
		if (you_are_testing_now) {
			cout << myObject[i].integer << '.' << myObject[i].nonLoopDecimal << '(' << myObject[i].LoopDecimal << ')' << endl;
		}		

		myObject[i].simplifyNonloop();
		if (you_are_testing_now) {
			cout << myObject[i].integer << '.' << myObject[i].nonLoopDecimal << '(' << myObject[i].LoopDecimal << ')' << endl;
		}		

		myObject[i].upperBefore();
		if (you_are_testing_now) {
			cout << myObject[i].integer << '.' << myObject[i].nonLoopDecimal << '(' << myObject[i].LoopDecimal << ')' << endl;
		}

	}//end for

	int answer = 0;
	for (int i = 0; i < numb; i++) {
		for (int j = i + 1; j < numb; j++) {
			if (myObject[i] == myObject[j] ){
				myObject[j].same = 1;
			}
		}
	}//先“删除”重复项

	//再统计
	for (int i = 0; i < numb; i++) {
			if (myObject[i].same == 0) {
				answer++;
			}	
	}

	if (you_are_testing_now) { cout << endl << "answer=" << answer; }
	else { cout << answer << endl; }

	return 0;
}
