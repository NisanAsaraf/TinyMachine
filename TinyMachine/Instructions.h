#ifndef OP_CODES
#define OP_CODES
#include <iostream>
#include <stack>
#include <unordered_map>

namespace tiny_machine
{

enum class Codes : uint32_t
{
	POP		=	0b01000000000000000000000000000001,
	PUSH	=	0b10000000000000000000000000000010,
	DUP		=	0b01000000000000000000000000000011,
	ADD		=	0b01000000000000000000000000000100,
	SUB		=	0b01000000000000000000000000000101,
	MUL		=	0b01000000000000000000000000000110,
	DIV		=	0b01000000000000000000000000000111,
	SWAP	=	0b01000000000000000000000000001000,
	PRINT	=	0b01000000000000000000000000001001,
	PRINTC	=	0b01000000000000000000000000001010,
	NOP		=	0b01000000000000000000000000001011,
	HALT	=	0b01000000000000000000000000001100,
	INC		=	0b01000000000000000000000000001101,
	DEC		=	0b01000000000000000000000000001110,
	JMP		=	0b10000000000000000000000000001111,
	JZ		=	0b10000000000000000000000000010000,
	JNZ		=	0b10000000000000000000000000010001,
	CALL	=	0b10000000000000000000000000010010,
	RET		=	0b10000000000000000000000000010011

};

std::unordered_map<std::string, uint32_t> createOpCodesMap();
uint32_t GetMSB(uint32_t a_val);

class Instructions
{
public:
	Instructions();

	void POP(std::stack<int32_t>& a_stack);
	int32_t PUSH(std::stack<int32_t>& a_stack, int32_t a_data);
	void DUP(std::stack<int32_t>& a_stack);
	void ADD(std::stack<int32_t>& a_stack);
	void SUB(std::stack<int32_t>& a_stack);
	void MUL(std::stack<int32_t>& a_stack);
	void DIV(std::stack<int32_t>& a_stack);
	void SWAP(std::stack<int32_t>& a_stack);
	void PRINT(std::stack<int32_t> a_stack);
	void PRINTC(std::stack<int32_t>& a_stack);
	void NOP();
	int32_t HALT();
	void INC(std::stack<int32_t>& a_stack);
	void DEC(std::stack<int32_t>& a_stack);
	int32_t JMP(std::stack<int32_t>& a_stack, int32_t a_data);
	int32_t JZ(std::stack<int32_t>& a_stack, int32_t a_data);
	int32_t JNZ(std::stack<int32_t>& a_stack, int32_t a_data);
	int32_t CALL(std::stack<int32_t>& a_stack, int32_t a_data);
};
}//namespace tiny_machine
#endif