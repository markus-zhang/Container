#ifndef BINARYTREEINTERFACE_
#define BINARYTREEINTERFACE_

template<class DataType>
class BinaryTreeInterface
{
public:
	virtual bool IsEmpty() const = 0;
	virtual int GetHeight() const = 0;
	virtual int GetNumNodes() const = 0;
	virtual DataType GetRootData() const = 0;
	virtual void SetRootData(const DataType& newdata) = 0;
	virtual bool Add(const DataType& newdata) = 0;
	virtual bool Remove(const DataType& olddata) = 0;
	virtual void Clear() = 0;
	virtual DataType GetEntry(const DataType& data) const = 0;
	virtual bool Locate(const DataType& data) const = 0;

	virtual void PreOrder(void Process(DataType&)) const = 0;
	virtual void InOrder(void Process(DataType&)) const = 0;
	virtual void PostOrder(void Process(DataType&)) const = 0;
};

#endif

