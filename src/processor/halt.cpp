#include "include/processor.hpp"

void machina::processor::exec_halt(  )
{
	this->status |= processor::halted; 
}
