#include<iostream>
#include<string>
#include<vector>
using namespace std;
struct city_group {
	string a;
	string b;
	int lapse;
};

int calculate_delta(string a, string b)
{
	int time1, time2;
	int hour1, hour2;
	int min1, min2;
	hour1 = (a[0] - '0') * 10 + (a[1] - '0');
	hour2 = (b[0] - '0') * 10 + (b[1] - '0');
	min1 = (a[3] - '0') * 10 + (a[4] - '0');
	min2 = (b[3] - '0') * 10 + (b[4] - '0');
	time1 = 3600 * hour1 + 60 * min1;
	time2 = 3600 * hour2 + 60 * min2;
	return time1 - time2;
}

int trans_time(string time)
{
	return ((time[0] - '0') * 10 + time[1] - '0') * 3600 + (time[3] - '0') * 10 + time[4] - '0';
}

void copy_new_group(vector<city_group>& newone, vector<city_group> origin)
{
	vector<city_group>::iterator it1 = origin.begin();
	vector<city_group>::iterator it2 = origin.end();
	for (; it1 != it2; it1++)
		newone.push_back(*it1);
}

int main()
{
	string origin;//��¼ԭʼ���е�����
	cin >> origin;//����ԭʼ����
	vector<city_group> all_info;//��¼�ܵĶ���
	vector<char> time;//��¼ԭʼ���е�ʱ������

	vector<vector<city_group>> all_relation;//��¼��origin_city����������·��


	getchar();
	string str;
	getline(cin, str);//����һ��ʱ����ٷָ�
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] != ' ')
			time.push_back(str[i]);
	}

	int total;
	cin >> total;//��¼���й�ϵ�Ķ���

	string temp_a;
	string temp_b;
	for (int i = 0; i < total; i++)
	{
		city_group new_group;
		cin >> new_group.a;
		cin >> temp_a;
		cin >> new_group.b;
		cin >> temp_b;
		new_group.lapse = calculate_delta(temp_a, temp_b);
		all_info.push_back(new_group);
	}

	string current_city;//��¼���ڵĳ���
	cin >> current_city;

	string current_time;//��¼���ڳ��е�ʱ��
	cin >> current_time;

	bool is_stop = false;
	int total_delta = 0;
	string front;//��¼��һ��Ҫ��Ѱ�ĵط�
	front = current_city;

	int a = 0;
	vector<city_group>::iterator tail = all_info.end();
	vector<city_group>::iterator it1 = all_info.begin();
	int all[1000];//��¼��Щ����current_city��λ��
	
	//�ҵ�һ��·��current_city����������ܹ�����origint_city
	int count=0;
	for (; it1 != tail; it1++)
	{
		count++;
		if (it1->a == origin || it1->b == origin)
		{
			all[a] = count;
			a++;
		}
	}

	vector<city_group> temp;
	bool got_front = false;
	for (int i = 0; i < a; i++)
	{
		copy_new_group(temp, all_info);
		
		it1 = temp.begin();
		for (int i = 0; i < all[i]; i++)
			it1++;
		total_delta = 0;
		do
		{
			tail = temp.end();
			it1 = temp.begin();
			while (it1->a != front && it1->b != front && it1 != tail)
			{
				it1++;
			}

			if (it1->a == front)
			{
				got_front = true;
				front = it1->b;
				total_delta = total_delta + it1->lapse;
				temp.erase(it1);
			}
			else if (it1->b == front)
			{
				got_front = true;
				front = it1->a;
				total_delta = total_delta - it1->lapse;
				temp.erase(it1);
			}
			else
				got_front = false;

			if (front == origin)
				is_stop = true;

			if (got_front == false)
				break;
		} while (is_stop == false);
		if (is_stop == true)
			break;
	}


	int hour_delta = abs(total_delta);

	int final_total = (hour_delta + trans_time(current_time)) / 3600;

	final_total = final_total % time.size();
		
	cout << time[time.size() - final_total];
	
}