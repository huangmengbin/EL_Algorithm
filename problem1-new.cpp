#include<iostream>
#define elif else if
using namespace std;
int i = 0;//È«¾Ö±äÁ¿

bool solve(char* expression) {

	bool value;
	bool tem;
	bool Not = 0;
	bool And = 0;
	bool Or = 0;

	//printf("%s\n", expression);
	while (expression[i] != '\0'&&expression[i] != ')') {
		cout << "expression[" << i << "]= : " << expression[i] << endl;

		switch (expression[i]) {
		case ' ':						break;
		case '!':		Not = 1;	 break;
		case '&':	And = 1;	 break;
		case '|':		Or = 1;		break;
		default:
			break;
		}

		if (expression[i] == 'V' || expression[i] == 'F' || expression[i] == '(') {//Óö¼û×óÀ¨ºÅµÝ¹é
			if (expression[i] == 'V') { tem = 1 ^ Not; }
			elif(expression[i] == 'F') { tem = 0 ^ Not; }
			elif(expression[i] == '(') { i++; tem = Not ^ solve(expression); }//Óö¼û×óÀ¨ºÅµÝ¹é//
			Not = 0;

			if (And == 0 && Or == 0) {
				value = tem;
			}
			elif(And == 1) { 
				value = value & tem;
				And = 0;
			}
			elif(Or == 1) {
				value = value | tem;
				Or = 0;
			}

		}
		
		i++;
	}
	cout <<"expression["<<i<<"]= : "<< expression[i] << endl;
	return value;
}
int main() {
	char expression[1002];
	gets_s(expression,1001);
	//cin.get(expression, 1001);
	cout <<"expression= : "<<expression<< endl;
	cout << endl;
	cout <<"Expression "<<1<<": "<<solve(expression) << endl;
	return 0;
}
