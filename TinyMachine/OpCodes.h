#ifndef OP_CODES
#define OP_CODES
#include <stack>
#include <iostream>
#include <unordered_map>
#include <functional>

namespace tiny_machine
{

enum class Codes : uint32_t
{
	POP = 0b01000000000000000000000000000001,
	PUSH = 0b10000000000000000000000000000010,
	DUP = 0b01000000000000000000000000000011,
	ADD = 0b01000000000000000000000000000100,
	SUB = 0b01000000000000000000000000000101,
	MUL = 0b01000000000000000000000000000110,
	DIV = 0b01000000000000000000000000000111,
	SWAP = 0b01000000000000000000000000001000,
	PRINT = 0b01000000000000000000000000001001,
	PRINTC = 0b01000000000000000000000000001010,
	NOP = 0b01000000000000000000000000001011,
	HALT = 0b01000000000000000000000000001100,
	INC = 0b01000000000000000000000000001101,
	DEC = 0b01000000000000000000000000001110
};

std::unordered_map<std::string, uint32_t> createOpCodesMap();

class Instructions
{
public:
	Instructions();

	bool POP(std::stack<uint32_t>& a_stack);
	bool PUSH(std::stack<uint32_t>& a_stack, uint32_t a_data);
	bool DUP(std::stack<uint32_t>& a_stack);
	bool ADD(std::stack<uint32_t>& a_stack);
	bool SUB(std::stack<uint32_t>& a_stack);
	bool MUL(std::stack<uint32_t>& a_stack);
	bool DIV(std::stack<uint32_t>& a_stack);
	bool SWAP(std::stack<uint32_t>& a_stack);
	bool PRINT(std::stack<uint32_t> a_stack);
	bool PRINTC(std::stack<uint32_t>& a_stack);
	bool NOP();
	bool HALT();
	bool INC(std::stack<uint32_t>& a_stack);
	bool DEC(std::stack<uint32_t>& a_stack);
};
}
#endif