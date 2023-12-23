#ifndef TINY_MACHINE
#define TINY_MACHINE
#include "OpCodes.h"
namespace tiny_machine
{

class TinyMachine
{
public:
	TinyMachine();
	bool Command(uint32_t a_command, uint32_t a_value = 0);
	bool CommandWithArgument(uint32_t a_command, uint32_t a_value);
	bool CommandWithNoArgument(uint32_t a_command);
	std::unordered_map<std::string, uint32_t> opcodes;
private:
	std::vector<uint32_t> v_bits;
	std::stack<int32_t> v_stack;
	Instructions v_instructions;
};
}//namespace tiny_machine

#endif