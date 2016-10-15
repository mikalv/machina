#include "include/processor.hpp"

void machina::processor::exec_call_immediate( machina::arch::pointer_t address )
{
	this->call_stack.push(this->ip + machina::instruction_size_multibyte);
	
	this->ip = address;
}

void machina::processor::exec_call(  )
{
	machina::arch::pointer_t address = this->operand_stack.top(); this->operand_stack.pop();
	
	this->call_stack.push(this->ip + machina::instruction_size_byte);
	
	this->ip = address;
}
