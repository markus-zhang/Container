#include <iostream>
#include "SLinkedList.h"


int main()
{
	SLinkedList<int> test_list;
	SListIterator<int> test_it = test_list.GetIterator();

	test_list.Append(10);
	test_list.Append(20);
	test_list.Append(30);
	test_list.Append(40);
	test_list.Append(50);
	test_list.Append(60);
	test_list.Append(70);

	/*for (test_it.Init(); test_it.Valid(); test_it.Forth())
	{
		std::cout << test_it.GetData() << " ";
	}*/
	//std::cout << std::endl;

	SLinkedList<int> test_list2;
	for (test_it.Init(); test_it.Valid(); test_it.Forth())
	{
		if (test_it.m_node->m_data == 70)
		{
			test_list.GetSubList(test_it, test_list2);
			break;
		}
	}

	SListIterator<int> test_it2 = test_list2.GetIterator();
	for (test_it2.Init(); test_it2.Valid(); test_it2.Forth())
	{
		std::cout << test_it2.GetData() << " ";
	}
}