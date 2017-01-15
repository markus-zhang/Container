#include <iostream>
#include "SLinkedList.h"


int main()
{
	SLinkedList<int> test_list;
	test_list.Append(10);
	test_list.Append(20);
	test_list.Append(30);
	test_list.Append(40);
	test_list.Append(50);
	test_list.Append(60);
	SListIterator<int> test_it = test_list.GetIterator();
	for (test_it.Init(); test_it.Valid(); test_it.Forth())
	{
		std::cout << test_it.GetData() << " ";
	}
}