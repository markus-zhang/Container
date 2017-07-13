//	Implementation of C++3e20100119.pdf

#ifndef BTDICNODE_H_
#define BTDICNODE_H_

template<typename Key, typename Element>
class Dictionary
{
private:
	void operator=(const Dictionary&) {}
	Dictionary(const Dictionary&) {}
public:
	Dictionary() {}
	virtual ~Dictionary() {}

	//	Clear the dictionary
	virtual void clear() = 0;

	//	Insert
	virtual void Insert(const Key& k, const Element& e) = 0;

	//	Remove record with key k, return it in e
	//	Remove an arbitrary one if multiple records exist
	virtual bool Remove(const Key& k, Element& e) = 0;

	//	Remove and return arbitrary record
	//	Purpose is to provide the inherited class
	//	a very efficient way to remove all the 
	//	records in the dictionary. Not all data structures
	//	are able to go to the next (and locate the first)
	//	record efficiently. So we can use the code fragment
	//	while (dict.Size() >0)
	//	{
	//		item = dict.RemoveAny();
	//		Process(item);
	//	}
	virtual Element RemoveAny() = 0;

	//	Return a copy in e of some record matching k
	//	Return arbitrary one if multiple records match k
	virtual bool Find(const Key& k, Element& e) const = 0;

	//	Return number of records
	virtual int Size() = 0;
};

template<typename Element>
class BinNode
{
public:
	virtual ~BinNode() {}

	//	Return value
	virtual Element& Val() = 0;

	//	Set value
	virtual void SetVal(const Element&) = 0;

	//	Return Left Child
	virtual BinNode* Left() const = 0;

	//	Return right child
	virtual BinNode* Right() const = 0;

	//	Set left child
	//	Parameter is a pointer because we need to
	//	use it to reset the root for insert and others
	virtual void SetLeft(BinNode*) = 0;

	//	Set right child
	virtual void SetRight(BinNode*) = 0;

	//	Is it a leaf?
	virtual bool IsLeaf() = 0;
};

template<typename key, typename element>
class BNode : public BinNode<element>
{
private:
	key m_Key;
	element m_Element;
	BNode* m_LeftChild;
	BNode* m_RightChild;
public:
	//	Constructors
	BNode()
	{
		m_LeftChild = m_RightChild = nullptr;
	}
	BNode(key k, element e, BNode* left, bNode* right)
	{
		m_Key = k;
		m_Element = e;
		m_LeftChild = left;
		m_RightChild = right;
	}
	~BNode() {}

	//	Set and Get
	element& GetElement()
	{
		return m_Element;
	}
	void SetElement(element e)
	{
		m_Element = e;
	}
	key& GetKey()
	{
		return m_Key;
	}
	void SetKey(key k)
	{
		m_Key = k;
	}
	
	BNode* GetLeftChild()
	{
		return m_LeftChild;
	}
	void SetLeftChild(BNode* left)
	{
		m_LeftChild = left;
	}
	BNode* GetRightChild()
	{
		return m_RightChild;
	}
	void SetRightChild(BNode* right)
	{
		m_RightChild = right;
	}

	bool IsLeaf()
	{
		if (m_LeftChild == nullptr && m_RightChild == nullptr)
		{
			return true;
		}
		return false;
	}
};

template<typename key, typename element>
class BST : public Dictionary<key, element>
{
private:
	BNode<key, element>* m_Root;
	int m_Count;

	//	Private helper
	bool findhelp(BNode<key, element>* root, const key& k,
		const element& e);
public:
	//	Public functions
	bool find(const key& k, const element& e);

};

template<typename key, typename element>
bool BST<key, element>::findhelp(BNode<key, element>* root,
	const key& k, const element& e)
{
	if (root == nullptr)
		return false;
	if (k < root->GetKey())
	{
		return findhelp(root->GetLeftChild(), k, e);
	}
	else if (k > root->GetKey())
	{
		return findhelp(root->GetRightChild(), k, e);
	}
	return true;
}

template<typename key, typename element>
bool BST<key, element>::find(const key& k, const element& e)
{
	return findhelp(m_Root, k, e);
}

#endif

