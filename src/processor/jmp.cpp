#include "include/processor.hpp"

void machina::processor::exec_jmp( machina::arch::pointer_t address )
{
	this->ip = address;
}

void machina::processor::exec_jmpz( machina::arch::pointer_t address )
{
	machina::arch::int64_t tmp0;
	
	tmp0 = this->operand_stack.top(); this->operand_stack.pop();
	
	this->ip = (tmp0 == 0) ? address : (this->ip + machina::instruction_size_multibyte);
}

void machina::processor::exec_jmpnz( machina::arch::pointer_t address )
{
	machina::arch::int64_t tmp0;
	
	tmp0 = this->operand_stack.top(); this->operand_stack.pop();
	
	this->ip = (tmp0 != 0) ? address : (this->ip + machina::instruction_size_multibyte);
}

void machina::processor::exec_jmplz( machina::arch::pointer_t address )
{
	machina::arch::int64_t tmp0;
	
	tmp0 = this->operand_stack.top(); this->operand_stack.pop();
	
	this->ip = (tmp0 < 0) ? address : (this->ip + machina::instruction_size_multibyte);
}

void machina::processor::exec_jmpgz( machina::arch::pointer_t address )
{
	machina::arch::int64_t tmp0;
	
	tmp0 = this->operand_stack.top(); this->operand_stack.pop();
	
	this->ip = (tmp0 > 0) ? address : (this->ip + machina::instruction_size_multibyte);
}

void machina::processor::exec_jmpeq( machina::arch::pointer_t address )
{
	machina::arch::int64_t tmp0, tmp1;
	
	tmp0 = this->operand_stack.top(); this->operand_stack.pop();
	tmp1 = this->operand_stack.top(); this->operand_stack.pop();
	
	this->ip = (tmp0 == tmp1) ? address : (this->ip + machina::instruction_size_multibyte);
}

void machina::processor::exec_jmpneq( machina::arch::pointer_t address )
{
	machina::arch::int64_t tmp0, tmp1;
	
	tmp0 = this->operand_stack.top(); this->operand_stack.pop();
	tmp1 = this->operand_stack.top(); this->operand_stack.pop();
	
	this->ip = (tmp0 != tmp1) ? address : (this->ip + machina::instruction_size_multibyte);
}
