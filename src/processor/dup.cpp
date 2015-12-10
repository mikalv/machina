#include "include/processor.hpp"

void machina::processor::exec_dup(  )
{
	machina::arch::int64_t tmp0;
	
	tmp0 = this->operand_stack.top(); this->operand_stack.pop();
	this->operand_stack.push(tmp0);
	this->operand_stack.push(tmp0);
}

 
 
 
