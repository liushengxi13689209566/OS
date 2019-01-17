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
#include <string>
using namespace std;

// void print(list<int> &physical_block)
// {
// 	for (auto tmp : physical_block)
// 		cout << tmp << " ";
// 	cout << endl;
// }

// int main(void)
// {
// 	// 規定内存中放置的页面不超过 4 （也就是list不超过 4）
// 	list<int> physical_block;
// 	vector<int> pages = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};

// 	for (auto i : pages) //依次访问页面
// 	{
// 		/*先看在没在内存中*/
// 		auto it = std::find(physical_block.begin(), physical_block.end(), i);
// 		if (it != physical_block.end())
// 		{
// 			cout << i << "在内存中" << endl;
// 			physical_block.erase(it);
// 			physical_block.push_front(i);
// 		}
// 		/*没在*/
// 		else
// 		{
// 			cout << i << "不在内存中" << endl;
// 			/*页面满了就得删除并添加*/
// 			if (physical_block.size() >= 4)
// 				physical_block.pop_back();

// 			physical_block.push_front(i);
// 		}
// 		/*打印内存中的页面*/
// 		print(physical_block);
// 		cout << "********************************" << endl;
// 	}
// }
#include <functional>
struct S
{
	std::string chars;
};

namespace std
{
template <>
class hash<S>
{
  public:
	int operator()(const S &s) const
	{
		return stoi(s.chars);
	}
};
class Node
{
  public:
	Node(std::string str) : data_(str), hnext_(nullptr) {}

	std::string data_;
	Node *hnext_;
};

class LruCache
{
  public:
	//　cpu简单读取数据
	bool ReadCache()
	{
	}
	// cpu 访问新数据，需要动态更新缓存
	bool WriteCache(std::string &str)
	{
		s_.chars = str;
		Node tmp(str);
		double_list_.push_back(tmp);
		hash_table_[hash_fn_(s_)] = &tmp;
	}

  private:
	S s_;
	std::hash<S> hash_fn_;

	int capacity_; //cache  capacity,其实就是 list 的容量
	//注意是：只用了一条 std::list
	//对于list中只有元素的删除操作会导致指向该元素的迭代器失效，其他元素迭代器不受影响，当删除元素时，将迭代器置为空就行了
	std::list<Node> double_list_;
	std::vector<Node *> hash_table_{100};
};

} // namespace std

int main(void)
{
	std::string str[] = {"7", "0", "1", "2", "0", "3", "0", "4", "2", "3", "0", "3", "2", "1", "2", "0", "1", "7", "0"};
	std::vector<std::string> pages(str, str + 19);

	LruCache lru;
	for (auto tt : pages)
	{
		// std::cout << "hash(s) = " << hash_fn(s) << "\n";
		lru.WriteCache(tt);
	}
}
