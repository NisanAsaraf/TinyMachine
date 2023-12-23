#include "TinyMachine.h"

using namespace std;

namespace tiny_machine
{
	std::stack<uint32_t>& TinyMachine::getStack()
	{
		return v_stack;
	}

	bool TinyMachine::Command(InsCode a_code, uint32_t a_value)
	{
        bool success;
        switch (a_code) 
        {
        case InsCode::POP:
            success = v_instructions.POP(v_stack);
            break;
        case InsCode::PUSH:
            success = v_instructions.PUSH(v_stack, a_value);
            break;
        case InsCode::DUP:
            success = v_instructions.DUP(v_stack);
            break;
        case InsCode::ADD:
            success = v_instructions.ADD(v_stack);
            break;
        case InsCode::SUB:
            success = v_instructions.SUB(v_stack);
            break;
        case InsCode::MUL:
            success = v_instructions.MUL(v_stack);
            break;
        case InsCode::DIV:
            success = v_instructions.DIV(v_stack);
            break;
        case InsCode::SWAP:
            success = v_instructions.SWAP(v_stack);
            break;
        case InsCode::PRINT:
            success = v_instructions.PRINT(v_stack);
            break;
        case InsCode::PRINTC:
            success = v_instructions.PRINTC(v_stack);
            break;
        case InsCode::NOP:
            success = v_instructions.NOP();
            break;
        case InsCode::HALT:
            success = v_instructions.HALT();
            break;
        case InsCode::INC:
            success = v_instructions.INC(v_stack);
            break;
        case InsCode::DEC:
            success = v_instructions.DEC(v_stack);
            break;
        default:
            success = 0;
            break;
		}
        return success;
	}
    void test1()
    {
        TinyMachine tm;
        tm.Command(InsCode::PUSH, 12);
        tm.Command(InsCode::PRINT);

        tm.Command(InsCode::PUSH, 8);
        tm.Command(InsCode::PRINT);

        tm.Command(InsCode::DUP);
        tm.Command(InsCode::PRINT);

        tm.Command(InsCode::INC);
        tm.Command(InsCode::PRINT);

        tm.Command(InsCode::MUL);
        tm.Command(InsCode::PRINT);

        tm.Command(InsCode::SUB);
        tm.Command(InsCode::PRINT);

        tm.Command(InsCode::DUP);
        tm.Command(InsCode::PRINT);

        tm.Command(InsCode::PRINTC);
    }
	int main()
	{
        test1();
		return 0;
	}
}