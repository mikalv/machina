#include "include/processor.hpp"

void machina::processor::exec_ret(  )
{
	this->ip = this->frame_stack.top(); this->frame_stack.pop();
}
 
