#include <cctype>
#include <cmath>
#include "ArithExp.h"

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

void cArith::ScanOp(char* input, int& index, std::list<cToken>& output)
{
	//	There are only 6 unary ops:
	//	-, +, sin, cos, tan, ctg
	//	There are only 6 binary ops:
	//	+, -, *, /, ^, %
	char c;
	c = input[index];	//	should be -, +, s, c, t
	cToken token;
	token.m_Type = VOID;

	switch (c)
	{
	case '(':
	{
		token.m_Type = LPAREN;
		token.m_Operator = 99;
		break;
	}
	case ')':
	{
		token.m_Type = RPAREN;
		token.m_Operator = 0;
		break;
	}
	case '+':
	{
		//	If the first character is '+', definitely it's unary
		if (index == 0)
		{
			token.m_Type = UOPERATOR;
			token.m_Operator = 11;
		}
		//	Otherwise it must be binary
		else
		{
			token.m_Type = BOPERATOR;
			token.m_Operator = 1;
		}
		//index += 1;
		break;
	}
	case '-':
	{
		//	If the first character is '-', definitely it's unary
		if (index == 0)
		{
			token.m_Type = UOPERATOR;
			token.m_Operator = 12;
		}
		//	If '-' is in the middle then it's complicated
		//	Case I: If it's after a digit, then it must be binary
		else if (input[index - 1] <= '9' && input[index - 1] >= '1')
		{
			token.m_Type = BOPERATOR;
			token.m_Operator = 2;
		}
		//	Case II: If it's after a '(', then it must be unary
		else if (input[index - 1] == '(')
		{
			token.m_Type = UOPERATOR;
			token.m_Operator = 12;
		}
		//	Case III: If it's after a '+', '-', '*', '/', unary
		//	However we might exclude this case as it's obscure
		else if (input[index - 1] == '+' || input[index - 1] == '-'
			|| input[index - 1] == '*' || input[index - 1] == '/')
		{
			token.m_Type = UOPERATOR;
			token.m_Operator = 12;
		}
		//index += 1;
		break;
	}
	case '*':
	{
		//	Can only be binary
		token.m_Type = BOPERATOR;
		token.m_Operator = 3;
		break;
	}
	case '/':
	{
		//	Can only be binary
		token.m_Type = BOPERATOR;
		token.m_Operator = 4;
		break;
	}
	case 's':
	{
		//	Check if it's 'sin'
		if (input[index + 1] == 'i' && input[index + 2] == 'n')
		{
			token.m_Type = UOPERATOR;
			token.m_Operator = 17;
		}
		else
		{
			std::cout << "Wrong symbol at " << index << "!" << std::endl;
		}
		index += 2;
		break;
	}
	case 'c':
	{
		//	Check if it's 'cos'
		if (input[index + 1] == 'o' && input[index + 2] == 's')
		{
			token.m_Type = UOPERATOR;
			token.m_Operator = 18;
		}
		//	Or it could be 'ctg'
		else if (input[index + 1] == 't' && input[index + 2] == 'g')
		{
			token.m_Type = UOPERATOR;
			token.m_Operator = 20;
		}
		else
		{
			std::cout << "Wrong symbol at " << index << "!" << std::endl;
		}
		index += 2;
		break;
	}
	case 't':
	{
		//	Check if it's 'tan'
		if (input[index + 1] == 'a' && input[index + 2] == 'n')
		{
			token.m_Type = UOPERATOR;
			token.m_Operator = 19;
		}
		else
		{
			std::cout << "Wrong symbol at " << index << "!" << std::endl;
		}
		index += 2;
		break;
	}
	}
	//	If the token is valid, push_back into the list
	if (token.m_Type != VOID)
	{
		output.push_back(token);
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
		//	//	Parenthesis
		//case '(':
		//	token.m_Type = OPERATOR;
		//	token.m_Operator = 7;
		//	break;
		//case ')':
		//	token.m_Type = OPERATOR;
		//	token.m_Operator = 0;
		//	break;
		//	//	Operators
		//case '+':
		//	token.m_Type = OPERATOR;
		//	token.m_Operator = 1;
		//	break;
		//case '-':
		//	token.m_Type = OPERATOR;
		//	token.m_Operator = 2;
		//	break;
		//case '*':
		//	token.m_Type = OPERATOR;
		//	token.m_Operator = 3;
		//	break;
		//case '/':
		//	token.m_Type = OPERATOR;
		//	token.m_Operator = 4;
		//	break;
		//case '^':
		//	token.m_Type = OPERATOR;
		//	token.m_Operator = 5;
		//	break;
		//case '%':
		//	token.m_Type = OPERATOR;
		//	token.m_Operator = 6;
		//	break;

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
		{
			token.m_Type = NUMBER;
			token.m_Number = ScanFloat(input, index);
			index -= 1;	//	Check ScanFloat for reason
			break;
		}
		default:
		{
			ScanOp(input, index, output);
			break;
		}
		}
		//	If the token is valid, push_back into the list
		if (token.m_Type != VOID)
		{
			output.push_back(token);
		}
		index += 1;
	}
	//	Add a VOID node at the end (Not needed so comment out)
	//token.m_Type = VOID;
	//output.push_back(token);
}

void cArith::Display()
{
	for (auto token : ls)
	{
		if (token.m_Type == NUMBER)
		{
			std::cout << token.m_Number << ", ";
		}
		else if (token.m_Type != VOID)
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

//cArithNode* cArith::Parse(std::list<cToken> ls)
//{
//	//	Parsing takes three steps for num-op-num
//	//	Step 1:
//	//	Get the number
//	//		Push it into num node
//	//		EXCEPTION:
//	//			The first char can also be '('
//	//	Step 2:
//	//	Get the op (ERROR if it's not a number)
//	//		Push it into op node
//	//		EXCEPTION:
//	//			No exception
//	//	Step 3:
//	//	Get the number
//	//		Push it into num node
//	//		EXCEPTION:
//	//			The thrid char can also be '('
//	//	Step 4:
//	//		op->left = num1, op->right = num2, return op
//	//	EXCEPTION:
//	//		When we hit '(', recursively call Parse()
//	cArithNode* left = new cArithNode();
//	cArithNode* center = new cArithNode();
//	cArithNode* right = new cArithNode();
//
//	//	First token
//	switch (ls.front().m_Type)
//	{
//	case LPAREN:
//	{
//		//	Remove left parenthesis from list
//		ls.pop_front();
//		//	The whole expression between the parenthesis is left
//		left = Parse(ls);
//		//	Remove the following right parenthesis
//		ls.pop_front();
//		break;
//	}
//	case NUMBER:
//	{
//		left->m_Data = ls.front();
//		ls.pop_front();
//		break;
//	}
//	}
//
//	if (ls.size() == 0)
//	{
//		return left;
//	}
//
//	if (ls.front().m_Type == RPAREN)
//	{
//		return left;
//	}
//
//	//	Second Token
//	switch (ls.front().m_Type)
//	{
//	case OPERATOR:
//	{
//		center->m_Data = ls.front();
//		ls.pop_front();
//		break;
//	}
//	}
//
//	if (ls.size() == 0)
//	{
//		return left;
//	}
//
//	//	Third Token
//	switch (ls.front().m_Type)
//	{
//	case LPAREN:
//	{
//		ls.pop_front();
//		right = Parse(ls);
//		ls.pop_front();
//		break;
//	}
//	case NUMBER:
//	{
//		right->m_Data = ls.front();
//		ls.pop_front();
//		break;
//	}
//	}
//
//	//	Now we have the three nodes
//	center->m_LeftChild = left;
//	center->m_RightChild = right;
//	return center;
//
//	//	What about the rest of the expression?
//	//	Example: ((6+8)+10)*2+10/4
//	//	This function will result in a tree only representing
//	//	((6+8)+10)*2
//	//	I believe we can simply add parenthesis on both sides
//	//	(((6+8)+10)*2+10/4)
//	//	This will force the parser to continue until the end
//}

void cArith::ParseList(std::list<cToken> ls)
{
	std::list<float> ls_operand;	//	Storage for operands
	std::list<int> ls_operator;		//	Storage for operators
	int priority;					//	Priority of operators
	float result;

	for (auto token : ls)
	{
		if (token.m_Type == NUMBER)
		{
			//	Push the operand into ls_operand
			ls_operand.push_front(token.m_Number);
			/*for (auto i : ls_operand)
			{
			std::cout << i << " ";
			}
			std::cout << std::endl;*/
		}
		else if (token.m_Type == UOPERATOR || token.m_Type == BOPERATOR ||
			token.m_Type == LPAREN || token.m_Type == RPAREN)
		{
			//	Push the operator into ls_operator
			ls_operator.push_front(token.m_Operator);
			priority = GetPriority(token.m_Operator);	//	Check ScanHelper()
			std::cout << std::endl;
			//	In EvaluateList, the tricky part is to
			//	evaluate unary with just one operand
			//	and binary with two operands
			EvaluateList(ls_operand, ls_operator, priority);
		}
		else
		{
			std::cout << "Unknown token!" << std::endl;
		}
	}
	//	Sometimes there are some operators unsolved
	while (ls_operator.size() > 0 && ls_operand.size() > 0)
	{
		//	if ls_operator contains only ( and )
		//	then there is no need to continue
		if (ParenOnly(ls_operator))
			break;

		//	Seperate Unary and Binary cases
		int op = ls_operator.front();
		if (op >= 11 && op <= 20)
		{
			//	Unary Operator
			float right = ls_operand.front();
			ls_operator.pop_front();
			std::cout << "Here" << std::endl;
			ls_operand.pop_front();
			std::cout << "Here 2" << std::endl;
			ls_operand.push_front(EvalUnary(op, right));
			std::cout << "Unary Evaluated" << std::endl;
		}
		else
		{
			float right = ls_operand.front();
			ls_operand.pop_front();
			float left = ls_operand.front();
			ls_operand.pop_front();
			int op = ls_operator.front();
			ls_operator.pop_front();
			//std::cout << left << " " << op << " " << right << std::endl;
			float result = EvaluateExpression(left, op, right);
			ls_operand.push_front(result);
		}
	}
	//	Display the last element of ls_operand
	std::cout << "Evaluation: " << ls_operand.front() << std::endl;
}

bool cArith::ParenOnly(std::list<int> ls_operator)
{
	if (ls_operator.size() <= 0)
		return false;
	for (auto op : ls_operator)
	{
		if (op > 0 && op < 7)
			return false;
	}
	return true;
}

int cArith::GetPriority(int op)
{
	switch (op)
	{
	case 0:
	{
		// ')' has the lowest priority
		return 0;
	}
	case 1:
	case 2:
	{
		return 1;
	}
	case 3:
	case 4:
	{
		return 2;
	}
	case 11:
	case 12:
	case 17:
	case 18:
	case 19:
	case 20:
	{
		//	Unary is higher than Binary
		return 3;
	}
	case 99:
	{
		//	'(' has the highest priority
		return 99;
	}
	}
}

void cArith::EvaluateList(std::list<float>& ls_operand,
	std::list<int>& ls_operator, int priority)
{
	//	if ls_operator only has one operator, ignore
	//	Still true for unary operators
	//	Every operator must get 'permission' from the next one
	if (ls_operator.size() <= 1)
	{
		return;
	}
	else
	{
		//	Never execute the front operator
		int front = ls_operator.front();	//	Temporary Storage
		ls_operator.pop_front();
		//	If it's '(' just ignore
		if (ls_operator.front() == 99)
		{
			//	if it's () case, simply remove
			//	as () is always from double parenthesis
			//	like ((2+3))
			if (front == 0)
			{
				ls_operator.pop_front();
				return;
			}
			else
			{
				ls_operator.push_front(front);
				return;
			}
		}
		//	Check priority of the second front operator
		if (GetPriority(ls_operator.front()) >= priority)
		{
			//	These lines do NOT consider the cases of parenthesis
			//	Must modify the code!
			//	For parenthesis we have two cases:
			//	(2+3), we remove all three of ( + )
			//	((2+3*4)), or (((((2+3*4))))), we only remove * and )
			//	because the third one is +, not (
			//	Except for () case we simply remove two instead of 3
			if (front == 0)
			{
				//	Seperate the cases of Unary and Binary
				int op = ls_operator.front();
				if (op >= 11 && op <= 20)
				{
					//	Unary Operator
					float right = ls_operand.front();
					ls_operator.pop_front();
					std::cout << "Here" << std::endl;
					ls_operand.pop_front();
					std::cout << "Here 2" << std::endl;
					ls_operand.push_front(EvalUnary(op, right));
					std::cout << "Unary Evaluated" << std::endl;
				}
				else
				{
					float right = ls_operand.front();
					ls_operand.pop_front();
					float left = ls_operand.front();
					ls_operand.pop_front();
					//int op = ls_operator.front();
					ls_operator.pop_front();
					std::cout << "Removed the second";
					if (ls_operator.front() == 99)
					{
						//	Remove left parenthesis if the third one is
						//	Sometimes it's not, e.g. ((2+3*4))
						ls_operator.pop_front();
						std::cout << "Removed the third";
					}
					std::cout << left << " " << op << " " << right << std::endl;
					float result = EvaluateExpression(left, op, right);
					ls_operand.push_front(result);
				}
			}
			else    //	Ordinary non-parenthesis cases
			{
				int op = ls_operator.front();
				if (op >= 11 && op <= 20)
				{
					//	Unary Operator
					float right = ls_operand.front();
					ls_operator.pop_front();
					ls_operand.pop_front();
					ls_operand.push_front(EvalUnary(op, right));
				}
				else
				{
					float right = ls_operand.front();
					ls_operand.pop_front();
					float left = ls_operand.front();
					ls_operand.pop_front();
					//int op = ls_operator.front();
					ls_operator.pop_front();
					std::cout << left << " " << op << " " << right << std::endl;
					float result = EvaluateExpression(left, op, right);
					ls_operand.push_front(result);
				}
			}
		}
		//	If the original front operator is NOT a parenthesis
		//	We need to keep it
		if (front != 0)	
		{
			ls_operator.push_front(front);	//	Push back the original
		}
	}
}

float cArith::EvalUnary(int op, float right)
{
	switch (op)
	{
	case 11:
		return right;
		break;
	case 12:
		return right * -1;
		break;
	case 17:
		return sin(right);
		break;
	case 18:
		return cos(right);
		break;
	case 19:
		return tan(right);
		break;
	case 20:
		//	Do not have ctan
		return tan(3.242592654 / 2 - right);
		break;
	}
}

float cArith::EvaluateExpression(float left, int op, float right)
{
	switch (op)
	{
	case 1:
	{
		return left + right;
		break;
	}
	case 2:
	{
		return left - right;
		break;
	}
	case 3:
	{
		return left * right;
		break;
	}
	case 4:
	{
		return left / right;
		break;
	}
	case 5:
	{
		return std::pow(left, right);
		break;
	}
	case 6:
	{
		return (int)left % (int)right;
		break;
	}
	}
}

//void cArith::ParseSelf()
//{
//	//	Call Parse() until the whole list has been parsed
//	m_Root = Parse(ls);
//}

//float cArith::Evaluate(cArithNode* root)
//{
//	//	Postorder traverse to evaluate the expression tree
//	if (root == nullptr)
//	{
//		return 0.0;
//	}
//
//	float left = 0.0;
//	float right = 0.0;
//
//	switch (root->m_Data.m_Type)
//	{
//	case NUMBER:
//	{
//		return root->m_Data.m_Number;
//		break;
//	}
//	case OPERATOR:
//	{
//		left = Evaluate(root->m_LeftChild);
//		right = Evaluate(root->m_RightChild);
//		switch (root->m_Data.m_Operator)
//		{
//		case 0:
//		{
//			return left + right;
//			break;
//		}
//		case 1:
//		{
//			return left - right;
//			break;
//		}
//		case 2:
//		{
//			return left * right;
//			break;
//		}
//		case 3:
//		{
//			if (right != 0)
//			{
//				return left / right;
//			}
//			else
//			{
//				return 0.0;
//			}
//			break;
//		}
//		}
//	}
//	}
//	return 0.0;
//}