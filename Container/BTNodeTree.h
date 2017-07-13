#ifndef BTNODETREE_
#define BTNODETREE_

#include <list>
#include <vector>
#include "BTNode.h"

class cBTNodeTree
{
public:
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

	//	Section 16.4 of Mirror and Wall
	void Save(std::list<float>& ls)
	{
		SaveHelper(ls, m_Root);
	}
	void SaveHelper(std::list<float>& ls, cBTNode* root);
	void LoadOriginal(std::list<float>& ls);
	cBTNode* LoadOriginalHelper(float f,
		cBTNode* root);
	//	Load a list of float into a balanced BST
	//	Two methods are virtually the same
	//	First one will modify the root directly
	//	Second one returns the root
	void LoadBalanced(std::list<float>& ls, cBTNode*& root);
	cBTNode* LoadBalancedPtr(std::list<float>& ls, cBTNode* root);
	void LoadBalancedMain(std::list<float>& ls)
	{
		LoadBalanced(ls, m_Root);
	}
	void LoadBalancedPtrMain(std::list<float>& ls)
	{
		m_Root = LoadBalancedPtr(ls, m_Root);
	}
	cBTNode* LoadBalancedHelper(std::list<float>& ls, cBTNode* root);

	//	Display the BST level by level
	void DisplayLevel();
	//	Check the difference between heights of left and right
	int BalanceFactor();

	//	Find the largest BST subtree of a BT
	//	Report the height and return the pointer to the root
	//cBTNode* FindLargestBSTHelper(cBTNode* root, int& max);
	void FindLargestBSTHelper(cBTNode* root, int& max);
	void FindLargestBST();

	//	Print the elements of 2 BST in sorted order
	//	We will generate a sorted vector of ls_a
	//	and generate sorted vector for ls_b, and merge them
	void PrintTwoBST(cBTNode* root1, cBTNode* root2);
	std::vector<float> BST2Array(cBTNode* root);
	void BST2ArrayHelper(cBTNode* root, std::vector<float>& vbst);
	void MergeArray(std::vector<float>& vbst1, std::vector<float> vbst2);

	//	BT to BST
	//	My method is to do an inorder traverse
	//	and push the values into a second tree
	cBTNodeTree* BT2BST();
	void BT2BSTHelper(cBTNode* input, cBTNodeTree*& output);
	cBTNode* BalanceInsert(cBTNode* root, cBTNode* newnode);
};

#endif