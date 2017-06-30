#ifndef BTNODE_
#define BTNODE_

class cBTNode
{
private:
	cBTNode* m_LeftChild;
	cBTNode* m_RightChild;
	float m_Data;
public:
	//	Constructor + Destructor
	cBTNode() : m_LeftChild(nullptr), m_RightChild(nullptr) {}
	cBTNode(const float& data) : m_LeftChild(nullptr), m_RightChild(nullptr),
		m_Data(data) {}
	cBTNode(const cBTNode& btnode)
	{
		Copy(btnode);
	}
	~cBTNode()
	{
		Destroy();
	}

	//	Utility
	bool IsLeaf()
	{
		return ((m_LeftChild == nullptr && m_RightChild == nullptr)
			? true : false);
	}

	void Copy(const cBTNode& btnode)
	{
		//	Deep copy
		SetData(btnode.GetData());
		SetLeftChild(btnode.GetLeftChild());
		SetRightChild(btnode.GetRightChild());
	}

	void Destroy()
	{
		if (m_LeftChild != nullptr)
		{
			//delete m_LeftChild;
			m_LeftChild = nullptr;
		}
		if (m_RightChild != nullptr)
		{
			//delete m_RightChild;
			m_RightChild = nullptr;
		}
	}

	//	Get + Set
	float GetData() const
	{
		return m_Data;
	}

	cBTNode* GetLeftChild() const
	{
		return m_LeftChild;
	}

	cBTNode* GetRightChild() const
	{
		return m_RightChild;
	}

	void SetData(const float& data)
	{
		m_Data = data;
	}

	void ModifyData(float& data)
	{
		m_Data = data;
	}

	void SetLeftChild(cBTNode* leftchild)
	{
		m_LeftChild = leftchild;
	}

	void SetRightChild(cBTNode* rightchild)
	{
		m_RightChild = rightchild;
	}
};

#endif
