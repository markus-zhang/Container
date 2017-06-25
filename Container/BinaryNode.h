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
	DataType GetData() const;

	bool IsLeaf() const;

	BinaryNode<DataType>* GetLeftChild() const;
	BinaryNode<DataType>* GetRightChild() const;

	void SetLeftChild(BinaryNode<DataType>* leftchild);
	void SetRightChild(BinaryNode<DataType>* rightchild);
};

#include "BinaryNode.cpp"

#endif

