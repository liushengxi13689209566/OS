/*************************************************************************
	> File Name: LRU.cpp
	> Author: Liu Shengxi 
	> Mail: 13689209566@163.com
	> Created Time: 2018年10月11日 星期四 21时22分41秒
 ************************************************************************/

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;
void print(list<int> &physical_block)
{
	for (auto tmp : physical_block)
		cout << tmp << " ";
	cout << endl;
}
int main(void)
{
	// 規定内存中放置的页面不超过 4 （也就是list不超过 4）
	list<int> physical_block;
	vector<int> pages = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};

	for (auto i : pages) //依次访问页面
	{
		/*先看在没在内存中*/
		auto it = std::find(physical_block.begin(), physical_block.end(), i);
		if (it != physical_block.end())
		{
			cout << i << "在内存中" << endl;
			physical_block.erase(it);
			physical_block.push_front(i);
		}
		/*没在*/
		else
		{
			cout << i << "不在内存中" << endl;
			/*页面满了就得删除并添加*/
			if (physical_block.size() >= 4)
				physical_block.pop_back();

			physical_block.push_front(i);
		}
		/*打印内存中的页面*/
		print(physical_block);
		cout << "********************************" << endl;
	}
}