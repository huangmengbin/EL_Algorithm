#include<iostream>
#include<vector>
using namespace std;


class Map {
public:
	vector<int>next_one;//��ǰ��� ���� ��һ��   �������������map[int_list.back()].next_one.back()]  �����õ�������
	bool win;					//�Ҽǵú���Ĭ��Ϊfalse??
	bool lose;
	bool is_end;

	Map(){
		win = false;
		lose = false;
		is_end = false;
	}
};



//ȫ�ֱ�������
Map map_point[200007];
//

//���ڿռ����⣬���ò���ȫ����

vector<int>int_list;										//��ǰ������
bool searched[200007];								//search[0]���ϣ���¼��ǰ������  ��������Щ����  �о��е���һ���������
//
//

int is_draw(int first, Map* map) {			//////����Ӻ����ǣ�������������������Ҳ���ѽ����������
																		//������ò�ƺ�Map����ز���д������Ӧ��Ҳ�ǿ��Ե�
	bool draw = false;										//��¼�Ƿ��ѭ��

	int_list.push_back(first);								//�ŵ�һ����ȥ

	while (int_list.size() != 1 || map[int_list.back()].next_one.size() != 0)//ֻҪ���Ȳ���1�����߻�����������,������ѭ��
	{
		while (map[int_list.back()].next_one.size() != 0)							//������͡������ٽ���ѭ��
		{

			searched[int_list.back()] = true;												//��¼
			if ((int_list.size() & 1) == 0) {													//����Ϊż�������ܿ���Ӯ
				map[int_list.back()].win = true;											//������map��win
			}
			else {
				map[int_list.back()].lose = true;											//������
			}

			int_list.push_back(map[int_list.back()].next_one.back());			//��һ��Ҳ�ƽ�ȥ


			if (searched[int_list.back()] == true) {										//�µ��������ǰ�����Ѿ����ڹ���
				draw = true;																		//��

				if (((int_list.size() & 1) == 0) && (map[int_list.back()].win == true)) {			//��ǰ�Ѿ��ѹ�����״̬��
					int_list.pop_back();
					map[int_list.back()].next_one.pop_back();
				}
				else if (((int_list.size() & 1) == 1) && (map[int_list.back()].lose == true)) {	//��ǰ�Ѿ��ѹ�����״̬��
					int_list.pop_back();
					map[int_list.back()].next_one.pop_back();
				}

			}//end if

		}//end �ڲ� while

		//���������ˣ���

		if ((int_list.size() & 1) == 0 && (map[int_list.back()].is_end)) {//������˫�����Ǿ�Ӯ��
			cout << "Win" << endl;
			for (unsigned i = 0; i < int_list.size(); i++) {
				cout << int_list[i] << " ";
			}
			cout << endl;
			return 2;																			//win
		}

		//���ڲ������꣬����Ҫ����
		int_list.pop_back();																//��ȥһ��
		searched[map[int_list.back()].next_one.back()] = false;		//��¼����Ҳ���һ������Ȼ�ܿ���gg
		map[int_list.back()].next_one.pop_back();							//�ӽڵ�Ҳɾ���ˣ�����Ҳû������·���ˣ���������ѭ��
	}
	//end while

	//ֻʣ���˿�ʼ���Ǹ�first,ʲô��û���ˣ�����û��Ӯ

	if (draw)return 1;																		//draw
	else return 0;																			//lose
}

//************************************************************************************************************************************************************************




bool debugging = false;				//************************************************/////		��������

int main() {

	int n, m;
	if (debugging)cout << "�����㣿";
	cin >> n;
	if (debugging)cout << "�����ߣ����������У�����Ҳû�ã�";
	cin >> m;

	for (int i = 1; i <= n; i++) {//��i ����,��n ����1-n

		if (debugging)cout << "��" << i << "����ĳ��������ǣ�";
		int point_number;				//��ʱֵ
		cin >> point_number;		//����ô�������
		if (debugging)cout << "Ŷ" << endl;
		map_point[i].is_end = (point_number == 0);
		if (debugging)cout << "���Ƿֱ�Ϊ��";
		for (int j = 0; j < point_number; j++)
		{
			int temp;//Ҳ����ʱֵ
			cin >> temp;//��һ��
			map_point[i].next_one.push_back(temp);//ͨ����һ��
		}
		if (debugging)cout << "	 Ŷ���ð�" << endl << endl;
	}
	//********************************************************���һ����������

	int first_point;//����
	cin >> first_point;

	//********************************************************�㶨���е�������


		int win2_draw1_lose0 = is_draw(first_point, map_point);
		if (win2_draw1_lose0 == 2) {
			//�Ѿ������
		}
		else if (win2_draw1_lose0 ==1) {
			cout << "Draw" << endl;
		}
		else if(win2_draw1_lose0==0){
			cout << "Lose" << endl;
		}
		if (debugging) {
			for (int i = 1; i <= n; i++) {
				cout << i << ":" << map_point[i].win << "," << map_point[i].lose << endl;
			}
		}
		return 0;
}