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
#include <unordered_map>

class Node
{
  public:
	Node(std::string str)
		: data_(str)
	{
	}
	std::string data_;
};

namespace std
{
template <>
class hash<Node>
{
  public:
	int operator()(const Node &s) const
	{
		return stoi(s.data_);
	}
};

} // namespace std

class LruCache
{
  public:
	// cpu 访问数据，需要动态更新缓存
	bool PutCache(std::string &str)
	{
		Node node(str);
		int key = hash_fn_(node);
		auto it = hash_table_.find(key);

		if (it != hash_table_.end())
		{
			cout << node.data_ << "数据已经在内存中．．．．" << endl;
			auto list_iter = it->second;
		}
		else
		{
		}
	}

  private:
	std::hash<Node> hash_fn_;
	int capacity_; //cache  capacity,其实就是 list 的容量
	//注意是：只用了一条 std::list
	//对于list中只有元素的删除操作会导致指向该元素的迭代器失效，其他元素迭代器不受影响，当删除元素时，将迭代器置为空就行了

	std::list<Node> double_list_;
	std::unordered_map<int, std::list<Node>::iterator> hash_table_;
};

int main(void)
{
	std::string str[] = {"7", "0", "1", "2", "0", "3", "0", "4", "2", "3", "0", "3", "2", "1", "2", "0", "1", "7", "0"};
	std::vector<std::string> pages(str, str + 19);

	LruCache lru;
	for (auto tt : pages)
	{
		// std::cout << "hash(s) = " << hash_fn(s) << "\n";
		lru.PutCache(tt);
	}
}
