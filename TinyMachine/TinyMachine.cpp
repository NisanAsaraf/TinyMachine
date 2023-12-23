#include "TinyMachine.h"

using namespace std;

namespace tiny_machine
{
    TinyMachine::TinyMachine()
    {
        opcodes = createOpCodesMap();
    }

    int32_t convertTwosComplementToInt(uint32_t a_value)
    {
        if (GetMSB(a_value) == 3)//11
        {
            return -static_cast<int32_t>((~a_value) + 1);
        }
        else if(GetMSB(a_value) == 0)//00
        {
            return static_cast<int32_t>(a_value);
        }
    }
    bool TinyMachine::CommandWithArgument(uint32_t a_opcode, uint32_t a_value)
    {
        bool success;
        Codes code = static_cast<Codes>(a_opcode);
        int32_t a_data = convertTwosComplementToInt(a_value);

        switch (code)
        {
        case Codes::PUSH:
            success = v_instructions.PUSH(v_stack, a_data);
            break;
        default:
            success = 0;
            break;
        }
        return success;
    }

    bool TinyMachine::CommandWithNoArgument(uint32_t a_opcode)
    {
        bool success;
        Codes code = static_cast<Codes>(a_opcode);

        switch (code)
        {
        case Codes::POP:
            success = v_instructions.POP(v_stack);
            break;
        case Codes::DUP:
            success = v_instructions.DUP(v_stack);
            break;
        case Codes::ADD:
            success = v_instructions.ADD(v_stack);
            break;
        case Codes::SUB:
            success = v_instructions.SUB(v_stack);
            break;
        case Codes::MUL:
            success = v_instructions.MUL(v_stack);
            break;
        case Codes::DIV:
            success = v_instructions.DIV(v_stack);
            break;
        case Codes::SWAP:
            success = v_instructions.SWAP(v_stack);
            break;
        case Codes::PRINT:
            success = v_instructions.PRINT(v_stack);
            break;
        case Codes::PRINTC:
            success = v_instructions.PRINTC(v_stack);
            break;
        case Codes::NOP:
            success = v_instructions.NOP();
            break;
        case Codes::HALT:
            success = v_instructions.HALT();
            break;
        case Codes::INC:
            success = v_instructions.INC(v_stack);
            break;
        case Codes::DEC:
            success = v_instructions.DEC(v_stack);
            break;
        default:
            success = 0;
            break;
        }
        return success;
    }

	bool TinyMachine::Command(uint32_t a_opcode, uint32_t a_value)
	{
        uint32_t MSB = GetMSB(a_opcode);
        if (MSB == 1) //no argument 01
        {
            return CommandWithNoArgument(a_opcode);
        }
        else if (MSB == 2) // with argument 10
        {
            return CommandWithArgument(a_opcode, a_value);
        }

        return 0;
	}

    void test1()
    {
        TinyMachine tm;
        tm.Command(tm.opcodes["PUSH"], 12);
        tm.Command(tm.opcodes["PRINT"]);

        tm.Command(tm.opcodes["PUSH"], 8);
        tm.Command(tm.opcodes["PRINT"]);

        tm.Command(tm.opcodes["DUP"]);
        tm.Command(tm.opcodes["PRINT"]);

        tm.Command(tm.opcodes["INC"]);
        tm.Command(tm.opcodes["PRINT"]);

        tm.Command(tm.opcodes["INC"]);
        tm.Command(tm.opcodes["PRINT"]);

        tm.Command(tm.opcodes["MUL"]);
        tm.Command(tm.opcodes["PRINT"]);

        tm.Command(tm.opcodes["SUB"]);
        tm.Command(tm.opcodes["PRINT"]);

        tm.Command(tm.opcodes["DUP"]);
        tm.Command(tm.opcodes["PRINT"]);

        tm.Command(tm.opcodes["PRINTC"]);
    }

    void test2()
    {
        TinyMachine tm;
        tm.Command(tm.opcodes["PUSH"], -512);
        tm.Command(tm.opcodes["PRINT"]);
    }

    void test3()
    {

    }
}

int main()
{
    tiny_machine::test1();
    return 0;
}