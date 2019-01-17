/*************************************************************************
	> File Name: test.cpp
	> Author: Liu Shengxi 
	> Mail: 13689209566@163.com
	> Created Time: 2018年06月11日 星期一 11时40分25秒
 ************************************************************************/

// #include<iostream>
// #include<deque>
// using namespace std;
// initializer_list<int> lst;
// int main(void) {
// 	deque<int> dq ;
// 	int tmp;
// 	for(int i = 0 ;i< 20 ;i++){
// 		cin >> tmp ;
// 		dq.push_back(tmp);
// 	}
// 	deque<int>::iterator it =

// }

#include <iostream>
#include <list>

std::ostream &operator<<(std::ostream &ostr, const std::list<int> &list)
{
	for (auto &i : list)
	{
		ostr << " " << i;
	}
	return ostr;
}

int main()
{
	std::list<int> list1 = {1, 2, 3, 4, 5};
	auto it = list1.begin();
	it++;
	it++;

	list1.splice(list1.begin(), list1, it);

	std::cout << "list1: " << list1 << "\n";
}