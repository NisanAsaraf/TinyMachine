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

    int TinyMachine::CommandWithArgument(uint32_t a_opcode, uint32_t a_value)
    {
        int status;
        Codes code = static_cast<Codes>(a_opcode);
        int32_t a_data = convertTwosComplementToInt(a_value);

        switch (code)
        {
        case Codes::PUSH:
            v_instructions.PUSH(v_stack, a_data);
            break;
        case Codes::JMP:
            status = v_instructions.JMP(v_stack, a_data);
            break;
        case Codes::JZ:
            status = v_instructions.JZ(v_stack, a_data);
            break;
        case Codes::JNZ:
            status = v_instructions.JNZ(v_stack, a_data);
            break;
        case Codes::CALL:
            status = v_instructions.CALL(v_stack, a_data, v_index);
            v_bits.push_back(opcodes["RET"]);
            break;
        case Codes::RET:
            status = v_instructions.RET();
            v_bits.pop_back();
            break;
        default:
            status = -1;
            break;
        }
        return status;
    }

    bool TinyMachine::CommandWithNoArgument(uint32_t a_opcode)
    {
        Codes code = static_cast<Codes>(a_opcode);

        switch (code)
        {
        case Codes::POP:
            v_instructions.POP(v_stack);
            break;
        case Codes::DUP:
            v_instructions.DUP(v_stack);
            break;
        case Codes::ADD:
            v_instructions.ADD(v_stack);
            break;
        case Codes::SUB:
            v_instructions.SUB(v_stack);
            break;
        case Codes::MUL:
            v_instructions.MUL(v_stack);
            break;
        case Codes::DIV:
            v_instructions.DIV(v_stack);
            break;
        case Codes::SWAP:
            v_instructions.SWAP(v_stack);
            break;
        case Codes::PRINT:
            v_instructions.PRINT(v_stack);
            break;
        case Codes::PRINTC:
            v_instructions.PRINTC(v_stack);
            break;
        case Codes::NOP:
            v_instructions.NOP();
            break;
        case Codes::HALT:
            v_instructions.HALT();
            break;
        case Codes::INC:
            v_instructions.INC(v_stack);
            break;
        case Codes::DEC:
            v_instructions.DEC(v_stack);
            break;
        default:
            return 0;
            break;
        }
        return 1;
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

    void TinyMachine::StreamBitsToVector(std::string const& filename)
    {
        std::ifstream file(filename, std::ios::binary);

        if (!file.is_open()) 
        {
            std::cerr << "Unable to open file." << std::endl;
        }

        uint32_t value;
        while (file.read(reinterpret_cast<char*>(&value), sizeof(uint32_t))) 
        {
            v_bits.push_back(value);
        }

        file.close();
    }

    void TinyMachine::runCommandsFromVector()
    {
        int32_t jumpStatus;
        for (v_index = 0; v_index < v_bits.size(); v_index++)
        {
            uint32_t MSB = GetMSB(v_bits[v_index]);
            if (MSB == 1) //no argument 01
            {
                if (CommandWithNoArgument(v_bits[v_index]) == -1)//only happens when HALT happens
                {
                    break;
                }
            }
            else if (MSB == 2) // with argument 10
            {
                if (v_index + 1 >= v_bits.size())
                {
                    return;
                }

                jumpStatus = CommandWithArgument(v_bits[v_index], v_bits[v_index + 1]);
                if (jumpStatus != -1)
                {
                    v_index = jumpStatus - 1;
                }
                else
                {
                    v_index++;
                }
            }
        }
    }
}

void test1()
{
    tiny_machine::TinyMachine tm;

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

void createBinTest1()
{
    tiny_machine::TinyMachine tm;
    std::string filename = "test1.bin";
    uint32_t tw = 12;
    uint32_t ew = 8;

    std::ofstream file(filename, std::ios::binary);

    if (!file.is_open())
    {
        std::cerr << "Unable to create file." << std::endl;
        return;
    }

    file.write(reinterpret_cast<const char*>(&tm.opcodes["PUSH"]), sizeof(uint32_t));
    file.write(reinterpret_cast<const char*>(&tw), sizeof(uint32_t));
    file.write(reinterpret_cast<const char*>(&tm.opcodes["PRINT"]), sizeof(uint32_t));

    file.write(reinterpret_cast<const char*>(&tm.opcodes["PUSH"]), sizeof(uint32_t));
    file.write(reinterpret_cast<const char*>(&ew), sizeof(uint32_t));
    file.write(reinterpret_cast<const char*>(&tm.opcodes["PRINT"]), sizeof(uint32_t));

    file.write(reinterpret_cast<const char*>(&tm.opcodes["DUP"]), sizeof(uint32_t));
    file.write(reinterpret_cast<const char*>(&tm.opcodes["PRINT"]), sizeof(uint32_t));

    file.write(reinterpret_cast<const char*>(&tm.opcodes["INC"]), sizeof(uint32_t));
    file.write(reinterpret_cast<const char*>(&tm.opcodes["PRINT"]), sizeof(uint32_t));

    file.write(reinterpret_cast<const char*>(&tm.opcodes["INC"]), sizeof(uint32_t));
    file.write(reinterpret_cast<const char*>(&tm.opcodes["PRINT"]), sizeof(uint32_t));

    file.write(reinterpret_cast<const char*>(&tm.opcodes["MUL"]), sizeof(uint32_t));
    file.write(reinterpret_cast<const char*>(&tm.opcodes["PRINT"]), sizeof(uint32_t));

    file.write(reinterpret_cast<const char*>(&tm.opcodes["SUB"]), sizeof(uint32_t));
    file.write(reinterpret_cast<const char*>(&tm.opcodes["PRINT"]), sizeof(uint32_t));

    file.write(reinterpret_cast<const char*>(&tm.opcodes["DUP"]), sizeof(uint32_t));
    file.write(reinterpret_cast<const char*>(&tm.opcodes["PRINT"]), sizeof(uint32_t));

    file.write(reinterpret_cast<const char*>(&tm.opcodes["PRINTC"]), sizeof(uint32_t));

    file.close();
}

void createBinTest2()
{
    tiny_machine::TinyMachine tm;
    std::string filename = "test2.bin";
    uint32_t t1 = 64;
    uint32_t t2 = 70;
    uint32_t t3 = 2;

    std::ofstream file(filename, std::ios::binary);

    if (!file.is_open())
    {
        std::cerr << "Unable to create file." << std::endl;
        return;
    }

    file.write(reinterpret_cast<const char*>(&tm.opcodes["PUSH"]), sizeof(uint32_t));
    file.write(reinterpret_cast<const char*>(&t1), sizeof(uint32_t));
    //file.write(reinterpret_cast<const char*>(&tm.opcodes["PRINT"]), sizeof(uint32_t));

    file.write(reinterpret_cast<const char*>(&tm.opcodes["INC"]), sizeof(uint32_t));
    //file.write(reinterpret_cast<const char*>(&tm.opcodes["PRINT"]), sizeof(uint32_t));

    file.write(reinterpret_cast<const char*>(&tm.opcodes["DUP"]), sizeof(uint32_t));
    //file.write(reinterpret_cast<const char*>(&tm.opcodes["PRINT"]), sizeof(uint32_t));

    file.write(reinterpret_cast<const char*>(&tm.opcodes["PRINTC"]), sizeof(uint32_t));

    file.write(reinterpret_cast<const char*>(&tm.opcodes["DUP"]), sizeof(uint32_t));
    //file.write(reinterpret_cast<const char*>(&tm.opcodes["PRINT"]), sizeof(uint32_t));

    file.write(reinterpret_cast<const char*>(&tm.opcodes["PUSH"]), sizeof(uint32_t));
    file.write(reinterpret_cast<const char*>(&t2), sizeof(uint32_t));
    //file.write(reinterpret_cast<const char*>(&tm.opcodes["PRINT"]), sizeof(uint32_t));

    file.write(reinterpret_cast<const char*>(&tm.opcodes["SUB"]), sizeof(uint32_t));
    //file.write(reinterpret_cast<const char*>(&tm.opcodes["PRINT"]), sizeof(uint32_t));

    file.write(reinterpret_cast<const char*>(&tm.opcodes["JNZ"]), sizeof(uint32_t));
    file.write(reinterpret_cast<const char*>(&t3), sizeof(uint32_t));
    //file.write(reinterpret_cast<const char*>(&tm.opcodes["PRINT"]), sizeof(uint32_t));

    file.write(reinterpret_cast<const char*>(&tm.opcodes["HALT"]), sizeof(uint32_t));

    file.close();
}

void BinTest1()
{
    tiny_machine::TinyMachine tm;
    createBinTest1();
    tm.StreamBitsToVector("test1.bin");
    tm.runCommandsFromVector();
}

void BinTest2()
{
    tiny_machine::TinyMachine tm;
    createBinTest2();
    tm.StreamBitsToVector("test2.bin");
    tm.runCommandsFromVector();
}

int main()
{
    BinTest2();
    return 0;
}