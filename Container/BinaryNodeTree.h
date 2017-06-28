#ifndef BINARYNODETREE_
#define BINARYNODETREE_

#include "BinaryTreeInterface.h"
#include "BinaryNode.h"

template<class DataType>
class BinaryNodeTree : public BinaryTreeInterface<DataType>
{
private:
	BinaryNode<DataType>* m_Root;
protected:
	//	Helper Functions
	int GetHeightHelper(BinaryNode<DataType>* treeptr) const;
	int GetNumNodesHelper(BinaryNode<DataType>* treeptr) const;

	//	Destroy all nodes from this tree
	void DestroyTree(BinaryNode<DataType>* treeptr);

	//	Recursively adds a new node to keep balanced
	BinaryNode<DataType>* BalanceAdd(BinaryNode<DataType>* treeptr,
		BinaryNode<DataType>* newnodeptr);

	//	Remove the target value by calling MoveValueUpTree
	//	to overwrite value with child's value
	//BinaryNode<DataType>* RemoveValue(BinaryNode<DataType>* subtreeptr,
		//const DataType targetdata, bool& success);

	//	Copy values up the tree to overwrite value in current
	//	node until a leaf is reached; the leaf is removed
	//	subsequently as it's value is now stored in the parent
	//BinaryNode<DataType>* MoveValueUpTree(BinaryNode<DataType>* subtreeptr);

	//	Recursively searches for target value in the tree
	//	by using PREORDER traversal
	//BinaryNode<DataType>* FindNode(BinaryNode<DataType>* targetree,
		//const DataType& targetdata, bool& success) const;

	//	Copies the tree rooted at treeptr and returns a pointer
	//	to the copy
	BinaryNode<DataType>* CopyTree(const BinaryNode<DataType>* treeptr) const;
	void CopyTreeAlter(const BinaryNode<DataType>* treeptr) const;


	//	Helper Function
	void PreOrderHelper(void Process(DataType&),
		BinaryNode<DataType>* treeptr) const;
	void InOrderHelper(void Process(DataType&),
		BinaryNode<DataType>* treeptr) const;
	void PostOrderHelper(void Process(DataType&),
		BinaryNode<DataType>* treeptr) const;
public:
	BinaryNodeTree();
	BinaryNodeTree(const DataType& root);
	BinaryNodeTree(const DataType& root,
		const BinaryNodeTree<DataType>* lefttree,
		const BinaryNodeTree<DataType>* righttree);
	virtual ~BinaryNodeTree();

	//	Methods
	bool IsEmpty() const;
	int GetHeight() const;
	int GetNumNodes() const;
	DataType GetRootData() const;
	void SetRooetData(const DataType& newdata);
	bool Add(const DataType& newdata);
	bool Remove(const DataType& data);
	void Clear();
	DataType GetEntry(const DataType& data) const;
	bool Locate(const DataType& data) const;

	//	Public Traversals Function
	void PreOrder(void Process(DataType&)) const;
	void InOrder(void Process(DataType&)) const;
	void InOrderNonR(void Process(DataType&)) const;
	void PostOrder(void Process(DataType&)) const;

	//	Overload Operator
	//BinaryNodeTree& operator=(const BinaryNodeTree& RightHandSide);
}; 

#include "BinaryNodeTree.cpp"
#endif

