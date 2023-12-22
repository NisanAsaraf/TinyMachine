#ifndef OP_CODES
#define OP_CODES
#include <stack>
namespace tiny_machine
{
class Instructions
{
public:
	void POP(std::stack<uint32_t>& a_stack);
	void PUSH(std::stack<uint32_t>& a_stack, uint32_t a_data);
	void DUP(std::stack<uint32_t>& a_stack);
	void ADD(std::stack<uint32_t>& a_stack);
	void SUB(std::stack<uint32_t>& a_stack);
	void MUL(std::stack<uint32_t>& a_stack);
	void DIV(std::stack<uint32_t>& a_stack);
	void SWAP(std::stack<uint32_t>& a_stack);
	void PRINT(std::stack<uint32_t>& a_stack);
	void PRINTC(std::stack<uint32_t>& a_stack);
	void NOP(std::stack<uint32_t>& a_stack);
	void HALT(std::stack<uint32_t>& a_stack);
	void INC(std::stack<uint32_t>& a_stack);
	void DEC(std::stack<uint32_t>& a_stack);
};
}
#endif