#include <iostream>
#include <string>
#include "SLinkedList.h"
#include "DLinkedList.h"
#include "ULinkedList.h"
#include "test.h"
#include "SDL.h"
//#include "BinaryNodeTree.h"
#include "BTNodeTree.h"
#include "ArithExp.h"
#include "BinaryTree.h"


int main(int argc, char* args[])
{	
	// Arith
	////	Arith tree test
	cArith* atree = new cArith();
	atree->Scan("-1+2*-(35+54)+sin(2)");
	atree->Display();
	atree->ParseListSelf();
	SDL_Delay(50000);
	
	//	Binary Tree test
	BST<int>* test20 = new BST<int>();
	test20->BSTInsert(40);
	test20->BSTInsert(55);
	test20->BSTInsert(50);
	test20->BSTInsert(45);
	test20->BSTInsert(53);
	test20->BSTInsert(51);
	test20->BSTInsert(35);
	test20->BSTInsert(36);
	test20->BSTInsert(38);

	test20->inOrderDisplay();
	std::cout << std::endl;
	test20->removeValue(35);
	test20->levelDisplay();
	SDL_Delay(99999);

	BTN<int>* succ = test20->findPredecessor(53);
	if (succ != nullptr)
	{
		std::cout << "Predecessor is " << succ->getItem() << std::endl;
	}
	else
	{
		std::cout << "There is no predecessor." << std::endl;
	}
	SDL_Delay(5000000);

	//	Pointer test
	cBTNodeTree* test10 = new cBTNodeTree();
	test10->test(10);
	std::cout << "KKK" << std::endl;
	test10->DisplayLevel();
	SDL_Delay(100000);
	
	// Get Largest BST
	cBTNodeTree* largetree = new cBTNodeTree();
	cBTNode* node10 = new cBTNode(10);
	cBTNode* node15 = new cBTNode(15);
	cBTNode* node12 = new cBTNode(12);
	cBTNode* node11 = new cBTNode(11);
	cBTNode* node18 = new cBTNode(18);
	cBTNode* node17 = new cBTNode(17);
	cBTNode* node14 = new cBTNode(14);
	cBTNode* node20 = new cBTNode(20);
	cBTNode* node13 = new cBTNode(13);
	cBTNode* node22 = new cBTNode(22);
	cBTNode* node21 = new cBTNode(21);
	cBTNode* node25 = new cBTNode(25);
	cBTNode* node29 = new cBTNode(29);
	
	largetree->m_Root = node10;
	largetree->m_Root->m_LeftChild = node15;
	largetree->m_Root->m_RightChild = node12;
	node15->m_LeftChild = node11;
	node15->m_RightChild = node18;
	node12->m_RightChild = node14;
	node12->m_LeftChild = node17;

	node18->m_RightChild = node20;
	node14->m_LeftChild = node13;
	node14->m_RightChild = node22;
	node22->m_LeftChild = node21;
	node22->m_RightChild = node25;
	node25->m_RightChild = node29;

	largetree->DisplayLevel();
	std::cout << "***********" << std::endl;
	cBTNodeTree* blah = new cBTNodeTree();
	blah = largetree->BT2BST();
	blah->DisplayLevel();

	//largetree->FindLargestBST();
	SDL_Delay(100000);

	// section 16.4 test
	/*cBTNodeTree* testtree3 = new cBTNodeTree();
	testtree3->Insert(5);
	testtree3->Insert(10);
	testtree3->Insert(15);
	testtree3->Insert(20);
	testtree3->Insert(25);
	testtree3->Insert(30);
	testtree3->Insert(35);
	testtree3->Insert(40);

	testtree3->DisplayLevel();
	std::list<float> ls2;
	testtree3->Save(ls2);
	cBTNodeTree* testtree4 = new cBTNodeTree();
	testtree4->LoadBalancedPtrMain(ls2);
	std::cout << testtree4->FindLargestBST()->GetData();
	SDL_Delay(100000);*/
	
	/*std::cout << testtree3->BalanceFactor();
	std::cout << std::endl;*/
	//testtree3->DisplayLevel();
	//std::list<float> ls2;
	//testtree3->Save(ls2);
	//cBTNodeTree* testtree4 = new cBTNodeTree();
	///*testtree4->LoadOriginal(ls2);*/
	//testtree4->LoadBalancedPtrMain(ls2);
	//std::cout << "*********************" << std::endl;
	//testtree4->DisplayLevel();

	//SDL_Delay(100000);
	
	////	Arith tree test
	//cArith* atree = new cArith();
	//atree->Scan("(((((2+3*4)))+(2.5*4+0)/(2.5+2.5))*100");
	////atree->Display();
	//atree->ParseListSelf();
	////atree->ParseSelf();
	////float result = atree->EvaluateSelf();
	////std::cout << result;
	//SDL_Delay(50000);
	
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

	std::list<float> ls;
	testtree->Save(ls);
	testtree->DisplayLevel();
	cBTNodeTree* testtree2 = new cBTNodeTree();
	testtree2->LoadOriginal(ls);
	testtree->DisplayLevel();
	std::cout << "Balance factor is: " << testtree->BalanceFactor();

	/*for (auto i : ls)
	{
		std::cout << i << ", ";
	}
	std::cout << std::endl;
	cBTNodeTree* testtree2 = new cBTNodeTree();
	testtree2->LoadOriginal(ls);
	testtree->InOrderDisplay();
	std::cout << "*******************" << std::endl;
	testtree2->InOrderDisplay();*/
	SDL_Delay(500000);

	//testtree->TraverseLevel();
	//cBTNode* temp = new cBTNode();
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
	//testtree->PrintNodeInRange(25, 80);
	//SDL_Delay(100000);
	
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