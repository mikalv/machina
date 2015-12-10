#include "include/processor.hpp"

void machina::processor::exec_store_immediate_int8( machina::arch::pointer_t address )
{
	machina::arch::int8_t value = this->operand_stack.top(); this->operand_stack.pop();
	
	this->memory->write_int8(address, value);
}

void machina::processor::exec_store_immediate_int16( machina::arch::pointer_t address )
{
	machina::arch::int32_t value = this->operand_stack.top(); this->operand_stack.pop();
	
	this->memory->write_int32(address, value);
}

void machina::processor::exec_store_immediate_int32( machina::arch::pointer_t address )
{
	machina::arch::int32_t value = this->operand_stack.top(); this->operand_stack.pop();
	
	this->memory->write_int32(address, value);
}

void machina::processor::exec_store_immediate_int64( machina::arch::pointer_t address )
{
	machina::arch::int64_t value = this->operand_stack.top(); this->operand_stack.pop();
	
	this->memory->write_int64(address, value);
}

void machina::processor::exec_store_immediate_float( machina::arch::pointer_t address )
{
	machina::arch::float_t value = *((machina::arch::float_t*)&(this->operand_stack.top())); this->operand_stack.pop();
	
	this->memory->write_float(address, value);
}
 
void machina::processor::exec_store_int8(  )
{
	machina::arch::pointer_t address = this->operand_stack.top(); this->operand_stack.pop();
	machina::arch::int8_t value = this->operand_stack.top(); this->operand_stack.pop();
	
	this->memory->write_int8(address, value);
}

void machina::processor::exec_store_int16(  )
{
	machina::arch::pointer_t address = this->operand_stack.top(); this->operand_stack.pop();
	machina::arch::int16_t value = this->operand_stack.top(); this->operand_stack.pop();
	
	this->memory->write_int16(address, value);
}

void machina::processor::exec_store_int32(  )
{
	machina::arch::pointer_t address = this->operand_stack.top(); this->operand_stack.pop();
	machina::arch::int32_t value = this->operand_stack.top(); this->operand_stack.pop();
	
	this->memory->write_int32(address, value);
}

void machina::processor::exec_store_int64(  )
{
	machina::arch::pointer_t address = this->operand_stack.top(); this->operand_stack.pop();
	machina::arch::int64_t value = this->operand_stack.top(); this->operand_stack.pop();
	
	this->memory->write_int64(address, value);
}

void machina::processor::exec_store_float(  )
{
	machina::arch::pointer_t address = this->operand_stack.top(); this->operand_stack.pop();
	machina::arch::float_t value = *((machina::arch::float_t*)&(this->operand_stack.top())); this->operand_stack.pop();
	
	this->memory->write_float(address, value);
}
