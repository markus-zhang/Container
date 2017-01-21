#ifndef TEST_H_
#define TEST_H_

#include "DLinkedList.h"

class test
{
public:
	void Init(std::string id, int hp, int x, int y)
	{
		m_ResID = id;	m_HP = hp;
		m_X = x;		m_Y = y;
	}
	bool operator==(const test& a)
	{
		if (this->m_HP == a.m_HP &&
			this->m_ResID == a.m_ResID &&
			this->m_X == a.m_X &&
			this->m_Y == a.m_Y)
			return true;
		return false;
	}
	bool operator!=(const test& a)
	{
		return !(*this == a);
	}
public:
	std::string m_ResID;
	int m_HP;
	int m_X;
	int m_Y;
};


class test_manager
{
public:
	class func_temp
	{
	public:
		bool operator()(test x, test y)
		{
			if (x == y)
				return true;
			return false;
		}
	};
public:
	bool Compare(const test& item, DListIterator<test>& it)
	{
		if (it.GetData() == item)
			return true;
		return false;
	}
	void Remove(test compare)
	{
		std::function<bool(test, test)> func_compare = func_temp();
		test_list.RemoveIf(func_compare, compare);
	}
public:
	DLinkedList<test> test_list;
};


#endif