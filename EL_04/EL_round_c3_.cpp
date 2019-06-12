#include<stdio.h>
#include<iostream>
#include<functional>
#include<algorithm>
#include<math.h>
#include<string>
using namespace std;
#define LL long long

int mid(int a, int b, int c) {//取三个数的中间那个 
	int temp;
	if (a > b) {
		temp = a;
		a = b;
		b = temp;
	}
	if (b > c) {
		temp = b;
		b = c;
		c = temp;
	}
	if (a > b) {
		temp = a;
		a = b;
		b = temp;
	}
	return b;
}

int calculate(int x1, int y1, int x2, int y2) {
	if ((x1 == x2) && (y1 == y2)) { return 0; }
	return abs(x2 - x1) + abs(y2 - y1)-1;

}

void printrow(int y,int small,int big) {
	int temp;
	if (big < small) {
		temp = small;
		small = big;
		big = temp;
	}

	for (int i = small + 1; i < big; i++) {
		cout << i << " " << y<<endl;
	}

}
void printcolumn(int x, int small, int big) {
	int temp;
	if (big < small) {
		temp = small;
		small = big;
		big = temp;
	}

	for (int i = small + 1; i < big; i++) {
		cout << x << " " << i<<endl;
	}


}
void printroad(int x1, int y1, int x2, int y2) {

	if ((x1 == x2) && (y1 == y2)) {
	}
	else if (x1 == x2) {
		printcolumn(x1, y1, y2);
	}
	else if (y1 == y2) {
		printrow(y1, x1, x2);
	}
	else {
		printcolumn(x1, y1, y2);
		cout << x1 << " " << y2<<endl;
		printrow(y2, x1, x2);
	}
}

int main() {

	int xa, xb, xc, ya, yb, yc;



	cin >> xa >> ya >> xb >> yb >> xc >> yc;

	int tempx, tempy;

	tempx = mid(xa, xb, xc);//中间点 

	tempy = mid(ya, yb, yc);

	//cout << tempx <<","<< tempy << endl;

	int result = 3;

	if ((tempx == xa) && (tempy == ya)) {
		
		result += calculate(xa, ya, xb, yb);
		result += calculate(xa, ya, xc, yc );
		cout << result << endl;

		cout << xa << " " << ya << endl;
		cout << xb << " " << yb << endl;
		cout << xc << " " << yc << endl;

		printroad(xa, ya, xb, yb);
		printroad(xa, ya, xc, yc);

	}
	else 	if ((tempx == xb) && (tempy == yb)) {

		result += calculate(xb, yb, xa, ya);
		result += calculate(xb, yb, xc, yc);
		cout << result << endl;

		cout << xa << " " << ya <<endl;
		cout << xb << " " << yb << endl;
		cout << xc << " " << yc << endl;

		printroad(xb, yb, xa, ya);
		printroad(xb, yb, xc, yc);
	}
	else 	if ((tempx == xc) && (tempy == yc)) {//前三个几乎是复制粘贴的 

		result += calculate(xc, yc, xb, yb);
		result += calculate(xc, yc, xa, ya);
		cout << result << endl;

		cout << xa << " " << ya << endl;
		cout << xb << " " << yb << endl;
		cout << xc << " " << yc << endl;

		printroad(xc, yc, xb, yb);
		printroad(xc, yc, xa, ya);
	}
	else {
		result += calculate(tempx, tempy, xa, ya);
		result += calculate(tempx, tempy, xb, yb);
		result += calculate(tempx, tempy, xc, yc);
		result += 1;
		cout << result << endl;

		cout << xa << " " << ya << endl;
		cout << xb << " " << yb << endl;
		cout << xc << " " << yc << endl;

		cout << tempx << " " << tempy << endl;

		printroad(tempx, tempy, xa, ya);
		printroad(tempx, tempy, xb, yb);
		printroad(tempx, tempy, xc, yc);
	}


	return 0;
}
