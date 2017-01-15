#ifndef _SLINKEDLIST_
#define _SLINKEDLIST_

//	Linked List Node Template Class

template<class T>
class SListNode
{
public:
	void InsertAfter(T new_data);
	T GetData() const;
public:
	T m_data;
	SListNode<T>* m_next;
};

//	Linked List Node Implementation
template<class T>
void SListNode<T>::InsertAfter(T new_data)
{
	SListNode<T>* new_node = new SListNode<T>;
	new_node->m_data = new_data;
	new_node->m_next = m_next;
	m_next = new_node;
}

template<class T>
T SListNode<T>::GetData() const
{
	return m_data;
}

//	Linked List Template Class

template<class T>
class SListIterator;

template<class T>
class SLinkedList
{
public:
	SLinkedList();
	~SLinkedList();
	void Init(T new_data);

	int GetCount();
	bool IsEmpty();

	void Append(T new_data);
	void Prepend(T new_data);
	void RemoveHead();
	void RemoveTail();

	SListIterator<T> GetIterator();
	void Insert(SListIterator<T>& it, T new_data);
public:
	SListNode<T>* m_head;
	SListNode<T>* m_tail;
	int m_count;
};

//	Linked List Implementation

template<class T>
SLinkedList<T>::SLinkedList()
{
	m_head = 0;
	m_tail = 0;
	m_count = 0;
}

template<class T>
SLinkedList<T>::~SLinkedList()
{
	SListNode<T>* it = m_head;
	SListNode<T>* next;

	while (it != 0)
	{
		next = it->m_next;
		delete it;
		it = next;
	}
}

template<class T>
void SLinkedList<T>::Init(T new_data)
{
	SListNode<T>* first_node = new SListNode<T>;
	first_node->m_data = new_data;
	m_head = first_node;
	m_tail = first_node;
}

template<class T>
int SLinkedList<T>::GetCount()
{
	return m_count;
}

template<class T>
bool SLinkedList<T>::IsEmpty()
{
	return m_head == null;
}

template<class T>
void SLinkedList<T>::Append(T new_data)
{
	if (m_head == 0)
	{
		// Empty List
		Init(new_data);
	}
	else
	{
		m_tail->InsertAfter(new_data);
		m_tail = m_tail->m_next;
	}
	m_count += 1;
}

template<class T>
void SLinkedList<T>::Prepend(T new_data)
{
	if (m_head == 0)
	{
		// Empty List
		Init(new_data);
	}
	else
	{
		// Create a new head node
		SListNode<T>* new_head = new SListNode<T>;
		new_head->m_data = new_data;
		new_head->m_next = m_head;

		// Replace m_head with new_head
		m_head = new_head;
	}
	m_count += 1;
}

template<class T>
void SLinkedList<T>::RemoveHead()
{
	if (m_head == 0)
		return;

	//	m_head will point to the second node in the list
	SListNode<T>* temp_node = 0;
	temp_node = m_head->m_next;
	m_head = 0;
	delete m_head;
	m_head = temp_node;

	//	If we delete the only node in the list
	//	Then we need to set m_tail to null
	//	As m_tail was originally pointed to the only node
	//	Since we have already deleted that one
	//	m_tail becomes a dangled pointer
	if (m_head == 0)
	{
		m_tail = 0;
	}
	m_count -= 1;
}

template<class T>
void SLinkedList<T>::RemoveTail()
{
	//	Empty List
	if (m_head == 0)
		return;
	//	List with only ONE node
	if (m_head->m_next == 0)
	{
		delete m_head;
		m_head = 0;
		m_tail = 0;
		m_count -= 1;
		return;
	}
	//	List with more than one nodes
	SListNode<T>* temp_node = 0;
	for (temp_node = head; ;)
	{
		if (temp_node->m_next == m_tail)
		{
			//	The next node of next node is null
			//	The next node is m_tail
			delete temp_node->m_next;
			temp_node->m_next = 0;
			m_tail = temp_node;
			break;
		}
	}
}

template<class T>
SListIterator<T> SLinkedList<T>::GetIterator()
{
	return SListIterator<T>(m_head, this);
}

template<class T>
void SLinkedList<T>::Insert(SListIterator<T>& it, T new_data)
{
	if (it.m_list != this)
		return;

	if (it.m_node != 0)
	{
		it.m_node->InsertAfter(new_data);
	}
}

//	Iterator class for Singly Linked List

template<class T>
class SListIterator
{
public:
	SListIterator(SListNode<T>* node, SLinkedList<T>* list);

	void Init();

	void Forth();
	void Backward();
	T& GetData();

	bool Valid();
public:
	SListNode<T>* m_node;
	SLinkedList<T>* m_list;
};

// Linked List Iterator Implementation

template<class T>
SListIterator<T>::SListIterator(SListNode<T>* node = 0, SLinkedList<T>* list = 0)
{
	m_node = node;
	m_list = list;
}

template<class T>
void SListIterator<T>::Init()
{
	if (m_list != 0)
	{
		//	Move to the head of the list
		m_node = m_list->m_head;
	}
}

template<class T>
void SListIterator<T>::Forth()
{
	//	Warning: Potentially hit a NULL node
	if (m_node != 0)
		m_node = m_node->m_next;
}

template<class T>
void SListIterator<T>::Backward()
{
	//	Warning: Akward implementation as there is no m_prev
	if (m_list->m_count > 1)
	{
		if (m_node != 0)
		{
			SListNode<T>* temp = m_list->m_head;
			while (temp != 0)
			{
				if (temp->m_next == m_node)
				{
					m_node = temp;
					temp = 0;	//	Cleaning up
					return;
				}
			}
		}
	}
}

template<class T>
T& SListIterator<T>::GetData()
{
	return m_node->m_data;
}

template<class T>
bool SListIterator<T>::Valid()
{
	return (m_node != 0);
}

#endif
