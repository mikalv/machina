#include "include/processor.hpp"

void machina::processor::exec_not_int8(  )
{
	machina::arch::int8_t tmp0, result;
	
	tmp0 = this->operand_stack.top(); this->operand_stack.pop();
	result = ~tmp0;
	this->operand_stack.push(result);
}

void machina::processor::exec_not_int16(  )
{
	machina::arch::int16_t tmp0, result;
	
	tmp0 = this->operand_stack.top(); this->operand_stack.pop();
	result = ~tmp0;
	this->operand_stack.push(result);
}

void machina::processor::exec_not_int32(  )
{
	machina::arch::int32_t tmp0, result;
	
	tmp0 = this->operand_stack.top(); this->operand_stack.pop();
	result = ~tmp0;
	this->operand_stack.push(result);
}

void machina::processor::exec_not_int64(  )
{
	machina::arch::int64_t tmp0, result;
	
	tmp0 = this->operand_stack.top(); this->operand_stack.pop();
	result = ~tmp0;
	this->operand_stack.push(result);
}
 
 
