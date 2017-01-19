#ifndef _DLINKEDLIST_
#define _DLINKEDLIST_

#include <assert.h>

//	Linked List Node Template Class

template<class T>
class DListNode
{
public:
	//	Constrcutors and Destructors
	DListNode();
	~DListNode();

	void InsertAfter(const T& new_data);
	void InsertBefore(const T& new_data);
	T GetData() const;
public:
	T m_data;
	DListNode<T>* m_next;
	DListNode<T>* m_prev;
};

//	Circular Linked List Template Class

template<class T>
class DListIterator;

template<class T>
class DLinkedList
{
public:
	DLinkedList();
	~DLinkedList();

	void Clear();
	DListIterator<T> GetIterator();
	void Remove(DListIterator<T>& it);
	void Append(const T& new_data);
	void Prepend(const T& new_data);
	int  Frequency(const T& data);
public:
	DListNode<T>* m_head;
	DListNode<T>* m_tail;
	int m_count;
};

//	Iterator class for Doubly Linked List

template<class T>
class DListIterator
{
public:
	DListIterator(DListNode<T>* node, DLinkedList<T>* list);

	void Init();

	void Forth();
	void Backward();
	T& GetData();

	bool Valid();
public:
	DListNode<T>* m_node;
	DLinkedList<T>* m_list;
};

//	Linked List Node Implementation

template<class T>
DListNode<T>::DListNode()
{
	m_next = m_prev = nullptr;
}

template<class T>
DListNode<T>::~DListNode()
{
	//	std::cout << "Called a destructor" << std::endl;
	if (m_next != 0)
	{
		delete m_next;
		m_next = 0;
	}
	if (m_prev != 0)
	{
		delete m_prev;
		m_prev = 0;
	}
}

template<class T>
void DListNode<T>::InsertAfter(const T& new_data)
{
	DListNode<T>* new_node = new DListNode<T>;
	new_node->m_data = new_data;
	new_node->m_next = m_next;	//	new_node's next
	new_node->m_prev = this;	//	new_node's prev
	m_next->m_prev = new_node;	//	new_node's next's prev
	m_next = new_node;			//	my next
}

template<class T>
void DListNode<T>::InsertBefore(const T& new_data)
{
	DListNode<T>* new_node = new DListNode<T>;
	new_node->m_data = new_data;
	new_node->m_prev = m_prev;	//	new_node's prev is my original prev
	new_node->m_next = this;	//	new_node's next is me
	m_prev->m_next = new_node;	//	new_node's prev's next is new_node
	m_prev = new_node;			//	my prev is new_node
}

template<class T>
T DListNode<T>::GetData() const
{
	return m_data;
}

//	Circular Linked List Implementation

template<class T>
DLinkedList<T>::DLinkedList()
{
	m_head = nullptr;
	m_tail = nullptr;
	m_count = 0;
}

template<class T>
DLinkedList<T>::~DLinkedList()
{
	Clear();
}

template<class T>
void DLinkedList<T>::Clear()
{
	if (m_count == 0)
		return;
	DListIterator<T> it = DListIterator<T>(m_head, this);
	for (it.Init(); it.Valid(); )
	{
		if (it.m_node->m_next != nullptr)
		{
			//DListNode<T>* garbage = new DListNode<T>;
			DListNode<T>* garbage = nullptr;
			garbage = it.m_node;
			it.Forth();
			garbage->m_next = nullptr;
			it.m_node->m_prev = nullptr;
			delete garbage;		
			garbage = nullptr;
			m_count -= 1;
		}
		else
		{
			//	Either only one node or the last node
			delete it.m_node;
			it.m_node = nullptr;
			m_count -= 1;
		}
	}
}

template<class T>
DListIterator<T> DLinkedList<T>::GetIterator()
{
	return DListIterator<T>(m_head, this);
}

template<class T>
void DLinkedList<T>::Remove(DListIterator<T>& it)
{
	//	Is it my iterator
	if (it.m_list != this)
		return;
	//	Remove the node pointed by the iterator
	if (!it.Valid())
		return;
	//	Only one node
	if (m_count == 1)
	{
		delete m_head;
		m_head = m_tail = nullptr;
		m_count -= 1;
	}
	//	If it's head node
	if (it.m_node == m_head)
	{
		//	Disconnect the second node
		DListNode<T>* temp = m_head->m_next;
		m_head->m_next->m_prev = nullptr;
		delete m_head;
		m_head = temp;
		temp = nullptr;
		m_count -= 1;
		return;
	}
	//	if it's tail node
	if (it.m_node == m_tail)
	{
		//	Disconnect the previous node
		DListNode<T>* temp = m_tail->m_prev;
		m_tail->m_prev->m_next = nullptr;
		delete m_prev;
		m_prev = temp;
		temp = nullptr;
		m_count -= 1;
		return;
	}
	if (it.m_node == m_tail)
		//	Disconnect neighbors
		DListNode<T>* temp = it.m_node;	//	Save for accessing
	temp->m_next->m_prev = temp->m_prev;
	temp->m_prev->m_next = temp->m_next;
	delete temp;
	temp = nullptr;
}

template<class T>
void DLinkedList<T>::Append(const T& new_data)
{
	//	If it's empty
	if (m_count == 0)
	{
		DListNode<T>* new_node = new DListNode<T>;
		new_node->m_data = new_data;
		m_head = m_tail = new_node;
	}
	else
	{
		//	If it has at least 1 nodes
		DListNode<T>* new_node = new DListNode<T>;
		new_node->m_data = new_data;
		//	Connection
		m_tail->m_next = new_node;
		new_node->m_prev = m_tail;
		m_tail = new_node;
	}
	m_count += 1;
}

template<class T>
int DLinkedList<T>::Frequency(const T& data)
{
	if (m_count == 0)
		return 0;
	//	At least one element
	int freq;
	DListIterator<T> it = DListIterator<T>(m_head, this);
	for (it.Init(); it.Valid(); it.Forth())
	{
		if (it.GetData() == data)
			freq += 1;
	}
	return freq;
}

template<class T>
void DLinkedList<T>::Prepend(const T& new_data)
{
	//	If it's empty
	if (m_count == 0)
	{
		DListNode<T>* new_node = new DListNode<T>;
		new_node->m_data = new_data;
		m_head = m_tail = new_node;
	}
	else
	{
		//	If it has at least 1 nodes
		DListNode<T>* new_node = new DListNode<T>;
		new_node->m_data = new_data;
		//	Connection
		m_head->m_prev = new_node;
		new_node->m_next = m_head;
		m_head = new_node;
	}
	m_count += 1;
}

//	Iterator Implementation

template<class T>
DListIterator<T>::DListIterator(DListNode<T>* node, DLinkedList<T>* list)
{
	assert(node != nullptr && list != nullptr);
	m_node = node;
	m_list = list;
}

template<class T>
void DListIterator<T>::Init()
{
	if (m_list != nullptr)
		m_node = m_list->m_head;
}

template<class T>
void DListIterator<T>::Forth()
{
	if (m_list != nullptr)
		m_node = m_node->m_next;
}

template<class T>
void DListIterator<T>::Backward()
{
	if (m_list != nullptr)
		m_node = m_list->m_prev;
}

template<class T>
T& DListIterator<T>::GetData()
{
	if (m_node != nullptr)
		return m_node->m_data;
}

template<class T>
bool DListIterator<T>::Valid()
{
	return (m_node != nullptr);
}

#endif