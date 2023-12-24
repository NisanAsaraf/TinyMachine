#include "Instructions.h"

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
			{ "DEC", static_cast<uint32_t>(Codes::DEC) },
			{ "JMP", static_cast<uint32_t>(Codes::JMP) },
			{ "JZ", static_cast<uint32_t>(Codes::JZ) },
			{ "JNZ", static_cast<uint32_t>(Codes::JNZ) }
		};

		return opCodes;
	}

	uint32_t GetMSB(uint32_t a_val)
	{
		return a_val >> 30;
	}

	Instructions::Instructions()
	{
	}

	bool Instructions::POP(std::stack<int32_t>& a_stack)
	{
		if (a_stack.empty())
		{
			return 0;
		}
		a_stack.pop();
		return 1;
	}

	bool Instructions::PUSH(std::stack<int32_t>& a_stack, int32_t a_data)
	{
		a_stack.push(a_data);
		return 1;
	}

	bool Instructions::DUP(std::stack<int32_t>& a_stack)
	{
		if (a_stack.empty())
		{
			return 0;
		}

		a_stack.push(a_stack.top());
		return 1;
	}

	bool Instructions::ADD(std::stack<int32_t>& a_stack)
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

	bool Instructions::SUB(std::stack<int32_t>& a_stack)
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

	bool Instructions::MUL(std::stack<int32_t>& a_stack)
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

	bool Instructions::DIV(std::stack<int32_t>& a_stack)
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

	bool Instructions::SWAP(std::stack<int32_t>& a_stack)
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

	bool Instructions::PRINT(std::stack<int32_t> a_stack)
	{
		if (a_stack.empty())
		{
			return 0;
		}

		std::stack<int32_t> reverse_stack;

		while (!a_stack.empty())
		{
			reverse_stack.push(a_stack.top());
			a_stack.pop();
		}

		while (!reverse_stack.empty())
		{
			if (GetMSB(reverse_stack.top() == 3))//negative
			{
				std::cout << ~reverse_stack.top() + 1;
			}
			else
			{
				std::cout << reverse_stack.top();
			}

			reverse_stack.pop();
			if (!reverse_stack.empty())
			{
				std::cout << ", ";
			}
		}

		std::cout << std::endl;

		return 1;
	}

	bool Instructions::PRINTC(std::stack<int32_t>& a_stack)
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

	bool Instructions::INC(std::stack<int32_t>& a_stack)
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

	bool Instructions::DEC(std::stack<int32_t>& a_stack)
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

	int32_t Instructions::JMP(std::stack<int32_t>& a_stack, int32_t a_data)
	{
		return a_data;
	}

	int32_t Instructions::JZ(std::stack<int32_t>& a_stack, int32_t a_data)
	{
		if (a_stack.empty())
		{
			return -1;
		}

		if (a_stack.top() == 0)
		{
			a_stack.pop();
			return a_data;
		}
		return -1;
	}

	int32_t Instructions::JNP(std::stack<int32_t>& a_stack, int32_t a_data)
	{
		if (a_stack.empty())
		{
			return -1;
		}

		if (a_stack.top() != 0)
		{
			a_stack.pop();
			return a_data;
		}

		return -1;
	}
}//namespace tiny_machine