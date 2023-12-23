#include "OpCodes.h"

namespace tiny_machine
{

	std::unordered_map<std::string, uint32_t> createOpCodesMap()
	{
		std::unordered_map<std::string, uint32_t> opCodes =
		{
			{ "POP", static_cast<uint32_t>(Codes::POP) },
			{ "PUSH", static_cast<uint32_t>(Codes::PUSH) },
			{ "DUP", static_cast<uint32_t>(Codes::DUP) },
			{ "ADD", static_cast<uint32_t>(Codes::ADD) },
			{ "SUB", static_cast<uint32_t>(Codes::SUB) },
			{ "MUL", static_cast<uint32_t>(Codes::MUL) },
			{ "DIV", static_cast<uint32_t>(Codes::DIV) },
			{ "SWAP", static_cast<uint32_t>(Codes::SWAP) },
			{ "PRINT", static_cast<uint32_t>(Codes::PRINT) },
			{ "PRINTC", static_cast<uint32_t>(Codes::PRINTC) },
			{ "NOP", static_cast<uint32_t>(Codes::NOP) },
			{ "HALT", static_cast<uint32_t>(Codes::HALT) },
			{ "INC", static_cast<uint32_t>(Codes::INC) },
			{ "DEC", static_cast<uint32_t>(Codes::DEC) }
		};

		return opCodes;
	}

	Instructions::Instructions()
	{
	}

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
		a_stack.push(a_data);
		return 1;
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

		uint32_t tmp1 = a_stack.top();
		a_stack.pop();
		uint32_t tmp2 = a_stack.top();
		a_stack.pop();

		a_stack.push(tmp1 + tmp2);
		return 1;
	}

	bool Instructions::SUB(std::stack<uint32_t>& a_stack)
	{
		if (a_stack.size() < 2)
		{
			return 0;
		}

		uint32_t tmp1 = a_stack.top();
		a_stack.pop();
		uint32_t tmp2 = a_stack.top();
		a_stack.pop();

		a_stack.push(tmp1 - tmp2);
		return 1;
	}

	bool Instructions::MUL(std::stack<uint32_t>& a_stack)
	{
		if (a_stack.size() < 2)
		{
			return 0;
		}

		uint32_t tmp1 = a_stack.top();
		a_stack.pop();
		uint32_t tmp2 = a_stack.top();
		a_stack.pop();

		a_stack.push(tmp1 * tmp2);
		return 1;
	}

	bool Instructions::DIV(std::stack<uint32_t>& a_stack)
	{
		if (a_stack.size() < 2)
		{
			return 0;
		}

		uint32_t tmp1 = a_stack.top();
		a_stack.pop();

		if (a_stack.top() == 0)
		{
			a_stack.push(tmp1);
			return 0;
		}

		uint32_t tmp2 = a_stack.top();
		a_stack.pop();

		a_stack.push(tmp1 / tmp2);

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

	bool Instructions::PRINT(std::stack<uint32_t> a_stack)
	{
		if (a_stack.empty())
		{
			return 0;
		}

		std::stack<uint32_t> reverse_stack;
		while (!a_stack.empty())
		{
			reverse_stack.push(a_stack.top());
			a_stack.pop();
		}

		while (!reverse_stack.empty())
		{
			std::cout << reverse_stack.top();

			reverse_stack.pop();
			if (!reverse_stack.empty())
			{
				std::cout << ", ";
			}
		}

		std::cout << std::endl;

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
		return 1;
	}

	bool Instructions::HALT()
	{
		return 1;
	}

	bool Instructions::INC(std::stack<uint32_t>& a_stack)
	{
		if (a_stack.empty())
		{
			return 0;
		}
		uint32_t tmp = a_stack.top();
		a_stack.pop();
		a_stack.push(++tmp);
		return 1;
	}

	bool Instructions::DEC(std::stack<uint32_t>& a_stack)
	{
		if (a_stack.empty())
		{
			return 0;
		}
		uint32_t tmp = a_stack.top();
		a_stack.pop();
		a_stack.push(--tmp);
		return 1;
	}
}//namespace tiny_machine