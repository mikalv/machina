#include "include/processor.hpp"

void machina::processor::exec_rol(  )
{
	machina::arch::int64_t tmp0, tmp1, tmp2;
	
	tmp0 = this->operand_stack.top(); this->operand_stack.pop();
	tmp1 = this->operand_stack.top(); this->operand_stack.pop();
	tmp2 = this->operand_stack.top(); this->operand_stack.pop();
	this->operand_stack.push(tmp0);
	this->operand_stack.push(tmp2);
	this->operand_stack.push(tmp1);
}

 
 
 
