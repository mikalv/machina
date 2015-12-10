#include "include/processor.hpp"

void machina::processor::exec_load_immediate_int8( machina::arch::int8_t value )
{
	this->operand_stack.push(value);
}

void machina::processor::exec_load_immediate_int16( machina::arch::int16_t value )
{
	this->operand_stack.push(value);
}

void machina::processor::exec_load_immediate_int32( machina::arch::int32_t value )
{
	this->operand_stack.push(value);
}

void machina::processor::exec_load_immediate_int64( machina::arch::int64_t value )
{
	this->operand_stack.push(value);
}

void machina::processor::exec_load_immediate_float( machina::arch::float_t value )
{
	this->operand_stack.push(*((machina::arch::int64_t*)(&value)));
}
 
void machina::processor::exec_load_int8(  )
{
	machina::arch::int8_t value;
	machina::arch::pointer_t address;
	
	address = this->operand_stack.top(); this->operand_stack.pop();
	value = this->memory->read_int8(address);
	
	this->operand_stack.push(value);
}

void machina::processor::exec_load_int16(  )
{
	machina::arch::int16_t value;
	machina::arch::pointer_t address;
	
	address = this->operand_stack.top(); this->operand_stack.pop();
	value = this->memory->read_int16(address);
	
	this->operand_stack.push(value);
}

void machina::processor::exec_load_int32(  )
{
	machina::arch::int32_t value;
	machina::arch::pointer_t address;
	
	address = this->operand_stack.top(); this->operand_stack.pop();
	value = this->memory->read_int32(address);
	
	this->operand_stack.push(value);
}

void machina::processor::exec_load_int64(  )
{
	machina::arch::int64_t value;
	machina::arch::pointer_t address;
	
	address = this->operand_stack.top(); this->operand_stack.pop();
	value = this->memory->read_int64(address);
	
	this->operand_stack.push(value);
}

void machina::processor::exec_load_float(  )
{
	machina::arch::float_t value;
	machina::arch::pointer_t address;
	
	address = this->operand_stack.top(); this->operand_stack.pop();
	value = this->memory->read_float(address);
	
	this->operand_stack.push(*((machina::arch::int64_t*)(&value)));
}
