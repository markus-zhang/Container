//	"Data Abstraction and Problem Solving with C++"
//	Binary Search Tree implementaion

#ifndef CONTAINER_BT_H_
#define CONTAINER_BT_H_

#include <functional>
#include <iostream>
#include <list>
#include <stack>
#include "BinaryTreeNode.h"

template<typename T>
class BST
{
private:
	BTN<T>* root;
	int counter;	//	Keep a counter for total number of nodes
protected:
	void inOrderTraverseHelper(BTN<T>* rt/*, std::function<void(BTN<T>*)> func*/);
	//void inOrderTraverseHelper(BTN<T>* rt, std::function<void(T&)> func);
	BTN<T>* balanceAddHelper(const T& item, BTN<T>* rt);

	BTN<T>* copyTreeHelper(const BTN<T>* rt);	//	Deep copy helper

	int getHeightHelper(BTN<T>* rt);

	BTN<T>* BSTInsertHelper(BTN<T>* rt, const T& item);

	BTN<T>* searchValue(BTN<T>* rt, const T& item);
	BTN<T>* findSuccessorHelper(BTN<T>* rt);
	BTN<T>* findSuccFromRoot(BTN<T>* node, T item);
	BTN<T>* findPredecessorHelper(BTN<T>* rt);
	BTN<T>* findPreFromRoot(BTN<T>* node, T item);
	BTN<T>* removeValueHelper(const T& item, BTN<T>* root);

	void levelDisplayHelper(BTN<T>* root);
	int countNumberHelper(BTN<T>* root);

public:
	//	Constructor and Destructor
	BST()
	{
		root == nullptr;
	}
	BST(const T& rootitem);
	BST(const T& rootitem, BTN<T>* left, BTN<T>* right);
	BST(const BTN<T>* node);
	

	//	Public Functions
	void inOrderDisplay();
	void inOrderProcess(std::function<void(T&)> func);

	int getHeight();

	void balanceAdd(const T& item);

	void inOrderTraversalNR(BTN<T>* rt, std::function<void(T&)> func);

	void BSTInsert(const T& item);

	void removeValue(const T& item);
	BTN<T>* findSuccessor(const T& item);
	BTN<T>* findPredecessor(const T& item);

	void levelDisplay();
	int countNumber();

	BTN<T>* search(const T& item)
	{
		return searchValue(root, item);
	}
};

//	Implementation

////	Constructor
template<typename T>
BST<T>::BST(const BTN<T>* rt)
{
	root = copyTreeHelper(rt);
}

////	Public Functions

template<typename T>
void BST<T>::inOrderTraverseHelper(BTN<T>* rt/*, std::function<void(BTN<T>*)> func*/)
{
	//	Traverse the BST in order
	if (rt == nullptr)
	{
		return;
	}

	//inOrderTraverseHelper(rt->getLeftChild(), func);
	inOrderTraverseHelper(rt->getLeftChild());
	//func(rt);
	std::cout << rt->getItem() << ", ";
	//inOrderTraverseHelper(rt->getRightChild(), func);
	inOrderTraverseHelper(rt->getRightChild());

}

/*template<typename T>
void BST<T>::inOrderTraverseHelper(BTN<T>* rt, std::function<void(T&)> func)
{
	if (rt != nullptr)
	{
		inOrderTraverseHelper(rt->getLeftChild(), func);
		func(rt->getItem());	//	Note that this does not modify the content in rt, even it's passed by reference
		
		inOrderTraverseHelper(rt->getRightChild(), func);
	}
}*/

template<typename T>
void BST<T>::inOrderDisplay()
{
	/*std::function<void(BST<T>*)> display = [](BTN<T>* rt)
	{
		std::cout << rt->getItem() << ", ";
	}*/

	//inOrderTraverseHelper(root, display);
	inOrderTraverseHelper(root);
}

template<typename T>
BTN<T>* BST<T>::copyTreeHelper(const BTN<T>* rt)
{
	BTN<T>* newrt = nullptr;
	if (rt != nullptr)
	{
		newrt = new BTN<T>*(rt->getItem(), nullptr, nullptr);
		newrt->setLeftChild(copyTree(rt->getLeftChild()));
		newrt->setRightChild(copyTree(rt->getRightChild()));
	}
	return newrt;
}

template<typename T>
void BST<T>::inOrderProcess(std::function<void(T&)> func)
{
	inOrderTraverseHelper(root, func);
}

template<typename T>
int BST<T>::getHeightHelper(BTN<T>* rt)
{
	//	Stopping criteria
	if (rt == nullptr)
		return 0;
	if (getHeightHelper(rt->getLeftChild()) >= getHeightHelper(rt->getRightChild()))
	{
		return 1 + getHeightHelper(rt->getLeftChild());
	}
	else
	{
		return 1 + getHeightHelper(rt->getRightChild());
	}
}

template<typename T>
int BST<T>::getHeight()
{
	return getHeightHelper(root);
}

template<typename T>
BTN<T>* BST<T>::balanceAddHelper(const T& item, BTN<T>* rt)
{
	//	Stopping criteria
	if (rt == nullptr)
	{
		BTN<T>* newnode = new BTN<T>(item);
		return newnode;
	}
	else
	{
		BTN<T>* left = rt->getLeftChild();
		BTN<T>* right = rt->getRightChild();
		if (getHeight(rt->getLeftChild()) <= getHeight(rt->getRightChild()))
		{
			left = balanceAddHelper(item, left);
			rt->setLeftChild(left);
		}
		else
		{
			right = balanceAddHelper(item, right);
			rt->setRightChild(right);
		}
		return rt;
	}
}

template<typename T>
void BST<T>::balanceAdd(const T& item)
{
	root = balanceAddHelper(item, root);
}

template<typename T>
void BST<T>::inOrderTraversalNR(BTN<T>* rt, std::function<void(T&)> func)
{
	//	Algorithm:
	//	Keep a stack<BinaryNode<DataType>*> as reference
	//	Start from the root, i.e. curptr = m_Root
	//	If curptr == nullptr && stack is empty, end
	//	If curptr != nullptr, push into stack, try to walk left
	//	If curptr == nullptr && stack is NOT empty,
	//	then we set curptr = stack.top()->GetRight()
	//	Process stack.top(), and pop stack
	//	Possible optimization: If node is leaf, then just Process
	
	std::stack<BTN<T>*> entry;
	BTN<T>* walker = rt;
	while (1)
	{
		if (walker == nullptr && entry.empty())
			break;
		else if (walker != nullptr)
		{
			entry.push(walker);
			walker = walker->getLeftChild();
		}
		else
		{
			walker = entry.top();
			T item = walker->getItem();
			//	Do whatever you want with item
			func(item);
			walker = walker->getRightChild();
			entry.pop();
		}
	}
}

template<typename T>
BTN<T>* BST<T>::BSTInsertHelper(BTN<T>* rt, const T& item)
{
	if (rt == nullptr)
	{
		BTN<T>* newnode = new BTN<T>(item);
		return newnode;
	}
	else
	{
		BTN<T>* left = rt->getLeftChild();
		BTN<T>* right = rt->getRightChild();

		if (item <= rt->getItem())
		{
			left = BSTInsertHelper(rt->getLeftChild(), item);
			rt->setLeftChild(left);
		}
		else
		{
			right = BSTInsertHelper(rt->getRightChild(), item);
			rt->setRightChild(right);
		}
		return rt;
	}
}

template<typename T>
void BST<T>::BSTInsert(const T& item)
{
	root = BSTInsertHelper(root, item);
}

template<typename T>
BTN<T>* BST<T>::searchValue(BTN<T>* rt, const T& item)
{
	//	Recursively search the value and return
	if (rt == nullptr)
	{
		//	Value is not in the tree
		return nullptr;
	}
	else
	{
		BTN<T>* node = new BTN<T>();
		if (item == rt->getItem())
		{
			//	Found the item
			return rt;
		}
		else if (item < rt->getItem())
		{
			//	Search in left subtree
			node = searchValue(rt->getLeftChild(), item);
		}
		else
		{
			node = searchValue(rt->getRightChild(), item);
		}
		return node;
	}
}

template<typename T>
BTN<T>* BST<T>::findSuccessorHelper(BTN<T>* rt)
{
	//	rt must be the node that has been located (cannot be nullptr)
	//	Case I: we can go right
	//	We will keep going right until we find one that can go left
	//	Then we keep going left
	if (rt->getRightChild() != nullptr)
	{
		std::cout << "Go Right" << std::endl;
		//	Now goes right
		BTN<T>* right = rt->getRightChild();
		while (right->getLeftChild())
		{
			std::cout << "Turn Left" << std::endl;
			//	If we can get left at the first right node
			//	Then keep going left
			//	If we cannot get left, then don't bother because rt is already the successor
			right = right->getLeftChild();
		}
		return right;
	}
	else
	{
		//	Case II: Successor might be the parent, or no successor
		//	So we search for the whole tree for its parent
		BTN<T>* succ = findSuccFromRoot(root, rt->getItem());
		return succ;
	}
}

template<typename T>
BTN<T>* BST<T>::findSuccFromRoot(BTN<T>* node, T item)
{
	//	Special program to locate successor from root
	if (node == nullptr)
		return nullptr;
	else
	{
		//				    40
		//          /                  \
		//		35                        55
		//         \                  /
		//		     38           50
		//          /           /     \
		//	       36         45       53
		//                            /
		//                          51
		//	Consider the case of 55: there is no successor
		//	Consider the case of 53: the successor is 55
		//		The last ancestor node that turns left
		//	Consider the case of 36: the successor is 38
		//		The last ancestor node that turns left
		//	Consider the case of 35: these kind of nodes
		//		can go right, so has already been dealt with
		//		by findSuccessorHelper()
		//	Strategy: keep a pointer to the last node that
		//		turns left
		BTN<T>* succ = nullptr;
		while (node != nullptr)
		{
			if (item < node->getItem())
			{
				//	We save the parent before going left
				//	in case that the left child of the parent
				//	contains the item
				succ = node;
				node = node->getLeftChild();
			}
			else if (item > node->getItem())
			{
				//	No need to save the node
				node = node->getRightChild();
			}
			else
			{
				//	We have reached the node containing the node
				//	just break and return succ
				break;
			}
		}
		return succ;
	}
}

template<typename T>
BTN<T>* BST<T>::findSuccessor(const T& item)
{
	//	Locate item
	BTN<T>* node = searchValue(root, item);
	if (node == nullptr)
	{
		return nullptr;
	}
	else
	{
		std::cout << "Found as: " << node->getItem() << std::endl;
		return findSuccessorHelper(node);
	}
}

template<typename T>
BTN<T>* BST<T>::findPredecessorHelper(BTN<T>* rt)
{
	//	rt must be the node that has been located (cannot be nullptr)
	//	Case I: we can go left
	//	We will keep going left until we find one that can go rigt
	//	Then we keep going right
	if (rt->getLeftChild() != nullptr)
	{
		std::cout << "Go Left" << std::endl;
		//	Now goes left
		BTN<T>* left = rt->getLeftChild();
		while (left->getRightChild())
		{
			std::cout << "Turn right" << std::endl;
			//	If we can get right at the first left node
			//	Then keep going right
			//	If we cannot get right, then don't bother because rt is already the predecessor
			left = left->getRightChild();
		}
		return left;
	}
	else
	{
		//	Case II: Successor might be the parent, or no successor
		//	So we search for the whole tree for its parent
		BTN<T>* pre = findPreFromRoot(root, rt->getItem());
		return pre;
	}
}

template<typename T>
BTN<T>* BST<T>::findPreFromRoot(BTN<T>* node, T item)
{
	//	Special program to locate predecessor from root
	if (node == nullptr)
		return nullptr;
	else
	{
//				    40
//          /                  \
//		35                        55
//         \                  /
//		     38           50
//          /           /     \
//	       36         45       53
//                            /
//                          51
//	Consider the case of 35: there is no successor
//	Consider the case of 36: the predecessor is 35,
//		The last ancestor that turns right
//	Consider the case of 55: these kind of nodes
//		can go left, so has already been dealt with
//		by findPredecessorHelper()
//	Strategy: keep a pointer to the last node that
//		turns left
		BTN<T>* pre = nullptr;
		while (node != nullptr)
		{
			if (item > node->getItem())
			{
				//	We save the parent before going left
				//	in case that the right child of the parent
				//	contains the item
				pre = node;
				node = node->getRightChild();
			}
			else if (item < node->getItem())
			{
				//	No need to save the node
				node = node->getLeftChild();
			}
			else
			{
				//	We have reached the node containing the node
				//	just break and return succ
				break;
			}
		}
		return pre;
	}
}

template<typename T>
BTN<T>* BST<T>::findPredecessor(const T& item)
{
	//	Locate item
	BTN<T>* node = searchValue(root, item);
	if (node == nullptr)
	{
		return nullptr;
	}
	else
	{
		std::cout << "Found as: " << node->getItem() << std::endl;
		return findPredecessorHelper(node);
	}
}

//template<typename T>
//BTN<T>* BST<T>::removeValueHelper(const T& item, BTN<T>* root)
//{
//	BTN<T>* node = searchValue(root, item);
//	std::cout << "Should remove: " << node->getItem() << std::endl;
//	//	Leaf nodes and One-child nodes
//	if (node->getLeftChild() == nullptr)
//	{
//		return node->getRightChild();
//	}
//	if (node->getRightChild() == nullptr)
//	{
//		return node->getLeftChild();
//	}
//
//	//	Two-children nodes
//	BTN<T>* pre = findPredecessor(node->getItem());
//	BTN<T>* succ = findSuccessor(node->getItem());
//	if (pre != nullptr)
//	{
//		T item = pre->getItem();
//		node->setItem(item);
//		node->setLeftChild(removeValueHelper(item, node->getLeftChild()));
//	}
//	else if (succ != nullptr)
//	{
//		T item = succ->getItem();
//		node->setItem(item);
//		node->setRightChild(removeValueHelper(item, node->getRightChild()));
//	}
//	return node;
//}

template<typename T>
BTN<T>* BST<T>::removeValueHelper(const T& item, BTN<T>* root)
{
	if (root == nullptr)
		return nullptr;

	if (item < root->getItem())
	{
		root->setLeftChild(removeValueHelper(item, root->getLeftChild()));
	}
	else if (item > root->getItem())
	{
		root->setRightChild(removeValueHelper(item, root->getRightChild()));
	}
	else
	{
		//	Found the item
		//	Leaf and one-child nodes
		if (root->getLeftChild() == nullptr)
			return root->getRightChild();
		if (root->getRightChild() == nullptr)
			return root->getLeftChild();

		//	Two-children nodes
		BTN<T>* pre = findPredecessor(item);
		BTN<T>* succ = findSuccessor(item);
		if (pre != nullptr)
		{
			T pre_item = pre->getItem();
			root->setItem(pre_item);
			root->setLeftChild(removeValueHelper(pre_item, root->getLeftChild()));
			return root;
		}
		if (succ != nullptr)
		{
			T succ_item = succ->getItem();
			root->setItem(succ_item);
			root->setRightChild(removeValueHelper(succ_item, root->getRightChild()));
			return root;
		}
	}
}

template<typename T>
void BST<T>::removeValue(const T& item)
{
	/*BTN<T>* node = new BTN<T>();
	node = searchValue(root, item);
	if (node == nullptr)
	{
		std::cout << "Not found!" << std::endl;
		return;
	}
	else
	{
		node = removeValueHelper(node);
	}*/
	removeValueHelper(item, root);
}

template<typename T>
void BST<T>::levelDisplayHelper(BTN<T>* root)
{
	if (root == nullptr)
		return;

	int height = getHeight();
	std::list<BTN<T>*> ls;
	ls.push_back(root);
	std::cout << root->getItem() << std::endl;

	while (1)
	{
		int size = ls.size();
		while (size > 0)
		{
			BTN<T>* left = ls.front()->getLeftChild();
			BTN<T>* right = ls.front()->getRightChild();
			if (left != nullptr)
			{
				ls.push_back(left);
			}
			if (right != nullptr)
			{
				ls.push_back(right);
			}
			ls.pop_front();
			size -= 1;
		}
		if (ls.empty())
			break;
		//	Display
		for (auto ptr : ls)
		{
			std::cout << ptr->getItem() << " ";
		}
		std::cout << std::endl;
	}
}

template<typename T>
void BST<T>::levelDisplay()
{
	levelDisplayHelper(root);
}

template<typename T>
int BST<T>::countNumberHelper(BTN<T>* root)
{
	if (root == nullptr)
		return 0;

	return 1 + countNumberHelper(root->getLeftChild()) + countNumberHelper(root->getRightChild());
}

template<typename T>
int BST<T>::countNumber()
{
	return countNumberHelper(root);
}
#endif