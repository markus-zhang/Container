#ifndef BTNODETREE_
#define BTNODETREE_

#include <list>
#include "BTNode.h"

class cBTNodeTree
{
private:
	cBTNode* m_Root;
public:
	//	Constructor + Destructor
	cBTNodeTree() : m_Root(nullptr) {}
	cBTNodeTree(const float& data)
	{
		m_Root = new cBTNode(data);
	}
	cBTNodeTree(cBTNode* root)
	{
		m_Root = root;
	}
	~cBTNodeTree() {}

	//	Utility
	int GetHeight(cBTNode* root);
	int GetHeightNonR();
	int GetHeightNonRV2();
	cBTNode* SearchHelper(cBTNode* node, const float& data);
	cBTNode* FindMax(cBTNode* node);
	cBTNode* FindMin(cBTNode* node);
	void InOrderHelper(cBTNode* node);
	void DisplayNode(const float& data)
	{
		std::cout << data << std::endl;
	}

	//	Getter and Setter
	cBTNode* GetRoot() const
	{
		return m_Root;
	}

	//	Binary Search Tree
	cBTNode* InsertHelper(cBTNode* tree, const float& data);
	void Insert(const float& data)
	{
		m_Root = InsertHelper(m_Root, data);
	}

	void TraverseLevel();
	cBTNode* Search(const float& data)
	{
		return SearchHelper(m_Root, data);
	}
	void Deletion(const float& data);

	//	Find the inorder predecessor and successor of given node
	void FindPreSucc(cBTNode* node, float data);
	void InOrderDisplay()
	{
		InOrderHelper(m_Root);
	}
};

#endif