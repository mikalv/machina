#include "include/processor.hpp"

void machina::processor::exec_frame( machina::arch::size_t size )
{
	for(machina::arch::size_t n = 0; n < size; n++)
	{
		this->frame_stack.push(machina::arch::null);
	}
}