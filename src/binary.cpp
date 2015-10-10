#include "include/binary.hpp"

#include <cstring>

bool machina::binary::check( const char *image )
{
	machina::binary::header comp;
	
	return !memcmp(image, &comp, sizeof(comp.magic));
}

bool machina::binary::verify( const char *image )
{
	const machina::binary::header *header  = (const machina::binary::header*)(image);
	const machina::binary::info   *info    = (const machina::binary::info*)(image + sizeof(machina::binary::header));
	const machina::arch::opcode_t *program = (const machina::arch::opcode_t*)(image + header->offset);
	const machina::binary::footer *footer  = (const machina::binary::footer*)(image + header->offset + header->size);
	
	machina::arch::size_t image_checksum = 0;
	
	for(unsigned int index = 0; index < sizeof(machina::binary::header); index++)
	{
		image_checksum += ((machina::arch::byte_t*)header)[index];
	}
	
	for(unsigned int index = 0; index < sizeof(machina::binary::info); index++)
	{
		image_checksum += ((machina::arch::byte_t*)info)[index];
	}
	
	for(unsigned int index = 0; index < header->size; index++)
	{
		image_checksum += ((machina::arch::byte_t*)program)[index];
	}
	
	return (footer->checksum == image_checksum);
}

machina::binary::header *machina::binary::read_header( const char *image )
{
	return (machina::binary::header*)(image);
}

machina::binary::info *machina::binary::read_info( const char *image )
{
	return (machina::binary::info*)(image + sizeof(machina::binary::header));
}

machina::binary::footer *machina::binary::read_footer( const char *image )
{
	return (machina::binary::footer*)(image + (machina::binary::read_header(image)->offset) + (machina::binary::read_header(image)->size));
}

machina::arch::opcode_t *machina::binary::read_program( const char *image )
{
	return (machina::arch::opcode_t*)(image + (machina::binary::read_header(image)->offset));
}
