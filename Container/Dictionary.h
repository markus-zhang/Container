#ifndef DICTIONARY_H_
#define DICTIONARY_H_

#include <functional>
#include <iostream>

template<typename Key, typename Item>
class Entry
{
public:
	Item item;
	Key key;
	//	Intrusive
	Entry<Key, Item>* prev;
	Entry<Key, Item>* next;
protected:
	void setKey(const Key& k);
public:
	Entry();
	Entry(Key k, Item i);

	Item getItem() const;
	Key getKey() const;
	void setItem(const Item& i);

	bool operator==(const Entry<Key, Item>& rightHand) const;
	bool operator>(const Entry<Key, Item>& rightHand) const;
	friend std::ostream& operator<<(std::ostream& outputStream,
		const Entry<Key, Item>& e);
};

template<typename Key, typename Item>
Entry<Key, Item>::Entry()
{
	prev = this;
	next = this;
}

template<typename Key, typename Item>
Entry<Key, Item>::Entry(Key k, Item i)
{
	key = k;
	item = i;
	prev = this;
	next = this;
}

template<typename Key, typename Item>
void Entry<Key, Item>::setKey(const Key& k)
{
	key = k;
}

template<typename Key, typename Item>
Item Entry<Key, Item>::getItem() const
{
	return item;
}

template<typename Key, typename Item>
Key Entry<Key, Item>::getKey() const
{
	return key;
}

template<typename Key, typename Item>
void Entry<Key, Item>::setItem(const Item& i)
{
	item = i;
	//	Do we need to set key?
}

template<typename Key, typename Item>
bool Entry<Key, Item>::operator==(const Entry<Key, Item>& rightHand) const
{
	return (key == rightHand.getKey() && item == rightHand.getItem());
}

template<typename Key, typename Item>
bool Entry<Key, Item>::operator>(const Entry<Key, Item>& rightHand) const
{
	return (key > rightHand.getKey());
}

template<typename Key, typename Item>
std::ostream& Entry<Key, Item>::operator<<(std::ostream& outputStream,
	const Entry<Key, Item>& e)
{
	//outputStream << 
}

//	Intrusive Dictionary List

template<typename Key, typename Item>
class Entry_List
{
private:
	Entry<Key, Item>* head;
protected:
	void InsertAfter(Entry<Key, Item>* e, Entry<Key, Item>* target);
	void remove(Entry<Key, Item>* target);
public:
	Entry_List();
	~Entry_List();

	bool isEmpty() const;
	
	void insertHead(const Key& k, const Item& i);
	void remove(const Key& k);
	void clear();

	Item getItemByKey(const Key& k);

	void traverse(std::function<void(Entry<Key, Item>*)> func);
};

template<typename Key, typename Item>
Entry_List<Key, Item>::Entry_List() {}

template<typename Key, typename Item>
Entry_List<Key, Item>::~Entry_List()
{
	clear();
}

template<typename Key, typename Item>
bool Entry_List<Key, Item>::isEmpty() const
{
	return (head->next == head);
}

template<typename Key, typename Item>
void Entry_List<Key, Item>::InsertAfter(Entry<Key, Item>* e, Entry<Key, Item>* target)
{
	if (target->next == target)
	{
		target->next = e;
		e->prev = target;
	}
	else
	{
		target->next->prev = e;
		e->next = target->next;
		e->prev = target;
		target->next = e;
	}
}

template<typename Key, typename Item>
void Entry_List<Key, Item>::insertHead(const Key& k, const Item& i)
{
	Entry<Key, Item>* e = new Entry<Key, Item>(k, i);
	insertAfter(e, head);
}

template<typename Key, typename Item>
void Entry_List<Key, Item>::remove(Entry<Key, Item>* target)
{
	//	Also works for only one node
	target->prev->next = target->next;
	target->next->prev = target->prev;
	target->prev = target;
	target->next = target;
}

template<typename Key, typename Item>
void Entry_List<Key, Item>::remove(const Key& k)
{
	//	We have to find the Entry first
	Entry<Key, Item>* walker = head->next;
	while (walker != walker->next)
	{
		if (walker->getKey() == k)
		{
			remove(walker);
			return;
		}
		walker = walker->next;
	}
	//	Check the last entry
	if (walker->getKey() == k)
	{
		remove(walker);
	}
}

template<typename Key, typename Item>
void Entry_List<Key, Item>::clear()
{
	Entry<Key, Item>* walker = head->next;
	while (walker != walker->next)
	{
		remove(walker);
		walker = walker->next;
	}
	//	Last entry
	remove(walker);
}

template<typename Key, typename Item>
Item Entry_List<Key, Item>::getItemByKey(const Key& k)
{
	//	We have to find the Entry first
	Entry<Key, Item>* walker = head->next;
	while (walker != walker->next)
	{
		if (walker->getKey() == k)
		{
			return walker->getItem();
		}
		walker = walker->next;
	}
	//	Check the last entry
	if (walker->getKey() == k)
	{
		return walker->getItem();
	}
	std::cout << "Haven't found!" << std::endl;
}

template<typename Key, typename Item>
void Entry_List<Key, Item>::traverse(std::function<void(Entry<Key, Item>*)> func)
{
	Entry<Key, Item>* walker = head->next;
	while (walker != walker->next)
	{
		func(walker);
		walker = walker->next;
	}
	if (walker != head)
	{
		func(walker);
	}
}

#endif