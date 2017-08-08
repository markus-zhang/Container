#ifndef TRITREE_H_
#define TRITREE_H_

#include "TriNode.h"

template<typename T>
class TriTree
{
private:
	TriNode<T>* root;
protected:
	void inOrderTraverseHelper(TriNode<T>* root);
public:
	TriTree();
	
	void inOrderTraverse();
};

template<typename T>
void TriTree<T>::inOrderTraverseHelper(TriNode<T>* root)
{
	if (root == nullptr)
		return;

	if (root->isLeaf())
	{
		//	Display items
		std::cout << "Small: " << root->getSmall() << ", Large: " << root->getLarge() << std::endl;
	}
	else
	{

	}
}

#endif
