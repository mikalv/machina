#include "include/processor.hpp"

void machina::processor::exec_ret(  )
{
	this->ip = this->call_stack.top(); this->call_stack.pop();
}
 
