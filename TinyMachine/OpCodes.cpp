#include "OpCodes.h"

using namespace tiny_machine;


bool Instructions::POP(std::stack<uint32_t>& a_stack)
{
	if (a_stack.empty())
	{
		return 0;
	}
	a_stack.pop();
	return 1;
}

bool Instructions::PUSH(std::stack<uint32_t>& a_stack, uint32_t a_data)
{

}

bool Instructions::DUP(std::stack<uint32_t>& a_stack)
{
	if (a_stack.empty())
	{
		return 0;
	}
	a_stack.push(a_stack.top());
	return 1;
}

bool Instructions::ADD(std::stack<uint32_t>& a_stack)
{
	if (a_stack.size() < 2)
	{
		return 0;
	}
	uint32_t tmp = a_stack.top();
	a_stack.pop();
	a_stack.push(tmp + a_stack.top());
	return 1;
}

bool Instructions::SUB(std::stack<uint32_t>& a_stack)
{
	if (a_stack.size() < 2)
	{
		return 0;
	}
	uint32_t tmp = a_stack.top();
	a_stack.pop();
	a_stack.push(tmp - a_stack.top());
	return 1;
}

bool Instructions::MUL(std::stack<uint32_t>& a_stack)
{
	if (a_stack.size() < 2)
	{
		return 0;
	}

	uint32_t tmp = a_stack.top();
	a_stack.pop();
	a_stack.push(tmp * a_stack.top());
	return 1;
}

bool Instructions::DIV(std::stack<uint32_t>& a_stack)
{
	if (a_stack.size() < 2)
	{
		return 0;
	}

	uint32_t tmp = a_stack.top();
	a_stack.pop();

	if (a_stack.top() == 0)
	{
		a_stack.push(tmp);
		return 0;
	}
	a_stack.push(tmp / a_stack.top());

	return 1;
}

bool Instructions::SWAP(std::stack<uint32_t>& a_stack)
{
	if (a_stack.size() < 2)
	{
		return 0;
	}

	uint32_t tmp1 = a_stack.top();
	a_stack.pop();
	uint32_t tmp2 = a_stack.top();
	a_stack.pop();

	a_stack.push(tmp1);
	a_stack.push(tmp2);
	return 1;
}

bool Instructions::PRINT(std::stack<uint32_t>& a_stack)
{
	if (a_stack.empty())
	{
		return 0;
	}

	std::cout << a_stack.top() << std::endl;
	return 1;
}

bool Instructions::PRINTC(std::stack<uint32_t>& a_stack)
{
	if (a_stack.empty())
	{
		return 0;
	}
	std::cout << char(a_stack.top()) << std::endl;
	return 1;
}

bool Instructions::NOP()
{

}

bool Instructions::HALT()
{

}

bool Instructions::INC(std::stack<uint32_t>& a_stack)
{

}

bool Instructions::DEC(std::stack<uint32_t>& a_stack)
{

}