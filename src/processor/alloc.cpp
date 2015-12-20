#include "include/processor.hpp"

void machina::processor::exec_alloc_immediate( machina::arch::size_t size )
{
	this->operand_stack.push(this->memory->alloc(size));	
}

void machina::processor::exec_alloc(  )
{
	machina::arch::size_t size = this->operand_stack.top(); this->operand_stack.pop();
	this->operand_stack.push(this->memory->alloc(size));
}
