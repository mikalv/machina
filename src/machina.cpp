#include "include/machina.hpp"
#include "include/binary.hpp"

#include <iostream>
#include <fstream>

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
	
	/**
	  * Read the program image from file
	  */ 
	std::ifstream file(path, std::ifstream::in);
	file.seekg(0, file.end);
	machina::arch::size_t size = file.tellg();
	file.seekg(0, file.beg);
	
	char *image = new char[size];
	
	file.read(image, size);
	file.close();
	
	if(image && machina::binary::check(image) && machina::binary::verify(image))
	{
		std::cout << "Loading image " << path << " (" << size << " bytes) ..." << std::endl;
		
		machina::binary::header *header = machina::binary::read_header(image);
		
		machina::arch::opcode_t *exemem = machina::binary::read_program(image);
		
		this->memory = new machina::memory((machina::arch::byte_t*)exemem, header->size);
		this->processor = new machina::processor(this->memory, header->entry);
		this->processor->run();
	}
	else
	{
		std::cerr << "Error: " << path << " (" << size << " bytes): " << "not a valid executable image" << std::endl;
	}
	
	delete[] image;
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