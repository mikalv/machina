#include "include/processor.hpp"

void machina::processor::exec_setup( machina::arch::size_t size )
{
	for(machina::arch::size_t n = 0; n < size; n++)
	{
		this->call_stack.push(machina::arch::null);
	}
}