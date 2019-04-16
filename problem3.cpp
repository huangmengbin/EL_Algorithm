#include<iostream>
#define elif else if
using namespace std;

	int m, n, t;//���⣬����������,  �Լ����¡�����󲻸Ķ�
	bool map[200][200] = { 0 };//��ͼ������󲻸Ķ���0��ʾͨ·��1��ʾ�жԷ�����
	short row_end=2, column_end=2;//�յ㣬����󲻸Ķ���2,2 �������ԡ�ʵ���ǵ�3�� ��3��

	short condition[200][200][11];//��¼ÿ��״̬, �ɸĶ���
									//���һ����¼����ض���������(�±�)���������ʱ�����ٲ�����ֵ��
									 //�ǵ�Ҫ��ʼ��Ϊһ���Ƚϴ����������������һֱ���ᱻ�޸�


	short answer(int i,int j) {//������մ� 
		short answer=6666;
		for (int k = 0; k < 11; k++) {
			if (condition[i][j][k]<answer) { answer = condition[i][j][k]; }
		}
		return answer;
	}

	class problem03 {

	public:
		short row=0, column=0;//��ǰλ�õ�
		short step = 0;//����
		short used = 0;//������µĸ���

		void inputMap(void) {//m,n,t���룬��ͼ��ʼ�����룬����������յ�
			cin >> m >> n >> t;
			char tem;
			for (int i = 0; i < m; i++)
				for (int j = 0; j < n; j++) {
					cin >> tem;
					if  (tem == '@' || tem == '2') { row = i;		column = j; }
					elif(tem == '+' || tem == '3') { row_end = i;	column_end = j; }
					elif(tem == '#' || tem == '1') { map[i][j] = 1; }
					elif(tem == '*' || tem == '0') { map[i][j] = 0; }//��ʡ�� 
				}//����ʱ������ 2 3 ���� ��� �յ�
		}

		bool effective_move(int a) {//��С���̣�8246�ֱ��Ӧ��������. ������һ��boolֵ��ʾ�Ƿ�Ϊ��Ч�ƶ�
			switch (a)
			{
			case 8:	row--; break;//��
			case 4:	column--; break;//��
			case 6:	column++; break;//��
			case 2:	row++; break;//��
			default:	cout << "move-error" << endl;	 break;
			}

			if (row < 0 || column < 0 || row >= m || column >= n) { return 0; }//�ܳ���ͼ
			else {
				step++;
				used += map[row][column];//�ȼ���if (map[row][column] == 1) { used++; }

				if (used > t) { return 0; }//���²���
				elif(step < condition[row][column][used]) { 
					condition[row][column][used] = step;
					return 1;
				}
				else { return 0; }

			}
		}//end effective_move

	};

	problem03 hmb[160000];
	problem03 tem[160000];
int main() {
	for(int i=0;i<200;i++)
		for(int j=0;j<200;j++)
			for (int k = 0; k < 11; k++) {
				condition[i][j][k] = 6666;
			}


	hmb[0].inputMap();
	problem03 tem8,tem2,tem4,tem6;
	int before_len = 1;
	int ptr=666;///�ǵ�ptr��ʼ��Ϊ����

	bool flat = 0;
	while (flat== 0&&ptr!=0) {///δ���յ㣬����·����

		ptr = 0;
		for (int i = 0; i < before_len; i++) {
			tem8 = tem2 = tem4 = tem6 = hmb[i];
			if (tem8.effective_move(8)) { tem[ptr] = tem8; ptr++; }
			if (tem2.effective_move(2)) { tem[ptr] = tem2; ptr++; }
			if (tem4.effective_move(4)) { tem[ptr] = tem4; ptr++; }
			if (tem6.effective_move(6)) { tem[ptr] = tem6; ptr++; }
		}//end for

		for (int i = 0; i < ptr; i++) {
			hmb[i] = tem[i];
			if (tem[i].row == row_end && tem[i].column == column_end) {//���յ�
				flat = 1;
				break;
			}
		}

		before_len = ptr;

	}//end while

	if (flat == 0) { cout << -1; }
	elif(flat == 1) { cout << answer(row_end,column_end); }

	return 0;
}
