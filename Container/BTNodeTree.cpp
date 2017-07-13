#include <stack>
#include <iostream>
#include <algorithm>
#include "BTNodeTree.h"

int cBTNodeTree::GetHeight(cBTNode* root)
{
	//	Recursive method to get height
	if (root == nullptr)
	{
		return 0;
	}
	return std::max(1 + GetHeight(root->GetLeftChild()),
		1 + GetHeight(root->GetRightChild()));
}

int cBTNodeTree::GetHeightNonR()
{
	//	Level order travesal (Double List Version)
	//	We will store the nodes of every LEVEL into a container
	//	And loop through the container to locate the nodes of next level
	//	We will also remove the nodes of last level from the container
	//	After each remove height+= 1
	//	Stop until the container is null (no next level)
	std::list<cBTNode*> level;
	int height = 0;

	if (m_Root == nullptr && level.size() == 0)
		return 0;

	level.push_back(m_Root);
	height += 1;
	while (1)
	{
		std::list<cBTNode*> nextlevel;
		for (auto i : level)
		{
			if (i->GetLeftChild() != nullptr)
				nextlevel.push_back(i->GetLeftChild());
			if (i->GetRightChild() != nullptr)
				nextlevel.push_back(i->GetRightChild());
		}
		if (nextlevel.empty())
			break;
		else
		{
			level.clear();
			level = nextlevel;
			nextlevel.clear();
			height += 1;
		}
	}
	return height;
}

int cBTNodeTree::GetHeightNonRV2()
{
	//	Level order travesal (Single List Version)
	//	We will store the nodes of every LEVEL into a container
	//	And loop through the container to locate the nodes of next level
	//	We will also remove the nodes of last level from the container
	//	After each remove height+= 1
	//	Stop until the container is null (no next level)
	std::list<cBTNode*> level;
	int height = 0;

	if (m_Root == nullptr && level.size() == 0)
		return 0;

	level.push_back(m_Root);
	height += 1;
	while (1)
	{
		int temp = level.size();
		while (temp > 0)
		{
			if (level.front()->GetLeftChild() != nullptr)
				level.push_back(level.front()->GetLeftChild());
			if (level.front()->GetRightChild() != nullptr)
				level.push_back(level.front()->GetRightChild());
			level.pop_front();	//	Only pop the current level nodes
			temp -= 1;
		}
		if (level.empty())
			break;
		height += 1;
	}
	return height;
}

cBTNode* cBTNodeTree::InsertHelper(cBTNode* root, const float& data)
{
	//	Binary Search Tree Insert
	if (root == nullptr)
	{
		cBTNode* newroot = new cBTNode(data);
		return newroot;
	}
	cBTNode* left = root->GetLeftChild();
	cBTNode* right = root->GetRightChild();

	if (data <= root->GetData())
	{
		left = InsertHelper(left, data);
		root->SetLeftChild(left);
	}
	else
	{
		right = InsertHelper(right, data);
		root->SetRightChild(right);
	}
	return root;
}

void cBTNodeTree::TraverseLevel()
{
	//	Level Traversal
	std::list<cBTNode*> level;
	if (m_Root == nullptr)
		return;

	level.push_back(m_Root);
	while (1)
	{
		int temp = level.size();
		//	Display nodes
		for (auto i : level)
		{
			std::cout << i->GetData() << " ";
		}
		std::cout << std::endl;
		while (temp > 0)
		{
			if (level.front()->GetLeftChild() != nullptr)
				level.push_back(level.front()->GetLeftChild());
			if (level.front()->GetRightChild() != nullptr)
				level.push_back(level.front()->GetRightChild());
			level.pop_front();
			temp -= 1;
		}
		if (level.empty())
			break;
	}
	return;
}

cBTNode* cBTNodeTree::SearchHelper(cBTNode* node, const float& data)
{
	//	Recursively Search
	if (node == nullptr)
	{
		std::cout << "Not Found!" << std::endl;
		return nullptr;
	}

	//	Stop when it's found
	if (node->GetData() == data)
	{
		std::cout << "Found!" << std::endl;
		return node;
	}

	//	Need to add insertion later!
	if (data < node->GetData())
	{
		SearchHelper(node->GetLeftChild(), data);
	}
	else
	{
		SearchHelper(node->GetRightChild(), data);
	}
}

void cBTNodeTree::Deletion(const float& data)
{
	DeletionHelper(data, m_Root);
}

cBTNode* cBTNodeTree::DeletionHelper(const float& data, cBTNode* node)
{
	//	We need to return cBTNode* to reset the root after the tree
	//	has been modified
	//	Step 1: Search the tree for data recursively
	if (node == nullptr)
		return nullptr;

	if (data < node->GetData())
	{
		//	Search in the left subtree
		node->SetLeftChild(DeletionHelper(data, node->GetLeftChild()));
	}
	else if (data > node->GetData())
	{
		//	Search in the right subtree
		node->SetRightChild(DeletionHelper(data, node->GetRightChild()));
	}
	else
	{
		//	Already found
		//	Step 2.1	Delete a leaf node / one-child node
		//	This is a very clever algorithm
		//	Case 1: one-child node
		//	node will be replaced by its non-nullptr child
		//	Case 2: leaf node
		//	node will be replaced by nullptr because both children are nullptr
		if (node->GetLeftChild() == nullptr)
			return node->GetRightChild();
		if (node->GetRightChild() == nullptr)
			return node->GetLeftChild();

		//	Step 2.2	Delete a two-children node
		//	Very easy, replace it with an inorder pre/succ
		//	and recursively delete the pre/succ
		//	The trick is to copy the data, NOT the node
		if (FindNodeSucc(data) != nullptr)
		{
			float temp = FindNodeSucc(data)->GetData();
			std::cout << "Succesor is " << temp << std::endl;
			node->ModifyData(temp);
			//	Now we need to delete the successor
			//	Because the successor is on the right side
			//	So we reset the right child
			node->SetRightChild(DeletionHelper(temp, node->GetRightChild()));
		}
		else if (FindNodePre(data) != nullptr)
		{
			float temp = FindNodePre(data)->GetData();
			std::cout << "Precessor is " << temp << std::endl;
			node->ModifyData(temp);
			node->SetLeftChild(DeletionHelper(temp, node->GetLeftChild()));
		}
	}
	return node;
}

void cBTNodeTree::FindPreSucc(cBTNode* node, float data)
{
	//	if (data < node->GetData())
	//		if (node->GetLeftChild() == nullptr)
	//			node has no pre (smaller than smallest node in tree)
	//		if (data > max of node->GetLeftChild())
	//			then pre = max of node->GetLeftChild() and succ = node->GetData()
	//		else
	//			set node = node->GetLeftChild() and call myself
	//	else
	//		if (node->GetRightChild() == nullptr)
	//			node has no succ (larger than largest node in tree)
	//		if (data < min of node->GetRightChild())
	//			then pre = node->GetData() and succ = min of node->GetRightChild()
	//		else
	//			set node = node->GetRightChild() and call myself
	if (data < node->GetData())
	{
		if (node->GetLeftChild() == nullptr)
		{
			std::cout << data << " has no pre" << std::endl;
			std::cout << "succ is " << node->GetData();
			return;
		}
		if (data > FindMax(node->GetLeftChild())->GetData())
		{
			std::cout << "Pre is " << FindMax(node->GetLeftChild())->GetData() << std::endl;
			std::cout << "Succ is " << node->GetData();
			return;
		}
		else
		{
			node = node->GetLeftChild();
			FindPreSucc(node, data);
		}
	}
	else
	{
		if (node->GetRightChild() == nullptr)
		{
			std::cout << data << " has no succ" << std::endl;
			std::cout << "pre is " << node->GetData();
			return;
		}
		if (data < FindMin(node->GetRightChild())->GetData())
		{
			std::cout << "Pre is " << node->GetData();
			std::cout << "Succ is " << FindMin(node->GetRightChild())->GetData();
			return;
		}
		else
		{
			node = node->GetRightChild();
			FindPreSucc(node, data);
		}
	}
}

cBTNode* cBTNodeTree::FindNodePreHelper(cBTNode* node, float data)
{
	//	We search X from the root
	//	Since we are looking for the predeccesor,
	//	if data < node->GetData(), we will look into left subtree
	//	until we hit a node(called A) that does not have a left subtree
	//	
	//	then we know that X is greater than A, because if X is smaller
	//	then X must be at LEFT subtree of A
	//
	//	So we search the right subtree of A and keep record of the last node
	//	we are traversing, until we find some node B larger than X, then
	//	we will go searching at the left subtree of B
	//
	//	So the above procedure can be concluded as:

	cBTNode* temp = Search(data);
	if (temp == nullptr)
		return nullptr;
	if (temp->GetLeftChild() != nullptr)
	{
		//	If it has left subtree, then the predecessor must be in left subtree
		return FindMax(temp->GetLeftChild());
	}
	else
	{
		//	Search the whole tree until we find the predecessor
		cBTNode* pre = nullptr;
		while (node != nullptr)
		{
			//	General rule:
			//	If we go right, then either pre is in the left subtree
			//	of the node;
			//	Or if the node is a leaf, there are only a few possibilities:
			//	1. grandfather -left-> father -left-> node
			//		The trick is to memorize the first ancestor
			//		that extends right subtree to reach grandfather
			//		(Consider the 83 case in Main.cpp)
			//	2. grandfather -left-> father -right-> node
			//		Then gradfather is pre
			//	3. grandfather -right-> father -left-> node
			//		Again grandfather is pre
			//	4. grandfather -right-> father -right-> node
			//		Then father is pre
			if (data > node->GetData())
			{
				//	Go for the right side
				//	Case 1: node->GetRightChild() == nullptr
				//		Then while() breaks, pre = node
				//	Case 2: walk zigzag (if > then turn left, else turn right)
				//		Until it reaches destination.
				//		The trick is to keep a pointer to the LAST traversed node
				pre = node;
				node = node->GetRightChild();
			}
			else if (data < node->GetData())
			{
				//	Do not need to keep last traversed node
				node = node->GetLeftChild();
			}
			else
			{
				//	Algorithm will always converge on node
				//	as long as node is valid (!= nullptr)
				//	By the time algorithm reaches node
				//	there are two cases:
				//	Case 1: root->...->node has a route that
				//		consists only right jumps
				//		Then the previous branch already
				//		captures "pre" = parent of node
				//		So we only need to break from loop
				//		and return pre
				//	Case 2: There is at least one left turn
				//		in the route. 
				//			Scenario 1:
				//			If node is the RIGHT child of its
				//			parent, then it doesn't matter, because
				//			this will trigger the 
				//			pre = node;
				//			node = node->GetRightChild()
				//			before we hit the node, i.e.
				//			when we hit the parent of the node
				//			and we only need to break to return its parent
				//			which is captured by "pre".
				//			
				//			Scenario 2:
				//			If node is the LEFT child of its parent,
				//			then "pre" has already captured our target
				//			Because the LAST NODE ON THE ROUTE THAT GOES
				//			TO ITS RIGHT CHILD is the predecessor
				//			And it is captured by
				//			pre = node;
				//			node = node->GetRightChild()
				//			and we only need to break to return
				break;
			}
		}
		return pre;
	}
}

cBTNode* cBTNodeTree::FindNodeSuccHelper(cBTNode* node, float data)
{
	cBTNode* temp = Search(data);
	if (temp == nullptr)
		return nullptr;
	if (temp->GetRightChild() != nullptr)
	{
		//	If it has right subtree, then the successor must be in right subtree
		return FindMin(temp->GetRightChild());
	}
	else
	{
		//	Search the whole tree until we find the successor
		cBTNode* succ = nullptr;
		while (node != nullptr)
		{
			if (data < node->GetData())
			{
				//	Go for the left side
				//	Case 1: node->GetLeftChild() == nullptr
				//		Then while() breaks, succ = node
				//	Case 2: walk zigzag (if > then turn left, else turn right)
				//		Until it reaches destination.
				//		The trick is to keep a pointer to the LAST traversed node
				succ = node;
				node = node->GetLeftChild();
			}
			else if (data > node->GetData())
			{
				//	Do not need to keep last traversed node
				node = node->GetRightChild();
			}
			else
			{
				//	Algorithm will always converge on node
				//	as long as node is valid (!= nullptr)
				//	By the time algorithm reaches node
				//	there are two cases:
				//	Case 1: root->...->node has a route that
				//		consists only left jumps
				//		Then the previous branch already
				//		captures "succ" = parent of node
				//		So we only need to break from loop
				//		and return "succ" (example: 10)
				//	Case 2: There is at least one right turn
				//		in the route. 
				//			Scenario 1: (example: 20)
				//			If node is the LEFT child of its
				//			parent, then it doesn't matter, because
				//			this will trigger the 
				//			succ = node;
				//			node = node->GetLeftChild()
				//			before we hit the node, i.e.
				//			when we hit the parent of the node
				//			and we only need to break to return its parent
				//			which is captured by "succ".
				//			
				//			Scenario 2: (example: 30)
				//			If node is the RIGHT child of its parent,
				//			then "pre" has already captured our target
				//			Because the LAST NODE ON THE ROUTE THAT GOES
				//			TO ITS LEFT CHILD is the predecessor
				//			And it is captured by
				//			succ = node;
				//			node = node->GetLeftChild()
				//			and we only need to break to return
				break;
			}
		}
		return succ;
	}
}

cBTNode* cBTNodeTree::FindMax(cBTNode* node)
{
	//	Simply the most right node
	if (node == nullptr)
		return nullptr;

	if (node->GetRightChild() == nullptr)
		return node;
	else
	{
		node = node->GetRightChild();
		FindMax(node);
	}
}

cBTNode* cBTNodeTree::FindMin(cBTNode* node)
{
	//	Simply the most right node
	if (node == nullptr)
		return nullptr;

	if (node->GetLeftChild() == nullptr)
		return node;
	else
	{
		node = node->GetLeftChild();
		FindMin(node);
	}
}

void cBTNodeTree::InOrderHelper(cBTNode* node)
{
	//	Recursively traverse the tree in order
	if (node == nullptr)
		return;

	InOrderHelper(node->GetLeftChild());
	DisplayNode(node->GetData());
	InOrderHelper(node->GetRightChild());
}

bool cBTNodeTree::IsBSTHelper(cBTNode* root)
{
	//	Recursively check if the tree / subtree is BST
	if (root == nullptr)
	{
		return true;	//	A null tree is considered as a BST
	}

	//	For all other scenarios
	//	Case I: Leaf
	if (root->IsLeaf())
	{
		return true;	//	A leaf is, of course, the minimum BST
	}
	//	Case II: Others
	else
	{
		//	Check the left child
		if (root->GetLeftChild() != nullptr)
		{
			if (root->GetLeftChild()->GetData() < root->GetData())
			{
				//	Continue check the left subtree
				return IsBSTHelper(root->GetLeftChild());
			}
			else
				return false;
		}
		//	Check the right child
		if (root->GetRightChild() != nullptr)
		{
			if (root->GetRightChild()->GetData() > root->GetData())
			{
				//	Continue check the right subtree
				return IsBSTHelper(root->GetRightChild());
			}
			else
				return false;
		}
	}
	return false;
}

void cBTNodeTree::MakeNonBST()
{
	//	To test IsBST() we must make a non-BS tree
	//	By simply swap the value of the root with left children
	//	If left child is nullptr, we create one
	if (m_Root == nullptr)
		return;

	if (m_Root->GetLeftChild() != nullptr)
	{
		float temp = m_Root->GetData();
		m_Root->SetData(m_Root->GetLeftChild()->GetData());
		m_Root->GetLeftChild()->SetData(temp);
	}
	else
	{
		cBTNode* temp = new cBTNode(m_Root->GetData() + 100);
		m_Root->SetLeftChild(temp);
	}
	return;
}

void cBTNodeTree::PrintNodeInRange(const float& lower, const float& upper)
{
	PrintNodeInRangeHelper(lower, upper, m_Root);
	return;
}

void cBTNodeTree::PrintNodeInRangeHelper(
	const float& lower, const float& upper, cBTNode* root)
{
	//	nullptr
	if (root == nullptr)
		return;
	//	Inorder Traversal
	if (root->GetData() <= upper && root->GetData() >= lower)
	{
		//	Print out the result
		std::cout << root->GetData() << ", ";
		PrintNodeInRangeHelper(lower, upper, root->GetLeftChild());
		PrintNodeInRangeHelper(lower, upper, root->GetRightChild());
	}
	else if (root->GetData() >= upper)
	{
		PrintNodeInRangeHelper(lower, upper, root->GetLeftChild());
	}
	else if (root->GetData() <= lower)
	{
		PrintNodeInRangeHelper(lower, upper, root->GetRightChild());
	}
	return;
}

void cBTNodeTree::SaveHelper(std::list<float>& ls, cBTNode* root)
{
	//	Preorder traverse and save the elements into ls
	if (root == nullptr)	return;
	ls.push_back(root->GetData());
	SaveHelper(ls, root->GetLeftChild());
	SaveHelper(ls, root->GetRightChild());
}

void cBTNodeTree::LoadOriginal(std::list<float>& ls)
{
	//	Load and restore original shape
	while (ls.size() > 0)
	{
		m_Root = LoadOriginalHelper(ls.front(), m_Root);
		ls.pop_front();
	}
}

cBTNode* cBTNodeTree::LoadOriginalHelper(float f,
	cBTNode* root)
{
	cBTNode* node = new cBTNode();
	if (root == nullptr)
	{
		root = new cBTNode(f);
		return root;
	}
	//	root is NOT nullptr
	cBTNode* left = root->GetLeftChild();
	cBTNode* right = root->GetRightChild();
	if (f < root->GetData())
	{
		left = LoadOriginalHelper(f, left);
		root->SetLeftChild(left);
	}
	else
	{
		right = LoadOriginalHelper(f, right);
		root->SetRightChild(right);
	}
	return root;
}


cBTNode* cBTNodeTree::LoadBalancedHelper(std::list<float>& ls,
	cBTNode* root)
{
	cBTNode* temp = new cBTNode();
	//	Stopping Condition I:
	if (ls.size() <= 0)
		return nullptr;

	//	Stopping Condition II:
	if (ls.size() == 1)
	{
		temp->SetData(ls.front());
		return temp;
	}

	//	When we have at least 2 elements in the list
	//	Step 1: Locate the middle element
	cBTNode* left = temp->GetLeftChild();
	cBTNode* right = temp->GetRightChild();
	if (ls.size() % 2 == 0)
	{
		//	Even numbers of elements
		int middle = ls.size() / 2;
		std::list<float> ls_left;
		std::list<float> ls_right;
		int index = 0;

		while (index < middle)
		{
			ls_left.push_back(ls.front());
			ls.pop_front();
		}
		//	Now we reach the middle element
		temp->SetData(ls.front());
		ls.pop_front();
		//	The rest is actually ls_right
		while (ls.size() > 0)
		{
			ls_right.push_back(ls.front());
			ls.pop_front();
		}
		//	Now we have the root and two lists


	}
}

void cBTNodeTree::LoadBalanced(std::list<float>& ls,
	cBTNode*& root)
{
	std::cout << "Height is " << GetHeightNonR() << std::endl;
	//	Stopping Condition I:
	if (ls.size() <= 0)
	{
		root = nullptr;
		return;
	}

	//	Stopping Condition II:
	if (ls.size() == 1)
	{
		root = new cBTNode(ls.front());
		return;
	}

	//	When we have at least 2 elements in the list
	//	Step 1: Locate the index of middle element

	int middle = (ls.size() - 1) / 2;
	std::list<float> ls_left;
	std::list<float> ls_right;
	int index = 0;
	
	//	Step 2: Get ls_left, middle element and ls_right
	while (index < middle)
	{
		ls_left.push_back(ls.front());
		ls.pop_front();
		index += 1;
	}
	//	Now we reach the middle element
	root = new cBTNode(ls.front());
	std::cout << root->GetData() << " ";
	ls.pop_front();
	//	The rest is actually ls_right
	while (ls.size() > 0)
	{
		ls_right.push_back(ls.front());
		ls.pop_front();
	}
	//	Now we have the root and two lists
	cBTNode* left = root->GetLeftChild();
	cBTNode* right = root->GetRightChild();
	if (ls_left.size() > 0)
	{
		LoadBalanced(ls_left, left);
		root->SetLeftChild(left);
	}
	else
	{
		left = nullptr;
	}
	if (ls_right.size() > 0)
	{
		LoadBalanced(ls_right, right);
		root->SetRightChild(right);
	}
	else
	{
		right = nullptr;
	}
	//}
}

cBTNode* cBTNodeTree::LoadBalancedPtr(std::list<float>& ls,
	cBTNode* root)
{
	//	Stopping Condition I:
	if (ls.size() <= 0)
	{
		return nullptr;
	}

	//	Stopping Condition II:
	if (ls.size() == 1)
	{
		cBTNode* node = new cBTNode(ls.front());
		return node;
	}

	//	When we have at least 2 elements in the list
	//	Step 1: Locate the index of middle element

	int middle = (ls.size() - 1) / 2;
	std::list<float> ls_left;
	std::list<float> ls_right;
	int index = 0;

	//	Step 2: Get ls_left, middle element and ls_right
	while (index < middle)
	{
		ls_left.push_back(ls.front());
		ls.pop_front();
		index += 1;
	}
	//	Now we reach the middle element
	cBTNode* node = new cBTNode(ls.front());
	ls.pop_front();
	//	The rest is actually ls_right
	while (ls.size() > 0)
	{
		ls_right.push_back(ls.front());
		ls.pop_front();
	}
	//	Now we have the root and two lists
	cBTNode* left = node->GetLeftChild();
	cBTNode* right = node->GetRightChild();
	if (ls_left.size() > 0)
	{
		left = LoadBalancedPtr(ls_left, left);
		node->SetLeftChild(left);
	}
	else
	{
		left = nullptr;
	}
	if (ls_right.size() > 0)
	{
		right = LoadBalancedPtr(ls_right, right);
		node->SetRightChild(right);
	}
	else
	{
		right = nullptr;
	}
	return node;
}

void cBTNodeTree::DisplayLevel()
{
	//	Level order travesal (Single List Version)
	//	We will store the nodes of every LEVEL into a container
	//	And loop through the container to locate the nodes of next level
	//	We will also remove the nodes of last level from the container
	//	After each remove height+= 1
	//	Stop until the container is null (no next level)
	std::list<cBTNode*> level;

	if (m_Root == nullptr && level.size() == 0)
		return;

	std::cout << m_Root->GetData() << std::endl;
	level.push_back(m_Root);
	while (1)
	{
		int temp = level.size();
		while (temp > 0)
		{
			if (level.front()->GetLeftChild() != nullptr)
				level.push_back(level.front()->GetLeftChild());
			if (level.front()->GetRightChild() != nullptr)
				level.push_back(level.front()->GetRightChild());
			level.pop_front();	//	Only pop the current level nodes
			temp -= 1;
		}
		if (level.empty())
			break;
		else
		{
			//	Display this level
			for (auto i : level)
			{
				std::cout << i->GetData() << " ";
			}
			std::cout << std::endl;
		}
	}
	return;
}

int cBTNodeTree::BalanceFactor()
{
	//	Return the difference between the heights of two subtrees
	if (m_Root == nullptr)
		return 0;

	int left, right;	
	if (m_Root->GetLeftChild() == nullptr)
		left = 0;
	else
		left = GetHeight(m_Root->GetLeftChild());

	if (m_Root->GetRightChild() == nullptr)
		right = 0;
	else
		right = GetHeight(m_Root->GetRightChild());
	std::cout << left << " " << right << std::endl;

	return left - right;
}

//cBTNode* cBTNodeTree::FindLargestBSTHelper(cBTNode* root, int& max)
//{
//	if (IsBSTHelper(root))
//	{
//		std::cout << root->GetData() << " is BST" << std::endl;
//		int height = GetHeight(root);
//		if (height > max)
//		{
//			max = height;
//			return root;
//		}
//		//	ERROR: No return if height <= max
//	}
//	else
//	{
//		cBTNode* leftmax = new cBTNode();
//		cBTNode* rightmax = new cBTNode();
//
//		if (root->GetLeftChild() != nullptr)
//		{
//			std::cout << root->GetLeftChild()->GetData() << ": left" << std::endl;
//			leftmax = FindLargestBSTHelper(root->GetLeftChild(), max);
//			std::cout << leftmax->GetData() << " Left max " << std::endl;
//		}
//		
//		if (root->GetRightChild() != nullptr)
//		{
//			rightmax = FindLargestBSTHelper(root->GetRightChild(), max);
//		}
//		if (GetHeight(leftmax) >= GetHeight(rightmax))
//		{
//			return leftmax;
//		}
//		else
//		{
//			return rightmax;
//		}
//	}
//}

void cBTNodeTree::FindLargestBSTHelper(cBTNode* root, int& max)
{
	if (IsBSTHelper(root))
	{
		std::cout << root->GetData() << " is BST" << std::endl;
		int height = GetHeight(root);
		if (height > max)
		{
			max = height;
		}
		//	ERROR: No return if height <= max
	}
	else
	{
		if (root->GetLeftChild() != nullptr)
		{
			FindLargestBSTHelper(root->GetLeftChild(), max);
		}

		if (root->GetRightChild() != nullptr)
		{
			FindLargestBSTHelper(root->GetRightChild(), max);
		}
	}
}

void cBTNodeTree::FindLargestBST()
{
	int max = 0;
	FindLargestBSTHelper(m_Root, max);
	std::cout << "Maximum is: " << max << std::endl;
}

void cBTNodeTree::PrintTwoBST(cBTNode* root1, cBTNode* root2)
{
	std::vector<float> vBST1 = BST2Array(root1);
	std::vector<float> vBST2 = BST2Array(root2);
	MergeArray(vBST1, vBST2);
	for (auto i : vBST1)
	{
		std::cout << i << ", ";
	}
	std::cout << std::endl;
}

std::vector<float> cBTNodeTree::BST2Array(cBTNode* root)
{
	std::vector<float> vBST;
	//	Inorder traverse
	BST2ArrayHelper(m_Root, vBST);
	return vBST;
}

void cBTNodeTree::BST2ArrayHelper(cBTNode* root, std::vector<float>& vbst)
{
	if (root == nullptr)
	{
		return;
	}
	BST2ArrayHelper(root->GetLeftChild(), vbst);
	vbst.push_back(root->GetData());
	BST2ArrayHelper(root->GetRightChild(), vbst);
}

void cBTNodeTree::MergeArray(std::vector<float>& vbst1,
	std::vector<float> vbst2)
{
	//	Insert vbst2 into vbst1
	std::vector<float>::iterator it = vbst2.begin();
	for (; it != vbst2.end(); it++)
	{
		vbst1.insert(
			std::upper_bound(vbst1.begin(), vbst1.end(), *it),
			*it);
	}
}

cBTNodeTree* cBTNodeTree::BT2BST()
{
	cBTNodeTree* output = new cBTNodeTree();
	BT2BSTHelper(m_Root, output);
	return output;
}

void cBTNodeTree::BT2BSTHelper(cBTNode* input, cBTNodeTree*& output)
{
	if (input == nullptr)
	{
		return;
	}
	
	BT2BSTHelper(input->GetLeftChild(), output);
	output->Insert(input->GetData());
	BT2BSTHelper(input->GetRightChild(), output);
}

cBTNode* cBTNodeTree::BalanceInsert(cBTNode* root, cBTNode* newnode)
{
	if (root == nullptr)
	{
		float data = newnode->GetData();
		cBTNode* temp = new cBTNode(data);
		return temp;
	}

	cBTNode* left = root->GetLeftChild();
	cBTNode* right = root->GetRightChild();
	if (newnode->GetData() <= root->GetData())
	{
		left = BalanceInsert(left, newnode);
		root->SetLeftChild(left);
	}
	else
	{
		right = BalanceInsert(right, newnode);
		root->SetRightChild(right);
	}
	return root;
}