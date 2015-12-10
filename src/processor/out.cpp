#include "include/processor.hpp"

void machina::processor::exec_out_immediate( machina::arch::int8_t value )
{
	fputc(value, stdout);
}

void machina::processor::exec_out(  )
{
	machina::arch::int8_t tmp0 = this->operand_stack.top(); this->operand_stack.pop();
	
	fputc(tmp0, stdout);
}