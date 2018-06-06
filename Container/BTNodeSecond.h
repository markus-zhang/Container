#ifndef BTNS_H_
#define BTNS_H_

#include <memory>
#include <utility>

template<typename T>
class cBTNodeSecond
{
public:
	std::unique_ptr<cBTNodeSecond> m_LeftChild;
	std::unique_ptr<cBTNodeSecond> m_RightChild;
	T m_Data;
public:
	cBTNodeSecond(const T& data) :
		m_Data(data)
	{}
	cBTNodeSecond(const T& data,
		std::unique_ptr<cBTNodeSecond> leftchild,
		std::unique_ptr<cBTNodeSecond> rightchild);

	//	Utilities
	bool isLeaf();

	void setData(const T& data);
	void setLeftChild(std::unique_ptr<cBTNodeSecond> leftchild);
	void setRightChild(std::unique_ptr<cBTNodeSecond> rightchild);

	// Placeholder for accessors
};

template<typename T>
cBTNodeSecond<T>::cBTNodeSecond(const T& data,
	std::unique_ptr<cBTNodeSecond> leftchild,
	std::unique_ptr<cBTNodeSecond> rightchild)
{
	m_Data = data;
	m_LeftChild = std::move(leftchild);
	m_RightChild = std::move(rightchild);
}

template<typename T>
bool cBTNodeSecond<T>::isLeaf()
{
	return (m_LeftChild == m_RightChild == nullptr);
}

template<typename T>
void cBTNodeSecond<T>::setData(const T& data)
{
	m_Data = data;
}

template<typename T>
void cBTNodeSecond<T>::setLeftChild(
	std::unique_ptr<cBTNodeSecond> leftchild)
{
	m_LeftChild = std::move(leftchild);
}

template<typename T>
void cBTNodeSecond<T>::setRightChild(
	std::unique_ptr<cBTNodeSecond> rightchild)
{
	m_LeftChild = std::move(rightchild);
}
#endif


