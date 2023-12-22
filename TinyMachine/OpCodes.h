#ifndef OP_CODES
#define OP_CODES
#include <stack>
#include <iostream>
namespace tiny_machine
{
class Instructions
{
public:
	bool POP(std::stack<uint32_t>& a_stack);
	bool PUSH(std::stack<uint32_t>& a_stack, uint32_t a_data);
	bool DUP(std::stack<uint32_t>& a_stack);
	bool ADD(std::stack<uint32_t>& a_stack);
	bool SUB(std::stack<uint32_t>& a_stack);
	bool MUL(std::stack<uint32_t>& a_stack);
	bool DIV(std::stack<uint32_t>& a_stack);
	bool SWAP(std::stack<uint32_t>& a_stack);
	bool PRINT(std::stack<uint32_t>& a_stack);
	bool PRINTC(std::stack<uint32_t>& a_stack);
	bool NOP();
	bool HALT();
	bool INC(std::stack<uint32_t>& a_stack);
	bool DEC(std::stack<uint32_t>& a_stack);
};
}
#endif