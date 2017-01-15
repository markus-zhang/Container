#ifndef _SLINKEDLIST_
#define _SLINKEDLIST_


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

#endif
