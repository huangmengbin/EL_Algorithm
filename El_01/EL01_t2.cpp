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
	string origin;//记录原始城市的名字
	cin >> origin;//输入原始城市
	vector<city_group> all_info;//记录总的对数
	vector<char> time;//记录原始城市的时间名字

	vector<vector<city_group>> all_relation;//记录从origin_city出发的所有路径


	getchar();
	string str;
	getline(cin, str);//读入一行时间表再分割
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] != ' ')
			time.push_back(str[i]);
	}

	int total;
	cin >> total;//记录所有关系的对数

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

	string current_city;//记录现在的城市
	cin >> current_city;

	string current_time;//记录现在城市的时间
	cin >> current_time;

	bool is_stop = false;
	int total_delta = 0;
	string front;//记录下一个要搜寻的地方
	front = current_city;

	int a = 0;
	vector<city_group>::iterator tail = all_info.end();
	vector<city_group>::iterator it1 = all_info.begin();
	int all[1000];//记录那些存在current_city的位置
	
	//找到一条路由current_city伸出来并且能够到达origint_city
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