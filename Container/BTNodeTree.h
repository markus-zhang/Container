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
	cBTNode* FindNodePreHelper(cBTNode* node, float data);
	cBTNode* FindNodeSuccHelper(cBTNode* node, float data);
	cBTNode* DeletionHelper(const float& data, cBTNode* root);
	bool IsBSTHelper(cBTNode* root);
	void MakeNonBST();	//Break the BST structure for IsBST() test
	void PrintNodeInRangeHelper(
		const float& lower, const float& upper,
		cBTNode* root);
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

	//	Find the inorder predecessor and successor of a number THAT IS NOT IN THE TREE
	void FindPreSucc(cBTNode* node, float data);

	//	Find the pre and succ for a node
	cBTNode* FindNodePre(float data)
	{
		return FindNodePreHelper(m_Root, data);
	}
	cBTNode* FindNodeSucc(float data)
	{
		return FindNodeSuccHelper(m_Root, data);
	}
	void InOrderDisplay()
	{
		InOrderHelper(m_Root);
	}
	bool IsBST()
	{
		return IsBSTHelper(m_Root);
	}
	void PrintNodeInRange(const float& lower, const float& upper);
};

#endif