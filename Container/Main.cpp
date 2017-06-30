#include <iostream>
#include <string>
#include "SLinkedList.h"
#include "DLinkedList.h"
#include "ULinkedList.h"
#include "test.h"
#include "SDL.h"
//#include "BinaryNodeTree.h"
#include "BTNodeTree.h"


int main(int argc, char* args[])
{
	//	Binary Tree test

	cBTNodeTree* testtree = new cBTNodeTree();
	testtree->Insert(80);
	testtree->Insert(90);
	testtree->Insert(85);
	testtree->Insert(88);
	testtree->Insert(83);
	testtree->Insert(40);
	testtree->Insert(10);
	testtree->Insert(18);
	testtree->Insert(15);
	testtree->Insert(50);
	testtree->Insert(30);
	testtree->Insert(20);
	testtree->Insert(60);
	testtree->Insert(70);

	testtree->TraverseLevel();
	cBTNode* temp = new cBTNode();
	//testtree->InOrderDisplay();
	//testtree->FindPreSucc(testtree->GetRoot(), 50);
	//testtree->Deletion(20);
	//testtree->TraverseLevel();
	//temp = testtree->FindNodeSucc(30);
	//std::cout << temp->GetData();

	//testtree->Deletion(40);
	//testtree->TraverseLevel();

	/*testtree->MakeNonBST();
	std::cout << "New Tree is :" << std::endl;
	testtree->TraverseLevel();
	std::cout << "Testing for BST..." << std::endl;
	if (testtree->IsBST())
	{
		std::cout << "I'm a BST!" << std::endl;
	}
	else
	{
		std::cout << "I'm not a BST!" << std::endl;
	}*/
	testtree->PrintNodeInRange(25, 80);
	SDL_Delay(100000);
	
	/*cBTNode* test1 = new cBTNode(10);
	cBTNode* test2 = new cBTNode(20);
	cBTNode* test3 = new cBTNode(30);
	cBTNode* test4 = new cBTNode(40);
	cBTNode* test5 = new cBTNode(50);
	cBTNode* test6 = new cBTNode(60);
	cBTNode* test7 = new cBTNode(70);
	cBTNode* test8 = new cBTNode(80);
	cBTNode* test9 = new cBTNode(90);
	cBTNodeTree* tree = new cBTNodeTree(test1);

	test1->SetLeftChild(test2);
	test1->SetRightChild(test3);
	test2->SetLeftChild(test4);
	test2->SetRightChild(test5);
	test4->SetRightChild(test7);
	test3->SetRightChild(test6);
	test6->SetLeftChild(test8);
	test8->SetLeftChild(test9);

	std::cout << "Height is " << tree->GetHeightNonRV2();
	SDL_Delay(5000);

	*/

	//	ULinkedList test
	
	ULinkedList<int> test_list;
	test_list.Insert(10);
	test_list.Insert(20);
	test_list.Insert(30);
	test_list.Insert(40);
	test_list.Insert(50);
	test_list.Insert(60);
	test_list.Insert(70);
	test_list.Insert(10);
	test_list.Insert(20);
	test_list.Insert(30);
	test_list.Insert(40);
	test_list.Insert(50);
	test_list.Insert(60);
	test_list.Insert(70);
	test_list.Insert(10);
	test_list.Insert(20);
	test_list.Insert(30);
	test_list.Insert(40);
	test_list.Insert(50);
	test_list.Insert(60);
	test_list.Insert(70);

	ULinkedList<int> test_list_2;
	class func_temp
	{
	public:
		bool operator()(int x, int y)
		{
			if (x <= y)
				return true;
			return false;
		}
	};
	std::function<bool(int, int)> func = func_temp();
	//test_list.CopyIf(func, 65, test_list_2);

	/*std::cout << SDL_GetCPUCacheLineSize() << std::endl;
	test_manager test_mgr;
	test test_item1, test_item2, test_item3, test_item4;
	test_item1.Init("Goblin", 10, 0, 0);
	test_item2.Init("Orc", 15, 0, 0);
	test_item3.Init("Goblin", 10, 20, 0);
	test_item4.Init("Goblin", 10, 0, 0);
	std::cout << sizeof(test_item1) << " " << sizeof(test_item2) << std::endl;

	test_mgr.test_list.Append(test_item1);
	test_mgr.test_list.Append(test_item2);
	test_mgr.test_list.Append(test_item3);

	test_mgr.Remove(test_item4);*/
	
	
	/*DLinkedList<int> test_list;
	test_list.Append(10);
	test_list.Append(20);
	test_list.Append(30);
	test_list.Prepend(10);
	
	class func_temp
	{
	public:
		bool operator()(int x, int y)
		{
			if (x <= y)
				return true;
			return false;
		}
	};
	std::function<bool(int, int)> func = func_temp();
	int para = 15;
	test_list.RemoveIf(func, para);*/
	
	
	//test_list.Append(50);
	//test_list.Append(60);
	//test_list.Append(70);

	//DListIterator<int> test_it = test_list.GetIterator();
	//for (test_it.Init(); test_it.Valid(); test_it.Forth())
	//{
	//	std::cout << test_it.GetData() << " ";
	//}

	//SLinkedList<int> test_list;
	//SListIterator<int> test_it = test_list.GetIterator();

	//test_list.Append(10);
	//test_list.Append(20);
	//test_list.Append(30);
	//test_list.Append(40);
	//test_list.Append(50);
	//test_list.Append(60);
	//test_list.Append(70);

	///*for (test_it.Init(); test_it.Valid(); test_it.Forth())
	//{
	//	std::cout << test_it.GetData() << " ";
	//}*/
	////std::cout << std::endl;

	//SLinkedList<int> test_list2;
	//for (test_it.Init(); test_it.Valid(); test_it.Forth())
	//{
	//	if (test_it.m_node->m_data == 70)
	//	{
	//		test_list.GetSubList(test_it, test_list2);
	//		break;
	//	}
	//}

	//SListIterator<int> test_it2 = test_list2.GetIterator();
	//for (test_it2.Init(); test_it2.Valid(); test_it2.Forth())
	//{
	//	std::cout << test_it2.GetData() << " ";
	//}
	return 0;
}