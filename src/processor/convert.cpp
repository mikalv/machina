#include "include/processor.hpp"

void machina::processor::exec_convert_float_to_int64(  )
{
	machina::arch::float_t tmp0 = *((machina::arch::float_t*)&(this->operand_stack.top())); this->operand_stack.pop();
	
	this->operand_stack.push((machina::arch::int64_t)tmp0);
}

void machina::processor::exec_convert_int64_to_float(  )
{
	machina::arch::int64_t tmp0 = this->operand_stack.top(); this->operand_stack.pop();
	
	this->operand_stack.push((machina::arch::float_t)tmp0);
}

void machina::processor::exec_convert_int64_to_int32(  )
{
	machina::arch::int64_t tmp0 = this->operand_stack.top(); this->operand_stack.pop();
	
	this->operand_stack.push((machina::arch::int32_t)tmp0);
}

void machina::processor::exec_convert_int32_to_int16(  )
{
	machina::arch::int32_t tmp0 = this->operand_stack.top(); this->operand_stack.pop();
	
	this->operand_stack.push((machina::arch::int16_t)tmp0);
}

void machina::processor::exec_convert_int16_to_int8(  )
{
	machina::arch::int16_t tmp0 = this->operand_stack.top(); this->operand_stack.pop();
	
	this->operand_stack.push((machina::arch::int8_t)tmp0);
}

void machina::processor::exec_convert_int8_to_int16(  )
{
	machina::arch::int8_t tmp0 = this->operand_stack.top(); this->operand_stack.pop();
	
	this->operand_stack.push((machina::arch::int16_t)tmp0);
}

void machina::processor::exec_convert_int16_to_int32(  )
{
	machina::arch::int16_t tmp0 = this->operand_stack.top(); this->operand_stack.pop();
	
	this->operand_stack.push((machina::arch::int32_t)tmp0);
}

void machina::processor::exec_convert_int32_to_int64(  )
{
	machina::arch::int32_t tmp0 = this->operand_stack.top(); this->operand_stack.pop();
	
	this->operand_stack.push((machina::arch::int64_t)tmp0);
}
