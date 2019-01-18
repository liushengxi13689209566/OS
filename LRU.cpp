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
#include <functional>
#include "myhead.h"

int hash_fn_(const Node &node)
{
	return stoi(node.m_Data);
}

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
			cout << node.m_Data << "数据已经在内存中．．．．" << endl;
			double_list_.erase(pos);
			double_list_.push_front(node);
			hash_tables_[key] = &node;
		}
		else
		{
			cout << node.m_Data << "数据未在内存中．．．．" << endl;
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
		return true;
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

	int capacity_ = 0; //cache  capacity,其实就是 list 的容量

	DoubleList double_list_;
	std::vector<Node *> hash_tables_{100, nullptr};
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
