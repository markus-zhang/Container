#ifndef ARITH_
#define ARITH_

#include <string>
#include <list>
#include <iostream>

enum TOKEN
{
	VOID,
	NUMBER,
	OPERATOR,
	LPAREN,
	RPAREN
};

class cToken
{
public:
	TOKEN m_Type;
	float m_Number;
	int m_Operator;
};

struct cArithNode
{
public:
	cToken m_Data;
	cArithNode* m_LeftChild;
	cArithNode* m_RightChild;
public:
	cArithNode()
	{
		m_LeftChild = m_RightChild = nullptr;
	}
};

class cArith
{
private:
	std::list<cToken> ls;
	cArithNode* m_Root;
public:
	//	Scan Utility
	float ScanFloat(char* input, int& index);
	void ScanHelper(char* input, std::list<cToken>& output);
public:
	cArith()
	{
		m_Root = nullptr;
	}
	~cArith() {}

	//	Scan
	void Scan(char* input)
	{
		ScanHelper(input, ls);
	}

	//	Display
	void Display();

	//	Parse
	cArithNode* Parse(std::list<cToken> ls);
	
};
#endif