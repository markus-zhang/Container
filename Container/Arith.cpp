#include <cctype>
#include <cmath>
#include "Arith.h"

float cArith::ScanFloat(char* input, int& index)
{
	//	Validate if the char at the index is a number
	if (!isdigit(input[index]))
	{
		return -1.0;
	}

	//	Continue reading input until non-digit char except '.'
	float result = 0;
	float multiplier_power = 0;
	bool decimal = false;
	while (1)
	{
		if (isdigit(input[index]))
		{
			if (!decimal)
			{
				result = result * 10 + input[index] - '0';
			}
			else
			{
				result += std::pow(10, multiplier_power)
							* (input[index] - '0');
				multiplier_power -= 1;
			}
		}
		else if (input[index] == '.')
		{
			//	Decimal Flag 
			decimal = true;
			multiplier_power = -1;	//	Next digit will multiply 0.1
		}
		else
		{
			//	End of digits
			return result;
		}
		index += 1;
	}
}

void cArith::ScanHelper(char* input, std::list<cToken>& output)
{
	//	Receives a C-String input and output list of cToken
	int index = 0;
	int length = strlen(input);
	char c;
	cToken token;

	while (index < length)
	{
		//	Different characters
		c = input[index];
		token.m_Type = VOID;

		switch (c)
		{
		//	Parenthesis
		case '(':
			token.m_Type = LPAREN;
			break;
		case ')':
			token.m_Type = RPAREN;
			break;
		//	Operators
		case '+':
			token.m_Type = OPERATOR;
			token.m_Operator = 0;
			break;
		case '-':
			token.m_Type = OPERATOR;
			token.m_Operator = 1;
			break;
		case '*':
			token.m_Type = OPERATOR;
			token.m_Operator = 2;
			break;
		case '/':
			token.m_Type = OPERATOR;
			token.m_Operator = 3;
			break;
		case '^':
			token.m_Type = OPERATOR;
			token.m_Operator = 4;
			break;
		case '%':
			token.m_Type = OPERATOR;
			token.m_Operator = 5;
			break;
		//	Numbers
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			token.m_Type = NUMBER;
			token.m_Number = ScanFloat(input, index);
			index -= 1;	//	Check ScanFloat for reason
			break;
		}
		//	If the token is valid, push_back into the list
		if (token.m_Type != VOID)
		{
			output.push_back(token);
		}
		index += 1;
	}
}

void cArith::Display()
{
	for (auto token : ls)
	{
		if (token.m_Type == NUMBER)
		{
			std::cout << token.m_Number << ", ";
		}
		else if (token.m_Type == OPERATOR)
		{
			std::cout << token.m_Operator << ", ";
		}
		else
		{
			std::cout << "ERROR, ";
		}
	}
	std::cout << std::endl;
}

cArithNode* cArith::Parse(std::list<cToken> ls)
{
	//	Parsing takes three steps for num-op-num
	//	Step 1:
	//	Get the number
	//		Push it into num node
	//		EXCEPTION:
	//			The first char can also be '('
	//	Step 2:
	//	Get the op (ERROR if it's not a number)
	//		Push it into op node
	//		EXCEPTION:
	//			No exception
	//	Step 3:
	//	Get the number
	//		Push it into num node
	//		EXCEPTION:
	//			The thrid char can also be '('
	//	Step 4:
	//		op->left = num1, op->right = num2, return op
	//	EXCEPTION:
	//		When we hit '(', recursively call Parse()
	cArithNode* left = new cArithNode();
	cArithNode* center = new cArithNode();
	cArithNode* right = new cArithNode();

	//	First token
	switch (ls.front().m_Type)
	{
	case LPAREN:
	{
		//	Remove left parenthesis from list
		ls.pop_front();
		//	The whole expression between the parenthesis is left
		left = Parse(ls);
		//	Remove the following right parenthesis
		ls.pop_front();
		break;
	}
	case NUMBER:
	{
		left->m_Data = ls.front();
		ls.pop_front();
		break;
	}
	}

	//	Second Token
	switch (ls.front().m_Type)
	{
	case OPERATOR:
	{
		center->m_Data = ls.front();
		ls.pop_front();
		break;
	}
	}

	//	Third Token
	switch (ls.front().m_Type)
	{
	case LPAREN:
	{
		ls.pop_front();
		right = Parse(ls);
		ls.pop_front();
		break;
	}
	case NUMBER:
	{
		right->m_Data = ls.front();
		ls.pop_front();
		break;
	}
	}

	//	Now we have the three nodes
	center->m_LeftChild = left;
	center->m_RightChild = right;
	return center;

	//	What about the rest of the expression?
	//	Example: ((6+8)+10)*2+10/4
	//	This function will result in a tree only representing
	//	((6+8)+10)*2
	//	I believe we can simply add parenthesis on both sides
	//	(((6+8)+10)*2+10/4)
	//	This will force the parser to continue until the end
}