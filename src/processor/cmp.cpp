#include "include/processor.hpp"

void machina::processor::exec_cmp_immediate_int8( machina::arch::int8_t value )
{
	machina::arch::int8_t tmp0, tmp1, result;
	
	tmp0 = value;
	tmp1 = this->operand_stack.top(); this->operand_stack.pop();
	
	result = (tmp1 < tmp0) ? -1 : ((tmp1 > tmp0) ? 1 : 0);
	
	this->operand_stack.push(result);
}

void machina::processor::exec_cmp_immediate_int16( machina::arch::int16_t value )
{
	machina::arch::int16_t tmp0, tmp1, result;
	
	tmp0 = value;
	tmp1 = this->operand_stack.top(); this->operand_stack.pop();
	
	result = (tmp1 < tmp0) ? -1 : ((tmp1 > tmp0) ? 1 : 0);
	
	this->operand_stack.push(result);
}

void machina::processor::exec_cmp_immediate_int32( machina::arch::int32_t value )
{
	machina::arch::int32_t tmp0, tmp1, result;
	
	tmp0 = value;
	tmp1 = this->operand_stack.top(); this->operand_stack.pop();
	
	result = (tmp1 < tmp0) ? -1 : ((tmp1 > tmp0) ? 1 : 0);
	
	this->operand_stack.push(result);
}

void machina::processor::exec_cmp_immediate_int64( machina::arch::int64_t value )
{
	machina::arch::int64_t tmp0, tmp1, result;
	
	tmp0 = value;
	tmp1 = this->operand_stack.top(); this->operand_stack.pop();
	
	result = (tmp1 < tmp0) ? -1 : ((tmp1 > tmp0) ? 1 : 0);
	
	this->operand_stack.push(result);
}

void machina::processor::exec_cmp_immediate_float( machina::arch::float_t value )
{
	machina::arch::float_t tmp0, tmp1;
	machina::arch::int64_t result;
	
	tmp0 = value;
	tmp1 = *((machina::arch::float_t*)&(this->operand_stack.top())); this->operand_stack.pop();
	
	result = (tmp1 < tmp0) ? -1 : ((tmp1 > tmp0) ? 1 : 0);
	
	this->operand_stack.push(result);
}

void machina::processor::exec_cmp_int8(  )
{
	machina::arch::int8_t tmp0, tmp1, result;
	
	tmp0 = this->operand_stack.top(); this->operand_stack.pop();
	tmp1 = this->operand_stack.top(); this->operand_stack.pop();
	
	result = (tmp1 < tmp0) ? -1 : ((tmp1 > tmp0) ? 1 : 0);
	
	this->operand_stack.push(result);
}

void machina::processor::exec_cmp_int16(  )
{
	machina::arch::int16_t tmp0, tmp1, result;
	
	tmp0 = this->operand_stack.top(); this->operand_stack.pop();
	tmp1 = this->operand_stack.top(); this->operand_stack.pop();
	
	result = (tmp1 < tmp0) ? -1 : ((tmp1 > tmp0) ? 1 : 0);
	
	this->operand_stack.push(result);
}

void machina::processor::exec_cmp_int32(  )
{
	machina::arch::int32_t tmp0, tmp1, result;
	
	tmp0 = this->operand_stack.top(); this->operand_stack.pop();
	tmp1 = this->operand_stack.top(); this->operand_stack.pop();
	
	result = (tmp1 < tmp0) ? -1 : ((tmp1 > tmp0) ? 1 : 0);
	
	this->operand_stack.push(result);
}

void machina::processor::exec_cmp_int64(  )
{
	machina::arch::int64_t tmp0, tmp1, result;
	
	tmp0 = this->operand_stack.top(); this->operand_stack.pop();
	tmp1 = this->operand_stack.top(); this->operand_stack.pop();
	
	result = (tmp1 < tmp0) ? -1 : ((tmp1 > tmp0) ? 1 : 0);
	
	this->operand_stack.push(result);
}

void machina::processor::exec_cmp_float(  )
{
	machina::arch::float_t tmp0, tmp1;
	machina::arch::int64_t result;
	
	tmp0 = *((machina::arch::float_t*)&(this->operand_stack.top())); this->operand_stack.pop();
	tmp1 = *((machina::arch::float_t*)&(this->operand_stack.top())); this->operand_stack.pop();
	
	result = (tmp1 < tmp0) ? -1 : ((tmp1 > tmp0) ? 1 : 0);
	
	this->operand_stack.push(result);
}
