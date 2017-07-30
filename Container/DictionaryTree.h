//#ifndef DICTIONARYTREE_H_
//#define DICTIONARYTREE_H_
//
//#include "BinaryTree.h"
//#include "Dictionary.h"	//	For Entry only
//
//template<class Key, class Item>
//class DictionaryInterface
//{
//public:
//	virtual bool isEmpty();
//	virtual int getNumberofItems();
//	virtual void add(const Key& k, const Item& item) = 0;
//	virtual void remove(const Key& k) = 0;
//	virtual void clear() = 0;
//	virtual Item getItem(const Key& k) const = 0;
//	virtual bool contains(const Key& k) const = 0;
//	virtual void traverse(std::function<void(Item&)> func) = 0;
//};
//
//template<class Key, class Item>
//class DictBST : public DictionaryInterface<Key, Item>
//{
//private:
//	BST<Entry<Key, Item>> itemTree;
//public:
//	DictBST();
//	DictBST(int maxNumber);
//	DictBST(const DictBST<Key, Item>& dict);
//
//	bool isEmpty();
//	int getNumberofItems();
//	void add(const Key& k, const Item& item);
//	void remove(const Key& k);
//	void clear();
//	Item getItem(const Key& k) const;
//	bool contains(const Key& k) const;
//	void traverse(std::function<void(Item&)> func);
//	void display();
//};
//
//template<class Key, class Item>
//DictBST<Key, Item>::DictBST() {}
//
//template<class Key, class Item>
//DictBST<Key, Item>::DictBST(int maxNumber)
//{
//	//	Presumably set maxNumber for itemTree
//}
//
//template<class Key, class Item>
//DictBST<Key, Item>::DictBST(const DictBST<Key, Item>& dict)
//{
//	
//}
//
//template<class Key, class Item>
//bool DictBST<Key, Item>::isEmpty()
//{
//	return (itemTree.getHeight() == 0);
//}
//
//template<class Key, class Item>
//int DictBST<Key, Item>::getNumberofItems()
//{
//	return itemTree.countNumber();
//}
//
//template<class Key, class Item>
//void DictBST<Key, Item>::add(const Key& k, const Item& i)
//{
//	itemTree.BSTInsert(Entry<Key, Item>(k, i));
//}
//
//template<class Key, class Item>
//void DictBST<Key, Item>::remove(const Key& k)
//{
//	itemTree.removeValue(Entry<Key, Item>(k, Item()));
//}
//
//template<class Key, class Item>
//void DictBST<Key, Item>::clear()
//{
//
//}
//
//template<class Key, class Item>
//Item DictBST<Key, Item>::getItem(const Key& k) const
//{
//	Entry<Key, Item> e = Entry<Key, Item>(k, Item());
//	BTN<Entry<Key, Item>>* temp = itemTree.search(e);
//	return (temp->getItem()).item;
//}
//
//template<class Key, class Item>
//bool DictBST<Key, Item>::contains(const Key& k) const
//{
//
//}
//
//template<class Key, class Item>
//void DictBST<Key, Item>::traverse(std::function<void(Item&)> func)
//{
//
//}
//
//template<class Key, class Item>
//void DictBST<Key, Item>::display()
//{
//	
//}
//
//#endif
