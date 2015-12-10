#include "include/processor.hpp"

void machina::processor::exec_inc_int8(  )
{
	machina::arch::int8_t tmp0 = this->operand_stack.top(); this->operand_stack.pop();
	
	tmp0 = tmp0 + 1;
	
	this->operand_stack.push(tmp0);
}

void machina::processor::exec_inc_int16(  )
{
	machina::arch::int16_t tmp0 = this->operand_stack.top(); this->operand_stack.pop();
	
	tmp0 = tmp0 + 1;
	
	this->operand_stack.push(tmp0);
}

void machina::processor::exec_inc_int32(  )
{
	machina::arch::int32_t tmp0 = this->operand_stack.top(); this->operand_stack.pop();
	
	tmp0 = tmp0 + 1;
	
	this->operand_stack.push(tmp0);
}

void machina::processor::exec_inc_int64(  )
{
	machina::arch::int64_t tmp0 = this->operand_stack.top(); this->operand_stack.pop();
	
	tmp0 = tmp0 + 1;
	
	this->operand_stack.push(tmp0);
}

void machina::processor::exec_inc_float(  )
{
	machina::arch::float_t tmp0 = *((machina::arch::float_t*)&(this->operand_stack.top())); this->operand_stack.pop();
	
	tmp0 = tmp0 + 1;
	
	this->operand_stack.push(*((machina::arch::int64_t*)(&tmp0)));
}
