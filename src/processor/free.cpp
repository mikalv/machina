#include "include/processor.hpp"

void machina::processor::exec_free(  )
{
	machina::arch::pointer_t address = this->operand_stack.top(); this->operand_stack.pop();
	this->memory->free(address);
}
 
