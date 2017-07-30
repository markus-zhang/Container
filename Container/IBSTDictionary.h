#ifndef IBSTDICTIONARY_H_
#define IBSTDICTIONARY_H_

#include <algorithm>

template<typename Key, typename Item>
class DictEntry
{
public:
	Item item;
	Key key;
	DictEntry* leftChild;
	DictEntry* rightChild;
protected:
	void setKey(const Key& k);
public:
	DictEntry();
	DictEntry(const Key& k, const Item& i);
	DictEntry(const Key& k, const Item& i,
		DictEntry* leftChild, DictEntry* rightChild);
	~DictEntry();

	Item getItem() const;
	Key getKey() const;
	DictEntry* getLeftChild();
	DictEntry* getRightChild();
	void setItem(const Item& i);
	void setLeftChild(DictEntry* left);
	void setRightChild(DictEntry* right);

	bool isLeaf();

	void displayItem()
	{
		std::cout << item << ", ";
	}

	bool operator==(const DictEntry<Key, Item>& rightHand) const;
	bool operator>(const DictEntry<Key, Item>& rightHand) const;
};

template<typename Key, typename Item>
DictEntry<Key, Item>::DictEntry()
{
	leftChild = nullptr;
	rightChild = nullptr;
}

template<typename Key, typename Item>
DictEntry<Key, Item>::DictEntry(const Key& k, const Item& i)
{
	key = k;
	item = i;
	leftChild = nullptr;
	rightChild = nullptr;
}

template<typename Key, typename Item>
DictEntry<Key, Item>::DictEntry(const Key& k, const Item& i,
	DictEntry<Key, Item>* left, DictEntry<Key, Item>* right)
{
	key = k;
	item = i;
	leftChild = left;
	rightChild = right;
}

template<typename Key, typename Item>
Item DictEntry<Key, Item>::getItem() const
{
	return item;
}

template<typename Key, typename Item>
Key DictEntry<Key, Item>::getKey() const
{
	return key;
}

template<typename Key, typename Item>
DictEntry<Key, Item>* DictEntry<Key, Item>::getLeftChild()
{
	return leftChild;
}

template<typename Key, typename Item>
DictEntry<Key, Item>* DictEntry<Key, Item>::getRightChild()
{
	return rightChild;
}

template<typename Key, typename Item>
void DictEntry<Key, Item>::setItem(const Item& i)
{
	item = i;
}

template<typename Key, typename Item>
void DictEntry<Key, Item>::setLeftChild(DictEntry* left)
{
	leftChild = left;
}

template<typename Key, typename Item>
void DictEntry<Key, Item>::setRightChild(DictEntry* right)
{
	rightChild = right;
}

template<typename Key, typename Item>
bool DictEntry<Key, Item>::isLeaf()
{
	return (leftChild == rightChild);
}

template<typename Key, typename Item>
bool DictEntry<Key, Item>::operator==(const DictEntry<Key, Item>& rightHand) const
{
	return (key == rightHand.getKey());
}

template<typename Key, typename Item>
bool DictEntry<Key, Item>::operator>(const DictEntry<Key, Item>& rightHand) const
{
	return (key > rightHand.getKey());
}

template<typename Key, typename Item>
void DictEntry<Key, Item>::setKey(const Key& k)
{
	key = k;
}

template<typename Key, typename Item>
class IBSTDict
{
private:
	DictEntry<Key, Item>* root;
	int totalNumber;
protected:
	void inOrderDisplayHelper(DictEntry<Key, Item>* root);
	DictEntry<Key, Item>* BSTInsertHelper(
		DictEntry<Key, Item>* root, const Key& k, const Item& i);
	int getHeightHelper(DictEntry<Key, Item>* root);
	DictEntry<Key, Item>* searchHelper(const Key& k,
		DictEntry<Key, Item>* root);
	DictEntry<Key, Item>* removeHelper(const Key& k,
		DictEntry<Key, Item>* root);
	DictEntry<Key, Item>* findPreFromRoot(DictEntry<Key, Item>* root,
		const Key& k);
	DictEntry<Key, Item>* findPredecessorHelper(
		DictEntry<Key, Item>* target);
	DictEntry<Key, Item>* findSuccFromRoot(DictEntry<Key, Item>* root,
		const Key& k);
	DictEntry<Key, Item>* findSuccessorHelper(
		DictEntry<Key, Item>* target);
	
public:
	IBSTDict() : root(nullptr) {}
	IBSTDict(Key k, Item i);

	void inOrderDisplay();
	void BSTInsert(const Key& k, const Item& i);
	int getHeight();
	DictEntry<Key, Item>* search(const Key& k);
	DictEntry<Key, Item>* findPredecessor(const Key& k);
	DictEntry<Key, Item>* findSuccessor(const Key& k);
};

template<typename Key, typename Item>
IBSTDict<Key, Item>::IBSTDict(Key k, Item i)
{
	root = new DictEntry<Key, Item>(k, i);
}

template<typename Key, typename Item>
void IBSTDict<Key, Item>::inOrderDisplayHelper(DictEntry<Key, Item>* root)
{
	//	Traverse the BST in order
	if (root == nullptr)
	{
		return;
	}

	inOrderDisplayHelper(root->getLeftChild());
	//	Must have a displayItem() method for the item
	root->displayItem();
	inOrderDisplayHelper(root->getRightChild());
}

template<typename Key, typename Item>
void IBSTDict<Key, Item>::inOrderDisplay()
{
	inOrderDisplayHelper(root);
}

template<typename Key, typename Item>
DictEntry<Key, Item>* IBSTDict<Key, Item>::BSTInsertHelper(
	DictEntry<Key, Item>* root, const Key& k, const Item& i)
{
	if (root == nullptr)
	{
		DictEntry<Key, Item>* newnode = new DictEntry<Key, Item>(k, i);
		return newnode;
	}
	else
	{
		DictEntry<Key, Item>* left = root->getLeftChild();
		DictEntry<Key, Item>* right = root->getRightChild();

		//	Must have overloaded operator>
		if (root->getItem() > i)
		{
			left = BSTInsertHelper(root->getLeftChild(), k, i);
			root->setLeftChild(left);
		}
		else
		{
			right = BSTInsertHelper(root->getRightChild(), k, i);
			root->setRightChild(right);
		}
		return root;
	}
}

template<typename Key, typename Item>
void IBSTDict<Key, Item>::BSTInsert(const Key& k, const Item& i)
{
	root = BSTInsertHelper(root, k, i);
}

template<typename Key, typename Item>
int IBSTDict<Key, Item>::getHeightHelper(DictEntry<Key, Item>* root)
{
	if (root == nullptr)
		return 0;
	else
	{
		return 1 + max(getHeightHelper(root->getLeftChild()),
			getHeightHelper(root->getLeftChild()));
	}
}

template<typename Key, typename Item>
int IBSTDict<Key, Item>::getHeight()
{
	return getHeightHelper(root);
}

template<typename Key, typename Item>
DictEntry<Key, Item>* IBSTDict<Key, Item>::searchHelper(
	const Key& k, DictEntry<Key, Item>* root)
{
	if (root == nullptr)
		return nullptr;

	if (root->getKey() == k)
		return root;
	else
	{
		if (root->getKey() > k)
		{
			return searchHelper(k, root->getLeftChild());
		}
		else
		{
			return searchHelper(k, root->getRightChild());
		}
	}
}

template<typename Key, typename Item>
DictEntry<Key, Item>* IBSTDict<Key, Item>::search(const Key& k)
{
	return searchHelper(k, root);
}

template<typename Key, typename Item>
DictEntry<Key, Item>* IBSTDict<Key, Item>::findPreFromRoot(
	DictEntry<Key, Item>* root, const Key& k)
{
	//	Special program to locate predecessor from root
	if (root == nullptr)
		return nullptr;
	else
	{
		//				    40
		//          /                  \
		//		35                        55
		//         \                  /
		//		     38           50
		//          /           /     \
		//	       36         45       53
		//                            /
		//                          51
		//	Consider the case of 35: there is no predecessor
		//	Consider the case of 36: the predecessor is 35,
		//		The last ancestor that turns right
		//	Consider the case of 55: these kind of nodes
		//		can go left, so has already been dealt with
		//		by findPredecessorHelper()
		//	Strategy: keep a pointer to the last node that
		//		turns left
		DictEntry<Key, Item>* pre = nullptr;
		while (node != nullptr)
		{
			if (k > node->getKey())
			{
				//	We save the parent before going left
				//	in case that the right child of the parent
				//	contains the item
				pre = node;
				node = node->getRightChild();
			}
			else if (k < node->getKey())
			{
				//	No need to save the node
				node = node->getLeftChild();
			}
			else
			{
				//	We have reached the node containing the node
				//	just break and return succ
				break;
			}
		}
		return pre;
	}
}

template<typename Key, typename Item>
DictEntry<Key, Item>* IBSTDict<Key, Item>::findSuccFromRoot(DictEntry<Key, Item>* root, const Key& k)
{
	//	Special program to locate successor from root
	if (root == nullptr)
		return nullptr;
	else
	{
		//				    40
		//          /                  \
		//		35                        55
		//         \                  /
		//		     38           50
		//          /           /     \
		//	       36         45       53
		//                            /
		//                          51
		//	Consider the case of 55: there is no successor
		//	Consider the case of 53: the successor is 55
		//		The last ancestor node that turns left
		//	Consider the case of 36: the successor is 38
		//		The last ancestor node that turns left
		//	Consider the case of 35: these kind of nodes
		//		can go right, so has already been dealt with
		//		by findSuccessorHelper()
		//	Strategy: keep a pointer to the last node that
		//		turns left
		DictEntry<Key, Item>* succ = nullptr;
		while (root != nullptr)
		{
			if (item < root->getKey())
			{
				//	We save the parent before going left
				//	in case that the left child of the parent
				//	contains the item
				succ = root;
				root = root->getLeftChild();
			}
			else if (item > root->getKey())
			{
				//	No need to save the node
				root = root->getRightChild();
			}
			else
			{
				//	We have reached the node containing the node
				//	just break and return succ
				break;
			}
		}
		return succ;
	}
}

template<typename Key, typename Item>
DictEntry<Key, Item>* IBSTDict<Key, Item>::findPredecessorHelper(
	DictEntry<Key, Item>* target)
{
	//	target must be the node that has been located (cannot be nullptr)
	//	Case I: we can go left
	//	We will go left and see if we can go right from there
	//	If we can, we kepp going right
	//	If we cannot, then we already located the pre
	if (target->getLeftChild() != nullptr)
	{
		std::cout << "Go Left" << std::endl;
		//	Now goes left
		DictEntry<Key, Item>* left = target->getLeftChild();
		while (left->getRightChild())
		{
			std::cout << "Turn right" << std::endl;
			//	If we can get right at the first left node
			//	Then keep going right
			//	If we cannot get right, then don't bother 
			//	because left is already the predecessor
			left = left->getRightChild();
		}
		return left;
	}
	else
	{
		//	Case II: Predecessor might be the parent, or no predecessor
		//	So we search for the whole tree for its parent
		DictEntry<Key, Item>* pre = findPreFromRoot(root, target->getKey());
		return pre;
	}
}

template<typename Key, typename Item>
DictEntry<Key, Item>* IBSTDict<Key, Item>::findSuccessorHelper(
	DictEntry<Key, Item>* target)
{
	//	target must be the node that has been located (cannot be nullptr)
	//	Case I: we can go right
	//	We will go right and tries to go left from there
	//	If we can go left from there, then we keep going left
	//	Otherwise we already found the succ
	if (target->getRightChild() != nullptr)
	{
		std::cout << "Go Right" << std::endl;
		//	Now goes right
		DictEntry<Key, Item>* right = target->getRightChild();
		while (left->getLeftChild())
		{
			std::cout << "Turn Left" << std::endl;
			right = right->getLeftChild();
		}
		return right;
	}
	else
	{
		//	Case II: Successor might be the parent, or no successor
		//	So we search for the whole tree for its parent
		DictEntry<Key, Item>* succ = findSuccFromRoot(root, target->getKey());
		return succ;
	}
}

template<typename Key, typename Item>
DictEntry<Key, Item>* IBSTDict<Key, Item>::findPredecessor(const Key& k)
{
	return findPredecessorHelper(root, k);
}

template<typename Key, typename Item>
DictEntry<Key, Item>* IBSTDict<Key, Item>::findSuccessor(const Key& k)
{
	return findSuccessorHelper(root, k);
}

template<typename Key, typename Item>
DictEntry<Key, Item>* IBSTDict<Key, Item>::removeHelper(
	const Key& k, DictEntry<Key, Item>* root)
{
	if (root == nullptr)
		return nullptr;

	if (k < root->getKey())
	{
		root->setLeftChild(removeHelper(k, root->getLeftChild()));
	}
	else if (k > root->getKey())
	{
		root->setRightChild(removeHelper(k, root->getRightChild()));
	}
	else
	{
		//	Leaf and Single-child nodes
		if (root->getLeftChild() == nullptr)
			return root->getRightChild();
		if (root->getRightChild() == nullptr)
			return root->getLeftChild();

		//	Two-children nodes
		DictEntry<Key, Item>* pre =
	}
}

#endif

