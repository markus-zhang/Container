#include "BinaryNode.h"

template<class DataType>
BinaryNode<DataType>::BinaryNode()
{

}

template<class DataType>
BinaryNode<DataType>::BinaryNode(const DataType& newdata)
{
	m_Data = newdata;
	m_LeftChild = m_RightChild = nullptr;
}

template<class DataType>
BinaryNode<DataType>::BinaryNode(const DataType& newdata,
	BinaryNode<DataType>* leftchild,
	BinaryNode<DataType>* rightchild)
{
	m_Data = newdata;
	m_LeftChild = leftchild;
	m_RightChild = rightchild;
}

template<class DataType>
void BinaryNode<DataType>::SetData(const DataType& newdata)
{
	m_Data = newdata;
}

template<class DataType>
DataType BinaryNode<DataType>::GetData()
{
	return m_Data;
}

template<class DataType>
bool BinaryNode<DataType>::IsLeaf()
{

}

template<class DataType>
BinaryNode<DataType>* BinaryNode<DataType>::GetLeftChild()
{
	return m_LeftChild;
}

template<class DataType>
BinaryNode<DataType>* BinaryNode<DataType>::GetRightChild()
{
	return m_RightChild;
}