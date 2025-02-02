/*************************************************************************
	> File Name: myhead.h
	> Author: Liu Shengxi 
	> Mail: 13689209566@163.com
	> Created Time: 2019年01月18日 星期五 11时32分34秒
 ************************************************************************/

#ifndef _MYHEAD_H
#define _MYHEAD_H
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <string>
#include <functional>
using namespace std;
struct Node
{
	Node(std::string Data)
	{
		m_Data = Data;
		m_pPrev = m_pNext = hnext = NULL;
	}
	bool operator==(const Node &node)
	{
		return this->m_Data == node.m_Data;
	}
	Node *hnext;		//散列表中拉链的hnext指针
	std::string m_Data; // 通用类型的数据元素

	Node *m_pPrev; // 指向上一个元素的指针
	Node *m_pNext; // 指向下一个元素的指针
};

class DoubleList
{
  private:
	int m_nCount;  // 链表中元素的数量
	Node *m_pHead; // 链表头指针
	Node *m_pTail; // 链表尾指针
  public:
	DoubleList() : m_nCount(0), m_pHead(NULL), m_pTail(NULL) {}

	DoubleList(const std::string &data) : m_nCount(0), m_pHead(NULL), m_pTail(NULL)
	{
		push_front(data);
	}

	virtual ~DoubleList()
	{
		Node *temp = m_pHead;
		while (temp)
		{
			delete temp;
			m_pHead = m_pHead->m_pNext;
		}
		m_nCount = 0;
	}

  public:
	int size() const
	{
		return m_nCount;
	}
	bool empty() const { return (!m_pHead || !m_pTail); }

	//从头部增加
	Node *push_front(Node node)
	{
		Node *pNewNode = &node;
		node.m_pPrev = node.m_pNext = NULL;

		if (m_pHead)
		{
			m_pHead->m_pPrev = pNewNode;
		}
		pNewNode->m_pNext = m_pHead;
		if (m_pHead == NULL)
			m_pTail = pNewNode;
		m_pHead = pNewNode;

		m_nCount++;
		return pNewNode;
	}

	//从尾部弹出
	void pop_back()
	{
		if (empty())
			throw("DoubleList : list is empty");

		Node *temp(m_pTail);
		m_pTail = m_pTail->m_pPrev;

		if (m_pTail)
			m_pTail->m_pNext = NULL;
		else
			m_pHead = m_pTail = NULL;

		delete temp;
		m_nCount--;
		return;
	}
	//删除
	void erase(Node *pos)
	{
		if (pos)
		{
			if (pos == m_pHead)
			{
				Node *temp = m_pHead;
				m_pHead = m_pHead->m_pNext;
				if (m_pHead)
				{
					m_pHead->m_pPrev = NULL;
				}
				delete temp;

				--m_nCount;
				if (0 == m_nCount)
				{
					m_pTail = m_pHead = NULL;
				}
			}
			else if (pos == m_pTail)
			{
				pop_back();
			}
			else
			{
				Node *temp = pos;
				pos->m_pPrev->m_pNext = pos->m_pNext;
				pos->m_pNext->m_pPrev = pos->m_pPrev;

				pos->m_pPrev = NULL;
				pos->m_pNext = NULL;

				delete temp;
			}
		}
	}
	std::string back()
	{
		if (empty())
			throw("CDListT : list is empty");
		return m_pTail->m_Data;
	}
	void print()
	{
		auto temp = m_pHead;
		while (temp)
		{
			cout << temp->m_Data << endl;
			temp = temp->m_pNext;
		}
		cout << endl;
	}
};
#endif
