#include<iostream>
#define elif else if
using namespace std;

bool solve(char* expression) {

	bool value;
	bool tem;
	bool Not = 0;
	bool And = 0;
	bool Or = 0;
	int i = 0;
	//printf("%s\n", expression);
	while (expression[i] != '\0'&&expression[i] != ')') {
		switch (expression[i]){
			case ' ':						break;
			case '!':		Not = 1;	 break;
			case '&':	And = 1;	 break;
			case '|':		Or = 1;		break;
		default:
			break;
		}

		if(expression[i] == 'V' || expression[i] == 'F'||expression[i]=='(') {//Óö¼û×óÀ¨ºÅµÝ¹é
			if (expression[i] == 'V') { tem = 1 ^ Not; }
			elif(expression[i] == 'F') { tem = 0 ^ Not; }
			elif(expression[i] == '(') { tem = Not ^ solve(&expression[i+1]); }//Óö¼û×óÀ¨ºÅµÝ¹é
			Not = 0;
			if (And == 0 && Or == 0) {
				value = tem;
			}
			elif(And == 1) { value = value & tem; And = 0; }
			elif(Or == 1) { value = value | tem; Or = 0; }
		}
		expression[i] = ' ';//Ïàµ±ÓÚÉ¾³ý
		i++;
	}
	expression[i] = ' ';
	return value;
}
int main() {
	char expression[1000];
	cin.get(expression, 999);
	//cout << expression<< endl;
	cout << solve(expression) << endl;
	return 0;
}