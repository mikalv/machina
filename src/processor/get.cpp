#include "include/processor.hpp"

void machina::processor::exec_get( machina::arch::size_t index )
{
	std::stack<machina::arch::pointer_t> tmp_stack;
	
	for(machina::arch::size_t n = 0; n < index; n++)
	{
		tmp_stack.push(this->call_stack.top()); this->call_stack.pop();
	}
	
	this->operand_stack.push(this->call_stack.top());
	
	for(machina::arch::size_t n = 0; n < index; n++)
	{
		this->call_stack.push(tmp_stack.top()); tmp_stack.pop();
	}
}