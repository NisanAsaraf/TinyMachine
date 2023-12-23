#include "TinyMachine.h"

using namespace std;

namespace tiny_machine
{
	std::stack<uint32_t>& TinyMachine::getStack()
	{
		return v_stack;
	}

	void TinyMachine::Command(std::string a_instruction, uint32_t a_value = 0)
	{

	}

	int main()
	{
		TinyMachine tm;

		return 0;
	}
}