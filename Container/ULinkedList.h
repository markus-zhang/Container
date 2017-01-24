#ifndef _ULINKEDLIST_
#define _ULINKEDLIST_

#define MULTIPLIER	1

#include <assert.h>
#include <functional>
#include <vector>

//	Unrolled Linked List Node Template Class

template<class T>
class UListNode
{
public:
	//	Constrcutors and Destructors
	UListNode(int nummax);
	~UListNode();
	//	UListNode methods
	void Insert(const T& new_data);
	T& Find(const T& new_data);
	bool Maxed();
	std::vector<T> GetData() const;
public:
	std::vector<T> m_data;
	int m_numElements;
	int m_numMax;
	bool m_maxed;
	UListNode<T>* m_next;
	UListNode<T>* m_prev;
};

template<class T>
UListNode<T>::UListNode(int nummax)
{
	m_numElements = 0;
	m_numMax = nummax;
	m_maxed = false;
	m_next = nullptr;
	m_prev = nullptr;
}

template<class T>
UListNode<T>::~UListNode()
{
	m_data.clear();
	m_numElements = 0;
	m_numMax = 0;
	m_maxed = false;
	m_next = nullptr;
	m_prev = nullptr;
}

template<class T>
void UListNode<T>::Insert(const T& new_data)
{
	m_data.push_back(new_data);
	m_numElements += 1;
	if (m_numElements >= m_numMax)
		m_maxed = true;
}

template<class T>
T& UListNode<T>::Find(const T& new_data)
{

}

template<class T>
bool UListNode<T>::Maxed()
{
	return m_maxed;
}

template<class T>
std::vector<T> UListNode<T>::GetData() const
{
	return m_data;
}

//	Unrolled Linked List Template Class

template<class T>
class UListIterator;

template<class T>
class ULinkedList
{
public:
	ULinkedList();
	~ULinkedList();
	
	//	UList method code
	UListIterator<T> GetIterator();
	void Insert(const T& new_data);
	template<typename... Args>
	void Remove_If(std::function<bool(T t, Args... args)> func, Args... para);
	template<typename... Args>
	void CopyIf(std::function<bool(T t, Args... args)> func, Args... para, ULinkedList<T>& list);
	void Clear();

public:
	UListNode<T>* m_head;
	UListNode<T>* m_tail;
	int m_count;
	int m_CacheSize;
};

template<class T>
ULinkedList<T>::ULinkedList()
{
	m_count = 0;
	m_head = nullptr;
	m_tail = nullptr;
	m_CacheSize = SDL_GetCPUCacheLineSize();
	assert(m_CacheSize > 0);
}

template<class T>
ULinkedList<T>::~ULinkedList()
{
	Clear();
}

template<class T>
UListIterator<T> ULinkedList<T>::GetIterator()
{
	return UListIterator<T>(this);
}

template<class T>
void ULinkedList<T>::Insert(const T& new_data)
{
	//	If the list is empty
	if (m_count == 0)
	{
		size_t size = sizeof(new_data);
		int max = (m_CacheSize * MULTIPLIER) / size - 1;
		UListNode<T>* new_node = new UListNode<T>(max);
		std::cout << "Size of object: " << size << std::endl
			<< "Size of Cache: " << m_CacheSize << std::endl
			<< "Maximum number: " << max << std::endl;
		new_node->Insert(new_data);
		if (max == 1)	//	Cache can only fit one object
			new_node->m_maxed = true;
		//	Setup head and tail
		m_head = m_tail = new_node;
		m_count += 1;
		return;
	}
	//-----------------Iterator version-------------------//
	UListIterator<T> it = GetIterator();
	for (it.Init(); it.Valid(); it.Forth())
	{
		//	Insert at first non-Maxed node
		if (!it.m_node->Maxed())
		{
			std::cout << "Found a node that is not full" << std::endl;
			it.m_node->Insert(new_data);
			return;
		}
		else
		{
			if (it.m_node != m_tail)
				continue;
			else
			{
				//	Possible Scenario that every node is full
				size_t size = sizeof(new_data);
				int max = (m_CacheSize * MULTIPLIER) / size - 1;
				UListNode<T>* new_node = new UListNode<T>(m_head->m_numMax);
				new_node->m_data.push_back(new_data);
				if (max == 1)	//	Cache can only fit one object
					new_node->m_maxed = true;
				//	Setup tail and prev and next
				new_node->m_prev = m_tail;
				new_node->m_next = nullptr;
				m_tail->m_next = new_node;
				m_tail = new_node;
				m_count += 1;	//	You added a new node, remember?
				std::cout << "m_count is " << m_count << std::endl;
				it.Forth();
			}
		}
	}
}

template<class T>
template<typename... Args>
void ULinkedList<T>::Remove_If(std::function<bool(T t, Args... args)> func, Args... para)
{
	//	Remove a monster with coordination and other identities
	assert(m_count > 0);
	UListIterator<T> it = GetIterator();
	for (it.Init(); it.Valid(); it.Forth())
	{
		//	In each node, search the vector
		std::vector<T>::iterator v_it;
		for (v_it = it.GetData().begin(); v_it != it.GetData().end(); v_it++)
		{
			if (func(*v_it, para...))
				std::cout << "Remove this" << std::endl;
		}
	}
}

template<class T>
template<typename... Args>
void ULinkedList<T>::CopyIf(std::function<bool(T t, Args... args)> func, Args... para, ULinkedList<T>& list)
{
	assert(m_count > 0);
	UListIterator<T> it = GetIterator();
	for (it.Init(); it.Valid(); it.Forth())
	{
		//	In each node, search the vector
		std::vector<T>::iterator v_it;
		for (v_it = it.GetData().begin(); v_it != it.GetData().end(); v_it++)
		{
			if (func(*v_it, para...))
			{
				std::cout << *v_it << " is copied" << std::endl;
				list.Insert(*v_it);
			}
		}
	}
}

template<class T>
void ULinkedList<T>::Clear()
{
	while (m_head != nullptr)
	{
		UListNode<T>* temp = m_head;
		m_head = m_head->m_next;
		temp->m_next = nullptr;
		delete temp;
		temp = nullptr;
		m_count -= 1;
	}
}

//////////////////////////////////////////////	
//	Iterator class for Doubly Linked List	//
//////////////////////////////////////////////

template<class T>
class UListIterator
{
public:
	UListIterator(ULinkedList<T>* list);

	void Init();

	void Forth();
	void Backward();
	std::vector<T>& GetData();

	bool Valid();
public:
	UListNode<T>* m_node;
	ULinkedList<T>* m_list;
};

template<class T>
UListIterator<T>::UListIterator(ULinkedList<T>* list)
{
	assert(list != nullptr);
	m_node = list->m_head;
	m_list = list;
	assert(m_list != nullptr && m_node != nullptr);
}

template<class T>
void UListIterator<T>::Init()
{
	if (m_list != nullptr)
		m_node = m_list->m_head;
	else
		m_node = nullptr;
}

template<class T>
void UListIterator<T>::Forth()
{
	if (m_list == nullptr)
		return;
	m_node = m_node->m_next;
}

template<class T>
void UListIterator<T>::Backward()
{
	if (m_list == nullptr)
		return;
	m_node = m_node->m_prev;
}

template<class T>
std::vector<T>& UListIterator<T>::GetData()
{
	return m_node->m_data;
}

template<class T>
bool UListIterator<T>::Valid()
{
	return (m_node != nullptr);
}

#endif
