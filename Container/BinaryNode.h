#ifndef BINARYNODE_
#define BINARYNODE_

template<class DataType>
class BinaryNode
{
private:
	DataType m_Data;
	BinaryNode<DataType>* m_LeftChild;
	BinaryNode<DataType>* m_RightChild;
public:
	BinaryNode();
	BinaryNode(const DataType& newdata);
	BinaryNode(const DataType& newdata,
		BinaryNode<DataType>* leftchild,
		BinaryNode<DataType>* rightchild);

	void SetData(const DataType& newdata);
	DataType GetData();

	bool IsLeaf();

	BinaryNode<DataType>* GetLeftChild();
	BinaryNode<DataType>* GetRightChild();

	void SetLeftChild(BinaryNode<DataType>* leftchild);
	void SetRightChild(BinaryNode<DataType>* rightchild);
};

#include "BinaryNode.cpp"

#endif

