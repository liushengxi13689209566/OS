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
	Node() {}
	Node(std::string str) : data_(str) {}
	bool operator==(const Node &node)
	{
		return this->data_ == node.data_;
	}
	std::string data_;
	Node *hnext; //散列表中拉链的hnext指针
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

#include "myhead.h"
class LruCache
{
  public:
	LruCache() : capacity_(0) {}

	bool PutCache(std::string &str)
	{
		Node node(str);
		int key = hash_fn_(node);

		Node *pos = SerarchCache(key, node);
		if (pos)
		{
			cout << node.data_ << "数据已经在内存中．．．．" << endl;
			double_list_.erase(pos);
			double_list_.push_front(node);
			hash_tables_[key] = &node;
		}
		else
		{
			cout << node.data_ << "数据未在内存中．．．．" << endl;
			/*页面满了就得删除并添加*/
			if (capacity_ >= 4)
			{
				hash_tables_[hash_fn_(double_list_.back())] = nullptr;
				double_list_.pop_back();
				--capacity_;
			}
			double_list_.push_front(node);
			hash_tables_[key] = &node;
			++capacity_;
		}
	}

  private:
	Node *SerarchCache(const int &key, const Node &node)
	{
		Node *p = hash_tables_[key];
		if (!p)
		{
			return nullptr;
		}
		else
		{
			Node *temp = p->hnext;
			while (temp)
			{
				if (*temp == node)
					return temp;
				temp = temp->hnext;
			}
			return nullptr;
		}
	}
	std::hash<Node> hash_fn_;
	int capacity_ = 0; //cache  capacity,其实就是 list 的容量

	DoubleList<Node> double_list_;
	std::vector<NodeT<Node> *> hash_tables_{100, nullptr};
};

int main(void)
{
	std::string str[] = {"7", "0", "1", "2", "0", "3", "0", "4", "2", "3", "0", "3", "2", "1", "2", "0", "1", "7", "0"};
	std::vector<std::string> pages(str, str + 19);

	LruCache lru;
	for (auto tt : pages)
	{
		lru.PutCache(tt);
	}
}
