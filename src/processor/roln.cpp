#include "include/processor.hpp"

void machina::processor::exec_roln( machina::arch::size_t n )
{
	machina::arch::int64_t *tmpn = new machina::arch::int64_t[n];
	
	for(machina::arch::size_t i = 0; i < n; i++)
	{
		tmpn[i] = this->operand_stack.top(); this->operand_stack.pop();
	}
		
	this->operand_stack.push(tmpn[0]);
	
	for(machina::arch::size_t i = (n-1); i > 0; i--)
	{
		this->operand_stack.push(tmpn[i]);
	}

	delete tmpn;
}