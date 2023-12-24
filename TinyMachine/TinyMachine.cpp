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
        int result;
        Codes code = static_cast<Codes>(a_opcode);
        int32_t a_data = convertTwosComplementToInt(a_value);

        switch (code)
        {
        case Codes::PUSH:
            result = v_instructions.PUSH(v_stack, a_data);
            break;
        case Codes::JMP:
            result = v_instructions.JMP(v_stack, a_data);
            break;
        case Codes::JZ:
            result = v_instructions.JZ(v_stack, a_data);
            break;
        case Codes::JNZ:
            result = v_instructions.JNZ(v_stack, a_data);
            break;
        default:
            result = -1;
            break;
        }
        return result;
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

    void TinyMachine::printVector()
    {
        for (uint32_t val : v_bits)
        {
            std::cout << val << std::endl;          
        }
    }

    void TinyMachine::runCommandsFromVector()
    {
        int jumpStatus;
        for (int i = 0; i < v_bits.size(); i++)
        {
            uint32_t MSB = GetMSB(v_bits[i]);
            if (MSB == 1) //no argument 01
            {
                CommandWithNoArgument(v_bits[i]);
            }
            else if (MSB == 2) // with argument 10
            {
                if (i + 1 >= v_bits.size())
                {
                    return;
                }
                jumpStatus = CommandWithArgument(v_bits[i], v_bits[i + 1])l
                if (jumpStatus != -1)
                {
                    i = jumpStatus;
                }
                else
                {
                    i++;
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

    std::ofstream file(filename, std::ios::binary | std::ios::app);

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

void BinTest1()
{
    tiny_machine::TinyMachine tm;
    createBinTest1();
    tm.StreamBitsToVector("test1.bin");
    tm.runCommandsFromVector();
}

void test2()
{
    tiny_machine::TinyMachine tm;
    tm.Command(tm.opcodes["PUSH"], -512);
    tm.Command(tm.opcodes["PRINT"]);
}

int main()
{
    test2();
    return 0;
}