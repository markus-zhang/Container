#ifdef BINARYNODETREE_
#include <stack>
//#include "BinaryNodeTree.h"

template <class DataType>
BinaryNodeTree<DataType>::BinaryNodeTree() : m_Root(nullptr)
{}

template <class DataType>
BinaryNodeTree<DataType>::BinaryNodeTree(const DataType& root)
{
	m_Root = new BinaryNode<DataType>(root, nullptr, nullptr);
}

template <class DataType>
BinaryNodeTree<DataType>::BinaryNodeTree(const DataType& root,
	const BinaryNodeTree<DataType>* lefttree,
	const BinaryNodeTree<DataType>* righttree)
{
	m_Root = new BinaryNode<DataType>(root,
		CopyTree(lefttree->m_Root), CopyTree(righttree->m_Root));
}	//	Deep copy is used here

template <class DataType>
BinaryNodeTree<DataType>::~BinaryNodeTree()
{
	DestroyTree(m_Root);
}


template<class DataType>
BinaryNode<DataType>* BinaryNodeTree<DataType>::CopyTree(
	const BinaryNode<DataType>* tree) const
{
	//	Use Recursion to copy tree and return root ptr
	BinaryNode<DataType>* newtree = nullptr;

	if (tree != nullptr)
	{
		newtree = new BinaryNode<DataType>* (tree->GetData(),
			nullptr, nullptr);
		newtree->SetLeftChild() = CopyTree(tree->GetLeftChild());
		newtree->SetRightChild() = CopyTree(tree->GetRightChild);
	}

	return newtree;
}

template <class DataType>
void BinaryNodeTree<DataType>::CopyTreeAlter(const BinaryNode<DataType>* treeptr) const
{
	if (treeptr == nullptr)
		return;

	//	Deep-copy the root element
	m_Root = new BinaryNode<DataType>* (treeptr->GetData());

	//	Deep-copy the subtree elements until nullptr
	//	I don't know how to achieve this
}	

template <class DataType>
void BinaryNodeTree<DataType>::DestroyTree(BinaryNode<DataType>* treeptr)
{
	if (treeptr != nullptr)
	{
		DestroyTree(treeptr->GetLeftChild());
		DestroyTree(treeptr->GetRightChild());
		delete treeptr;
	}
}

template <class DataType>
int BinaryNodeTree<DataType>::GetHeightHelper(BinaryNode<DataType>* treeptr) const
{
	if (treeptr == nullptr)
		return 0;
	else
	{
		if (GetHeightHelper(treeptr->GetLeftChild())
			>= GetHeightHelper(treeptr->GetRightChild()))
		{
			return 1 + GetHeightHelper(treeptr->GetLeftChild());
		}
		else
		{
			return 1 + GetHeightHelper(treeptr->GetRightChild());
		}
	}	
}

template <class DataType>
int BinaryNodeTree<DataType>::GetNumNodesHelper(BinaryNode<DataType>* treeptr) const
{
	if (treeptr == nullptr)
		return 0;
	else
		return 1 + GetNumNodesHelper(treeptr->GetLeftChild()) + GetNumNodesHelper(treeptr->GetRightChild());
}

template <class DataType>
BinaryNode<DataType>* BinaryNodeTree<DataType>::BalanceAdd(
	BinaryNode<DataType>* treeptr, BinaryNode<DataType>* newnodeptr)
{
	//	Recursively put new node into shorter branch
	if (treeptr == nullptr)
	{
		//	Stop recursion here
		treeptr = new BinaryNode<DataType>* (newnodeptr->GetData());
		return treeptr;
	}
	else
	{
		//	We need these two temporary pointers
		//	Because BalanceAdd returns pointers
		//	And we need to link the returned pointer
		//	to the parent pointer

		BinaryNode<DataType>* left = treeptr->GetLeftChild();
		BinaryNode<DataType>* right = treeptr->GetRightChild();

		//	Since we don't know which branch is longer
		if (GetNumNodesHelper(treeptr->GetLeftChild()) >= GetNumNodesHelper(treeptr->GetRightChild()))
		{
			//	Left Branch is longer, then we put into right branch
			//	Notice that ultimately the "last" right
			//	which is nullptr, will be filled with
			//	the data contained by newnodeptr

			right = BalanceAdd(treeptr->GetRightChild(), newnodeptr);

			//	Once returned from BalanceAdd(Right, newnode)
			//	And if right is null before BalanceAdd
			//	right will now be newnode
			//	So we need to reset rightchild of treeptr
			//	But if Right is NOT null
			//	Then Right won't change (goes deeper to find a nullptr to insert)
			//	Anyway reseting doesn't hurt

			treeptr->SetRightChild(right);
		}
		else
		{
			left = BalanceAdd(treeptr->GetLeftChild(), newnodeptr);
			treeptr->SetLeftChild(left);
		}

		//	Suppose either right is null BEFORE
		//	this call, then at this point it
		//	is already filled with new data
		//
		//	Now where does "return treeptr" go back?
		//
		//	Remember treeptr is the parent node of new data
		//	and we didn't change treeptr (because it's not nullptr)
		//
		//	Obvious it goes back to the last call
		//	So in THE LAST CALL (upper level)
		//	we obviously didn't fill any new data
		//	otherwise we don't need this call, right?
		//
		//	Which means THE LAST left or right (we don't know which one)
		//	will be this treeptr
		//	Assume left = BalanceAdd(treeptr->GetLeftChild(), newnodeptr);
		//	then THE LAST left = treeptr of THIS CALL
		//	And this treeptr = LAST treeptr->GetLeftChild()
		//	Which means THE LAST left does not change at all
		//	Why? Because left = treeptr->GetLeftChild() by definition
		//
		//	You may ask, then why do we need to return treeptr at all?
		//	Because we need to do 
		//	treeptr->SetLeftChild(left);
		//	once left or right is nullptr and get modified
		//	in the NEXT CALL
		//	It's a bit lazy as we ONLY need to SetLeftChild()
		//	when left actually changes from nullptr to something new

		return treeptr;
	}
}

template <typename DataType>
void BinaryNodeTree<typename DataType>::PreOrderHelper(
	void Process(DataType&), BinaryNode<DataType>* treeptr) const
{
	if (treeptr == nullptr)
		return;
	DataType temp = treeptr->GetData();
	Process(temp);
	InOrderHelper(Process, treeptr->GetLeftChild());
	InOrderHelper(Process, treeptr->GetLeftChild());
}

template <typename DataType>
void BinaryNodeTree<typename DataType>::InOrderHelper(
	void Process(DataType&), BinaryNode<DataType>* treeptr) const
{
	if (treeptr == nullptr)
		return;
	InOrderHelper(Process, treeptr->GetLeftChild());
	DataType temp = treeptr->GetData();
	Process(temp);
	InOrderHelper(Process, treeptr->GetLeftChild());

}

template <typename DataType>
void BinaryNodeTree<DataType>::PostOrderHelper(
	void Process(DataType&), BinaryNode<DataType>* treeptr) const
{
	if (treeptr == nullptr)
		return;
	InOrderHelper(Process, treeptr->GetLeftChild());
	InOrderHelper(Process, treeptr->GetLeftChild());
	DataType temp = treeptr->GetData();
	Process(temp);
}

template <typename DataType>
void BinaryNodeTree<DataType>::PreOrder(void Process(DataType&)) const
{
	PreOrderHelper(Process, m_Root);
}

template <typename DataType>
void BinaryNodeTree<DataType>::InOrder(void Process(DataType&)) const
{
	InOrderHelper(Process, m_Root);
}

template <typename DataType>
void BinaryNodeTree<DataType>::PostOrder(void Process(DataType&)) const
{
	PostOrderHelper(Process, m_Root);
}

template <typename DataType>
void BinaryNodeTree<DataType>::InOrderNonR(void Process(DataType&)) const
{
	//	Algorithm:
	//	Keep a stack<BinaryNode<DataType>*> as reference
	//	Start from the root, i.e. curptr = m_Root
	//	If curptr == nullptr && stack is empty, end
	//	If curptr != nullptr, push into stack
	//	If curptr == nullptr && stack is NOT empty,
	//	then we set curptr = stack.top()->GetRight()
	//	Process stack.top(), and pop stack
	//	Possible optimization: If node is leaf, then just Process

	std::stack<BinaryNode<DataType>*> recursion;
	BinaryNode<DataType>* curptr = nullptr;

	curptr = m_Root;
	while (1)
	{
		if (curptr == nullptr && recursion.size == 0)
			break;
		else
		{
			if (curptr != nullptr)
			{
				recursion.push(curptr);
				curptr = curptr->GetLeftChild();
			}
			else
			{
				curptr = recursion.top();				
				DataType temp = curptr->GetData();
				Process(temp);
				curptr = curptr->GetRightChild();
				recursion.pop();
			}
		}
	}
}

template <typename DataType>
bool BinaryNodeTree<DataType>::Add(const DataType& newdata)
{
	return true;
}

template <typename DataType>
bool BinaryNodeTree<DataType>::Remove(const DataType& data)
{
	return true;
}

template <typename DataType>
void BinaryNodeTree<DataType>::Clear()
{
	//	Some code here
}

template <typename DataType>
DataType BinaryNodeTree<DataType>::GetEntry(const DataType& data) const
{
	//	temp code
	return m_Root->GetData();
}

template <typename DataType>
bool BinaryNodeTree<DataType>::Locate(const DataType& data) const
{
	return true;
}

template <typename DataType>
bool BinaryNodeTree<DataType>::IsEmpty() const
{
	return (m_Root == nullptr ? false :	true);
}

template <typename DataType>
int BinaryNodeTree<DataType>::GetHeight() const
{
	return 0;
}

template <typename DataType>
int BinaryNodeTree<DataType>::GetNumNodes() const
{
	return 0;
}

template <typename DataType>
DataType BinaryNodeTree<DataType>::GetRootData() const
{
	return m_Root->GetData();
}

template <typename DataType>
void BinaryNodeTree<DataType>::SetRootData(const DataType& newdata)
{
	m_Root->SetData(newdata);
}

#endif