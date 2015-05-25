#include "include/machina.hpp"

using machina::virtual_machine;

virtual_machine::virtual_machine(  )
{
	
}

void virtual_machine::load( machina::arch::opcode_t *image, machina::arch::size_t size, machina::arch::pointer_t entry )
{
	this->memory = new machina::memory((machina::arch::byte_t*)image, size);
	this->processor = new machina::processor(this->memory, entry);
	
	this->processor->run();
}

void virtual_machine::load( const char *path )
{
	/**
	  * @todo	Implement
	  */ 
	
	path = path;
}

void virtual_machine::reset(  )
{
	delete this->memory;
	delete this->processor;
}

void virtual_machine::dump( FILE *output )
{
	this->processor->dump(output);
}

void virtual_machine::trace( FILE *output )
{
	this->processor->trace(output);
}