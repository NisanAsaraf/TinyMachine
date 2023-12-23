#include "TinyMachine.h"

using namespace std;

namespace tiny_machine
{
	std::stack<uint32_t>& TinyMachine::getStack()
	{
		return v_stack;
	}

	void TinyMachine::Command(InsCode a_code, uint32_t a_value = 0)
	{
        switch (a_code) 
        {
        case InsCode::POP:
            v_instructions.POP(v_stack);
            break;
        case InsCode::PUSH:
            v_instructions.PUSH(v_stack, a_value);
            break;
        case InsCode::DUP:
            v_instructions.DUP(v_stack);
            break;
        case InsCode::ADD:
            v_instructions.ADD(v_stack);
            break;
        case InsCode::SUB:
            v_instructions.SUB(v_stack);
            break;
        case InsCode::MUL:
            v_instructions.MUL(v_stack);
            break;
        case InsCode::DIV:
            v_instructions.DIV(v_stack);
            break;
        case InsCode::SWAP:
            v_instructions.SWAP(v_stack);
            break;
        case InsCode::PRINT:
            v_instructions.PRINT(v_stack);
            break;
        case InsCode::PRINTC:
            v_instructions.PRINTC(v_stack);
            break;
        case InsCode::NOP:
            v_instructions.NOP();
            break;
        case InsCode::HALT:
            v_instructions.HALT();
            break;
        case InsCode::INC:
            v_instructions.INC(v_stack);
            break;
        case InsCode::DEC:
            v_instructions.DEC(v_stack);
            break;
        default:
            break;
		}
	}

	int main()
	{
		TinyMachine tm;

		return 0;
	}
}