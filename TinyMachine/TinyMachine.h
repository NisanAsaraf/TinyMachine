#ifndef TINY_MACHINE
#define TINY_MACHINE
#include "Instructions.h"
#include <fstream>
#include <cstdint>
#include <vector>

namespace tiny_machine
{

class TinyMachine
{
public:

	TinyMachine();
	bool Command(uint32_t a_command, uint32_t a_value = 0);
	int CommandWithArgument(uint32_t a_command, uint32_t a_value);
	bool CommandWithNoArgument(uint32_t a_command);
	void runCommandsFromVector();
	void StreamBitsToVector(std::string const& filename);
	std::unordered_map<std::string, uint32_t> opcodes;

private:
	std::vector<uint32_t> v_bits;
	std::stack<int32_t> v_stack;
	Instructions v_instructions;
	size_t v_index;
};
}//namespace tiny_machine

#endif