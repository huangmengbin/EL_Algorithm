#include<stdio.h>
#include<iostream>
#include<functional>
#include<algorithm>
#include<math.h>
#include<string>
#define elif else if
using namespace std;

int numb;


class problem03 {
public:
	bool same = 0;
	char integer[40] = { '\0' };
	int sizeOfInteger;
	char before[80]= { '\0' };
	int sizeOfBefore;
	char inbox[80]= { '\0' };
	int sizeOfInbox;

	void input(string temp) {
		//bool dot = 0;
		int i = 0;//读入下标
		int j = 0;
		for (i = 0; temp[i] != '\0'&&temp[i] != '.'; i++) {
			integer[i] = temp[i];
		}
		sizeOfInteger = i;
		for ( j = 0; temp[i] != '\0'&&temp[i] != '('		; i++) {
			if (temp[i] >= '0'&&temp[i] <= '9') { before[j] = temp[i]; j++; }
		}
		sizeOfBefore= j;
		for (j = 0; temp[i] != '\0'&&temp[i] != ')'		; i++) {
			if (temp[i] >= '0'&&temp[i] <= '9') { inbox[j] = temp[i]; j++; }
		}
		sizeOfInbox = j;
		return;
	}


	void briefInbox() {
		/*
		char subStr[300];
		for (int i = 1; i < sizeOfInbox; i++) {
			if (sizeOfInbox%i == 0) {
				subStr = copy(inbox, 0, i );
				printf("%s\n", subStr);
				int tms = sizeOfInbox / i;
				bool flag = 1;
				for (int j = 2; j < tms; j++) {
					if (strcmp(copy(j*i-i, i, inbox),subStr ) != 0) {
						flag = 0;
						break;
					}
				}

			}
			if (!flag) continue;
		}*/
		return;
	}

	void changeBefore() {

		return;
	}
	void upperBefore() {
		if (strcmp(inbox, "9") == 0) {
			if (sizeOfBefore == 0) {
				return;
			}
			else {
				before[sizeOfBefore - 1] += 1;
			}
		}
	}

	bool operator == (problem03 &i) {
		return ((strcmp(integer, i.integer) == 0) && (strcmp(before, i.before) == 0) && (strcmp(inbox, i.inbox) == 0));
	}
};
problem03 myObject[300];
int main() {

	cin >> numb;//行

	string temp ;
	for (int i = 0; i < numb; i++) {
		cin >> temp;
		myObject[i].input(temp);
/*
		cout << myObject[i].integer<<endl;
		cout << myObject[i].before << endl;
		cout << myObject[i].inbox << endl;
		*/
		myObject[i].briefInbox();
		myObject[i].changeBefore();
		myObject[i].upperBefore();

		cout << myObject[i].before << endl;
	}
	int answer = 0;
	for (int i = 0; i < numb; i++) {
		for (int j = i + 1; j < numb; j++) {
			if (myObject[i] == myObject[j] && myObject[i].same ==0 &&myObject[i].same ==0){
				answer++;
				myObject[i].same = 1;
				myObject[j].same = 1;
			}
		}

	}
	cout << answer;

	return 0;
}
