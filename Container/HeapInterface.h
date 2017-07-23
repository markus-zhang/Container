#ifndef HEAPINTERFACE_H_
#define HEAPINTERFACE_H_

template<typename T>
class HeapInterface
{
public:
	virtual bool isEmpty() const = 0;

	virtual int getNumberOfNodes() const = 0;

	virtual int getHeight() const = 0;

	virtual T peekTop() const = 0;

	virtual void add(const T& item) = 0;

	//	Remove the root node
	virtual void remove() = 0;

	virtual void clear() = 0;
};

#endif
