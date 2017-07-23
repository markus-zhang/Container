#ifndef ARRAYMAXHEAP_H_
#define ARRAYMAXHEAP_H_

#include <vector>
#include <math.h>
#include "HeapInterface.h"

template<typename T>
class ArrayMaxHeap : public HeapInterface<T>
{
private:
	static const int ROOT_INDEX = 0;
	static const int DEFAULT_CAPACITY = 100;	//	Small Capacity
	std::vector<T> items;	//	Array (Vector) or items
	int itemCount;	//	Number of items
	int maxItems;	//	Maximum Capacity

	//	Given a nodeIndex, output its left child index
	int getLeftChildIndex(const int nodeIndex) const;

	//	Given a nodeIndex, output its right child index
	int getRightChildIndex(int nodeIndex) const;

	//	Returns the parent index
	int getParentIndex(int nodeIndex) const;

	//	Test if it's leaf
	bool isLeaf(int nodeIndex) const;

	//	Convert a semi heap to a heap
	void heapRebuild(int subTreeRootIndex);

	//	Create a heap from an unoredered array(vector)
	void heapCreate();

	//	Add helper
	void addHelper(int itemindex);
public:
	//	Constructor & Destructor
	ArrayMaxHeap();
	ArrayMaxHeap(const std::vector<T> someArray, const int arraySize);
	virtual ~ArrayMaxHeap();

	//	HeapInterface Overrides
	bool isEmpty() const;
	int getNumberOfNodes() const;
	int getHeight() const;
	T peekTop() const;
	void add(const T& item);
	//	Remove the root node
	void remove();
	void clear();

	//	Heapsort
	std::vector<T> heapSort(std::vector<T> input);
};

template<typename T>
ArrayMaxHeap<T>::ArrayMaxHeap() {}

template<typename T>
ArrayMaxHeap<T>::~ArrayMaxHeap()
{
	clear();
}

template<typename T>
ArrayMaxHeap<T>::ArrayMaxHeap(const std::vector<T> someArray, const int arraySize)
{
	itemCount = 0;
	for (auto i : someArray)
	{
		items.push_back(i);
		itemCount += 1;
	}
	heapCreate();
}

template<typename T>
int ArrayMaxHeap<T>::getLeftChildIndex(const int nodeIndex) const
{
	//Its left child, if it exists, is items[2 * i + 1]
	return 2 * nodeIndex + 1;
}

template<typename T>
int ArrayMaxHeap<T>::getRightChildIndex(const int nodeIndex) const
{
	//Its right child, if it exists, is items[2 * i + 2]
	return 2 * nodeIndex + 2;
}

template<typename T>
int ArrayMaxHeap<T>::getParentIndex(int nodeIndex) const
{
	//Its parent, is items[(i - 1) / 2]
	return (nodeIndex - 1) / 2;
}

template<typename T>
bool ArrayMaxHeap<T>::isLeaf(int nodeIndex) const
{
	if (2 * nodeIndex + 1 > items.size() - 1)
		return true;
	return false;
}

template<typename T>
void ArrayMaxHeap<T>::heapRebuild(int subTreeRootIndex)
{
	//	Rebuild a heap from semi-heap
	//	We assume it's already a semi-heap
	//	Consider the following heap:
	//				10
	//           /       \
	//         9           6
	//        / \         /
	//       3   2       5
	//	By deleting 10, we actually put 5 into root
	//				 5
	//           /       \
	//         9           6
	//        / \         
	//       3   2   
	//	But as this is a max heap, root must be the maximum
	//	So we swap 5 with the larger child, which is 9
	//				 9
	//           /       \
	//         5           6
	//        / \        
	//       3   2   
	//	Now what we have is a max heap

	//	Step 1: Replace the root with the value of last node
	//	This is already done

	//	Step 2: Remove the last element
	//	This is already done

	//	Step 3: 
	if (isLeaf(subTreeRootIndex) || items.size() <= 1)
	{
		return;
	}
	bool left_larger = 1;	//	Assuming left child is larger
	//	One child case
	if (subTreeRootIndex * 2 + 2 > items.size() - 1)
	{
		if (items[subTreeRootIndex] < items[2 * subTreeRootIndex + 1])
		{
			//	Swap root with left child
			T exchange;
			exchange = items[2 * subTreeRootIndex + 1];
			items[2 * subTreeRootIndex + 1] = items[subTreeRootIndex];
			items[subTreeRootIndex] = exchange;
			return;
		}
		else
			return;
	}
	else
	{
		if (items[2 * subTreeRootIndex + 1] < items[2 * subTreeRootIndex + 2])
		{
			left_larger = 0;
		}
	}

	if (left_larger)
	{
		if (items[subTreeRootIndex] < items[2 * subTreeRootIndex + 1])
		{
			//	Swap root with left child
			T exchange;
			exchange = items[2 * subTreeRootIndex + 1];
			items[2 * subTreeRootIndex + 1] = items[subTreeRootIndex];
			items[subTreeRootIndex] = exchange;
			//	Recursively calls itself on the next root
			if (items.size() - 1 >= 2 * subTreeRootIndex + 1)
			{
				heapRebuild(2 * subTreeRootIndex + 1);
			}
		}
	}
	else
	{
		if (items[subTreeRootIndex] < items[2 * subTreeRootIndex + 2])
		{
			//	Swap root with right child
			T exchange;
			exchange = items[2 * subTreeRootIndex + 2];
			items[2 * subTreeRootIndex + 2] = items[subTreeRootIndex];
			items[subTreeRootIndex] = exchange;
			//	Recursively calls itself on the next root
			if (items.size() - 1 >= 2 * subTreeRootIndex + 2)
			{
				heapRebuild(2 * subTreeRootIndex + 2);
			}
		}
	}
	//	if root is already greater than the children, do nothing
}

template<typename T>
void ArrayMaxHeap<T>::heapCreate()
{
	heapRebuild(0);
}

//	HeapInterface Overrides
template<typename T>
bool ArrayMaxHeap<T>::isEmpty() const
{
	return (itemCount == 0);
}

template<typename T>
int ArrayMaxHeap<T>::getNumberOfNodes() const
{
	return itemCount;
}

template<typename T>
int ArrayMaxHeap<T>::getHeight() const
{
	//	Heaps are complete binary trees, 
	//	so the number of nodes is between 1+...+2^(n-1) and 1+...+2^n,
	//	with n as the height.
	for (int n = 1; ; n++)
	{
		if (itemCount <= pow(2, n+1) - 1 && itemCount >= pow(2, n) - 1)
		{
			return n;
		}
	}
}

template<typename T>
T ArrayMaxHeap<T>::peekTop() const
{
	if (itemCount > 0)
		return items.front();
}

template<typename T>
void ArrayMaxHeap<T>::add(const T& item)
{
	//	Step 1: put the new item into the back
	items.push_back(item);
	itemCount += 1;

	//	Step 2: call addHelper(index)
	addHelper(items.size() - 1);
}

template<typename T>
void ArrayMaxHeap<T>::addHelper(int itemindex)
{
	//	Compare the itemindex with its parent
	//	Swap if it's larger than the parent
	if (items[itemindex] > items[(itemindex - 1) / 2])
	{
		T temp = items[itemindex];
		items[itemindex] = items[(itemindex - 1) / 2];
		items[(itemindex - 1) / 2] = temp;
		//	Now it's moved to (itemindex - 1) / 2
		addHelper((itemindex - 1) / 2);
	}
}

//	Remove the root node
template<typename T>
void ArrayMaxHeap<T>::remove()
{
	//	Replace the root with the tail element
	//	Then call heapRebuild()
	/*std::cout << "Before remove ";
	for (auto i : items)
	{
		std::cout << i << ", ";
	}
	std::cout << std::endl;*/
	heapRebuild(0);
	items[0] = items[items.size() - 1];
	items.pop_back();
	itemCount -= 1;
	/*std::cout << "After remove ";
	for (auto i : items)
	{
		std::cout << i << ", ";
	}
	std::cout << std::endl;*/
	heapRebuild(0);
}

template<typename T>
void ArrayMaxHeap<T>::clear()
{
	items.clear();
	itemCount = 0;
}

template<typename T>
std::vector<T> ArrayMaxHeap<T>::heapSort(std::vector<T> input)
{
	//	read into heap
	if (input.size() <= 1)
		return input;
	for (auto i : input)
	{
		items.push_back(i);
	}

	//	Rebuid into a heap
	heapCreate();
	for (auto i : items)
	{
		std::cout << i << ", ";
	}
	std::cout << std::endl;
	
	//	Remove root as root is always the largest
	std::vector<T> output;
	while (items.size() > 0)
	{
		//std::cout << items.front() << ", ";
		output.push_back(items.front());
		std::cout << std::endl;
		remove();
	}
	return output;
}
#endif
