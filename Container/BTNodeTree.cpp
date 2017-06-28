#include <stack>
#include <iostream>
#include "BTNodeTree.h"

int cBTNodeTree::GetHeight(cBTNode* root)
{
	//	Recursive method to get height
	if (root == nullptr)
	{
		return 0;
	}

	return (GetHeight(root->GetLeftChild()) >= GetHeight(root->GetLeftChild())
		? 1 + GetHeight(root->GetLeftChild())
		: 1 + GetHeight(root->GetRightChild()));
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
	std::cout << node->GetData() << " ";
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
		FindMax(node);
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