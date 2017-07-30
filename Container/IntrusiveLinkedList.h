#ifndef INTRUSIVELIST_H_
#define INTRUSIVELIST_H_

template<typename T>
struct ILinkedListNode
{
	//	Circular Sentinel Intrusive Doubly Linked List
	ILinkedListNode* prev;
	ILinkedListNode* next;

	ILinkedListNode() : prev(this), next(this) {}
};

template<typename T>
class ILinkedList
{
private:
	ILinkedListNode* head;
protected:
	void addAfter(ILinkedListNode* node, ILinkedListNode* prev);
	void addBefore(ILinkedListNode* node, ILinkedListNode* prev);

public:
	ILinkedList();

	bool isEmpty();

	void remove(ILinkedListNode* node);
	void addHead(ILinkedListNode* node);

	ILinkedListNode* front();
};

template<typename T>
ILinkedList<T>::ILinkedList()
{
	//	Make two dummy nodes
	head->prev = head;
	head->next = head;
	numNode = 0;
}

template<typename T>
bool ILinkedList<T>::isEmpty()
{
	return (head->next == head);
}

template<typename T>
void ILinkedList::remove(ILinkedListNode* node)
{
	node->next->prev = node->prev;
	node->prev->next = node->next;
	node->next = node;
	node->prev = node;
}

template<typename T>
void ILinkedList<T>::addAfter(ILinkedListNode* node, ILinkedListNode* prev)
{
	node->next = prev->next;
	prev->next->prev = node;
	node->prev = prev;
	prev->next = node;
}

template<typename T>
void ILinkedList<T>::addBefore(ILinkedListNode* node, ILinkedListNode* next)
{
	node->prev = next->prev;
	next->prev->next = node;
	node->next = next;
	next->prev = node;
}

template<typename T>
void ILinkedList<T>::addHead(ILinkedListNode* node)
{
	addAfter(node, head);
}

template<typename T>
ILinkedListNode* ILinkedList<T>::front()
{
	return head->next;
}
#endif

