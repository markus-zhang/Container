#ifndef TRINODE_H_
#define TRINODE_H_

template<typename T>
class TriNode
{
private:
	T small, large;
	TriNode<T>* leftChild;
	TriNode<T>* midChild;
	TriNode<T>* rightChild;
public:
	TriNode();
	TriNode(const T& item);
	TriNode(const T& item, TriNode<T>* left, TriNode<T>* mid,
		TriNode<T>* right);

	bool isLeaf() const;
	bool isTwoNode() const;
	bool isThreeNode() const;

	T getSmall() const;
	T getLarge() const;

	void setSmall(const T& small);
	void setLarge(const T& large);

	TriNode<T>* getLeftChild() const;
	TriNode<T>* getMidChild() const;
	TriNode<T>* getRightChild() const;

	void setLeftChild(TriNode<T>* left);
	void setMidChild(TriNode<T>* mid);
	void setRightChild(TriNode<T>* right);
};

template<typename T>
TriNode<T>::TriNode()
{
	leftChild = nullptr;
	midChild = nullptr;
	rightChild = nullptr;
}

template<typename T>
TriNode<T>::TriNode(const T& item)
{
	setSmall(item);
	leftChild = nullptr;
	midChild = nullptr;
	rightChild = nullptr;
}

template<typename T>
TriNode<T>::TriNode(const T& item, TriNode* left, TriNode* mid, TriNode* right)
{
	setSmall(item);
	leftChild = left;
	midChild = mid;
	rightChild = right;
}

template<typename T>
bool TriNode<T>::isLeaf() const
{
	return (leftChild == midChild == rightChild == nullptr);
}

template<typename T>
bool TriNode<T>::isTwoNode() const
{
	return false;
}

template<typename T>
bool TriNode<T>::isThreeNode() const
{
	return false;
}

template<typename T>
T TriNode<T>::getSmall() const
{
	return small;
}

template<typename T>
T TriNode<T>::getLarge() const
{
	return large;
}

template<typename T>
void TriNode<T>::setSmall(const T& s)
{
	small = s;
}

template<typename T>
void TriNode<T>::setLarge(const T& l)
{
	large = l;
}

template<typename T>
TriNode<T>* TriNode<T>::getLeftChild() const
{
	return leftChild;
}

template<typename T>
TriNode<T>* TriNode<T>::getMidChild() const
{
	return midChild;
}

template<typename T>
TriNode<T>* TriNode<T>::getRightChild() const
{
	return rightChild;
}

template<typename T>
void TriNode<T>::setLeftChild(TriNode<T>* left)
{
	leftChild = left;
}

template<typename T>
void TriNode<T>::setMidChild(TriNode<T>* mid)
{
	midChild = mid;
}

template<typename T>
void TriNode<T>::setRightChild(TriNode<T>* right)
{
	rightChild = right;
}

#endif

