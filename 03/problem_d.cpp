#include<functional>
#include<algorithm>
#include<vector>
#include<string>
#include<math.h>
#include<iostream>
#include<vector>
#include<stdlib.h>
#include<stdio.h>

using namespace std;
#define LL long long
#define elif else if

bool debug = false;

int main() {
	//int a[] = { 1,1,2,3,4,4,6,6,4,4,5,5,7,6, };
	int n;
	int equal = 0;
	cin >> n;
	int c[5004];
	for (int i = 0; i < n; i++) {
		cin >> c[i];
		if (i > 0) { if (c[i] == c[i - 1]) { equal++; } }
	}

	unique(c, c + n);
	n = n - equal;

	if (n == 1) {//**************************************************
		cout << 0 << endl;
		return 0;
	}

	if (debug) {
		cout << endl;
		for (int i = 0; i < n; i++) {
			cout << c[i] << " ";
		}
		cout << endl << endl;
	}
	//////////////////////insert
	equal = 0;
	int maxx = 0;

	for (int i = 0; i < n; i++) {
		//a[i]
	}

	return 0;
}
/*
int hmb[5004];
for (int i = 0; i < n; i++) {
	hmb[i] = c[i];
}
sort(hmb, hmb + n);
if (debug){
	for (int i = 0; i < n; i++) {
		cout << hmb[i] << " ";
	}
	cout << endl << endl;
}

equal = 0;
int maxx = 0;
for (int i = 1; i < n; i++) {
	if (hmb[i] == hmb[i - 1]) {
		equal++;
	}
	else {
		equal = 0;
	}
	maxx = max(maxx, equal);
}
if (debug) {
	cout << "n=" << n<<endl;
	cout << "max=" << maxx << endl << endl;
}
cout << n - maxx - 1<<endl;
*/