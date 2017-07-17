//	"Data Abstraction and Problem Solving with C++"
//	Binary Search Tree implementaion

#ifndef CONTAINER_BTN_H_
#define CONTAINER_BTN_H_

template<typename T>
class BTN
{
private:
	T item;
	BTN* leftChild;
	BTN* rightChild;
public:
	//	Constructor and Destructor
	BTN();
	BTN(const T& it);
	BTN(const T& it, BTN* left, BTN* right);
	~BTN();

	//	Accessor and Mutator
	T getItem();
	BTN<T>* getLeftChild();
	BTN<T>* getRightChild();
	void setItem(const T& it);
	void setLeftChild(BTN* left);
	void setRightChild(BTN* right);

	//	Utilities
	bool isLeaf();
};

//	Constructor and Destructor
template<typename T>
BTN<T>::BTN() : leftChild(nullptr), rightChild(nullptr) {}

template<typename T>
BTN<T>::BTN(const T& it) : item(it), leftChild(nullptr), rightChild(nullptr) {}

template<typename T>
BTN<T>::BTN(const T& it, BTN* left, BTN* right) : item(it), leftChild(left), rightChild(right) {}

template<typename T>
BTN<T>::~BTN()
{
	leftChild = nullptr;
	rightChild = nullptr;
}

//	Accessor and Mutator
template<typename T>
T BTN<T>::getItem()
{
	return item;
}

template<typename T>
BTN<T>* BTN<T>::getLeftChild()
{
	return leftChild;
}

template<typename T>
BTN<T>* BTN<T>::getRightChild()
{
	return rightChild;
}

template<typename T>
void BTN<T>::setItem(const T& it)
{
	item = it;
}

template<typename T>
void BTN<T>::setLeftChild(BTN<T>* left)
{
	leftChild = left;
}

template<typename T>
void BTN<T>::setRightChild(BTN<T>* right)
{
	rightChild = right;
}

////	Utilities
template<typename T>
bool BTN<T>::isLeaf()
{
	if (leftChild == nullptr && rightChild == nullptr)
		return true;

	return false;
}

#endif
