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
			{ "JNZ", static_cast<uint32_t>(Codes::JNZ) },
			{ "CALL", static_cast<uint32_t>(Codes::CALL) },
			{ "RET", static_cast<uint32_t>(Codes::RET) }
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

	void Instructions::POP(std::stack<int32_t>& a_stack)
	{
		if (a_stack.empty())
		{
			return;
		}
		a_stack.pop();
	}

	void Instructions::PUSH(std::stack<int32_t>& a_stack, int32_t a_data)
	{
		a_stack.push(a_data);
	}

	void Instructions::DUP(std::stack<int32_t>& a_stack)
	{
		if (a_stack.empty())
		{
			return;
		}
		a_stack.push(a_stack.top());
	}

	void Instructions::ADD(std::stack<int32_t>& a_stack)
	{
		if (a_stack.size() < 2)
		{
			return;
		}

		uint32_t tmp1 = a_stack.top();
		a_stack.pop();
		uint32_t tmp2 = a_stack.top();
		a_stack.pop();

		a_stack.push(tmp1 + tmp2);
	}

	void Instructions::SUB(std::stack<int32_t>& a_stack)
	{
		if (a_stack.size() < 2)
		{
			return;
		}

		uint32_t tmp1 = a_stack.top();
		a_stack.pop();
		uint32_t tmp2 = a_stack.top();
		a_stack.pop();

		a_stack.push(tmp1 - tmp2);
	}

	void Instructions::MUL(std::stack<int32_t>& a_stack)
	{
		if (a_stack.size() < 2)
		{
			return;
		}

		uint32_t tmp1 = a_stack.top();
		a_stack.pop();
		uint32_t tmp2 = a_stack.top();
		a_stack.pop();

		a_stack.push(tmp1 * tmp2);
	}

	void Instructions::DIV(std::stack<int32_t>& a_stack)
	{
		if (a_stack.size() < 2)
		{
			return;
		}

		uint32_t tmp1 = a_stack.top();
		a_stack.pop();

		if (a_stack.top() == 0)
		{
			a_stack.push(tmp1);
			return;
		}

		uint32_t tmp2 = a_stack.top();
		a_stack.pop();

		a_stack.push(tmp1 / tmp2);
	}

	void Instructions::SWAP(std::stack<int32_t>& a_stack)
	{
		if (a_stack.size() < 2)
		{
			return;
		}

		uint32_t tmp1 = a_stack.top();
		a_stack.pop();
		uint32_t tmp2 = a_stack.top();
		a_stack.pop();

		a_stack.push(tmp1);
		a_stack.push(tmp2);
	}

	void Instructions::PRINT(std::stack<int32_t> a_stack)
	{
		if (a_stack.empty())
		{
			return;
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
	}

	void Instructions::PRINTC(std::stack<int32_t>& a_stack)
	{
		if (a_stack.empty())
		{
			return;
		}
		std::cout << char(a_stack.top());
	}

	void Instructions::NOP()
	{
	}

	void Instructions::HALT()
	{
	}

	void Instructions::INC(std::stack<int32_t>& a_stack)
	{
		if (a_stack.empty())
		{
			return;
		}
		uint32_t tmp = a_stack.top();
		a_stack.pop();
		a_stack.push(++tmp);
	}

	void Instructions::DEC(std::stack<int32_t>& a_stack)
	{
		if (a_stack.empty())
		{
			return;
		}
		uint32_t tmp = a_stack.top();
		a_stack.pop();
		a_stack.push(--tmp);
	}

	int32_t Instructions::JMP(std::stack<int32_t>& a_stack, int32_t a_data)
	{
		if (a_stack.empty())
		{
			return -1;
		}

		if (a_data > a_stack.size() || a_data < 0)
		{
			return -1;
		}

		return a_data;
	}

	int32_t Instructions::JZ(std::stack<int32_t>& a_stack, int32_t a_data)
	{
		if (a_stack.empty())
		{
			return -1;
		}

		if (a_data > a_stack.size() || a_data < 0)
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

	int32_t Instructions::JNZ(std::stack<int32_t>& a_stack, int32_t a_data)
	{
		if (a_stack.empty())
		{
			return -1;
		}

		if (a_data > a_stack.size() || a_data < 0)
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

	int32_t Instructions::CALL(std::stack<int32_t>& a_stack, int32_t a_data, size_t a_ret)
	{
		if (a_data < 0)
		{
			return -1;
		}

		v_retIndex = a_ret + 1;
		return a_data;
	}

	int32_t Instructions::RET()
	{
		return v_retIndex;
	}
}//namespace tiny_machine