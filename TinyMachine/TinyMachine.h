#ifndef TINY_MACHINE
#define TINY_MACHINE
#include <stack>
#include "OpCodes.h"
namespace tiny_machine
{
class TinyMachine
{
public:
	TinyMachine() = default;
	std::stack<uint32_t>& getStack();
	void Command(InsCode, uint32_t a_value = 0);
private:
	std::stack<uint32_t> v_stack;
	Instructions v_instructions;
};
}//namespace tiny_machine

#endif