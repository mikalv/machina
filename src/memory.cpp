#include "include/memory.hpp" 
#include "include/exception.hpp"

machina::memory::block::block( machina::arch::size_t size )
{
	try
	{
		this->content = new machina::arch::byte_t[size];
		this->size = size;
		this->unset_flags(~0x0);
		this->set_flags(machina::memory::block::pure_physical | machina::memory::block::free);
	}
	catch(std::bad_alloc &e)
	{
		machina::exception::out_of_memory oomem;
		char buffer[64]; sprintf(buffer, "%s: tried to allocate %ld bytes of memory\n", e.what(), size);
		oomem.message = buffer;
		throw oomem;
	}
}

machina::memory::block::block( machina::arch::byte_t *initial, machina::arch::size_t size )
{
	try
	{
		this->content = new machina::arch::byte_t[size];
		this->size = size;
		this->unset_flags(~0x0);
		this->set_flags(machina::memory::block::pure_physical | machina::memory::block::free);
		
		memcpy(this->content, initial, size);
	}
	catch(std::bad_alloc &e)
	{
		machina::exception::out_of_memory oomem;
		char buffer[64]; sprintf(buffer, "%s: tried to allocate %ld bytes of memory\n", e.what(), size);
		oomem.message = buffer;
		throw oomem;
	}
}
	
machina::memory::block::~block(  )
{
	if(this->content)
	{
		delete this->content;
		this->content = nullptr;
	}
	
	this->address = machina::arch::null;
	this->unset_flags(~0x0);
	this->set_flags(machina::memory::block::deleted);
	this->size = 0;
}

void machina::memory::block::resize( machina::arch::size_t new_size )
{
	try
	{
		machina::arch::byte_t *new_content = new machina::arch::byte_t[new_size];
		
		if(this->content)
		{
			memcpy(new_content, this->content, ((new_size > this->size) ? this->size : new_size));
			delete this->content;
		}
			
		this->content = new_content;
		this->size = new_size;
		this->unset_flags(machina::memory::block::pure_virtual);
	}
	catch(std::bad_alloc &e)
	{
		machina::exception::out_of_memory oomem;
		char buffer[64]; sprintf(buffer, "%s: tried to allocate %ld bytes of memory\n", e.what(), size);
		oomem.message = buffer;
		throw oomem;
	}
}

void machina::memory::block::map( machina::arch::pointer_t address )
{
	this->address = address;	
	this->unset_flags(machina::memory::block::pure_physical);
}

void machina::memory::block::set_flags( const machina::arch::byte_t flags )
{
	this->flags = this->flags | flags;
}

void machina::memory::block::unset_flags( const machina::arch::byte_t flags )
{
	this->flags = this->flags & ~flags;
}

machina::arch::byte_t *machina::memory::block::at_offset( machina::arch::pointer_t offset )
{
	if(offset >= this->size)
	{
		/**
		  * Error: throw Exception
		  */
		machina::exception::invalid_address invadd;
		char buffer[64]; sprintf(buffer, "access to block of memory out of bounds: @ 0x%.16lX\n", this->address + offset);
		invadd.message = buffer;
		throw invadd;
	}
	
	if(!this->content || (this->flags & machina::memory::block::pure_virtual))
	{
		/**
		  * Error: throw Exception
		  */
		machina::exception::invalid_address invadd;
		char buffer[64]; sprintf(buffer, "access to pure-virtual block of memory: @ 0x%.16lX\n", this->address + offset);
		invadd.message = buffer;
		throw invadd;
	}
	
	return (this->content + offset);
}

machina::memory::memory( machina::arch::byte_t *initial, machina::arch::size_t size )
{
	this->blocks.push_back(new memory::block(initial, size));
	this->blocks.back()->unset_flags(machina::memory::block::free);
	this->blocks.back()->set_flags(machina::memory::block::static_fixed);
	this->blocks.back()->map(machina::arch::null);
}

void machina::memory::dump( FILE *output )
{
	fprintf(output,         "Machina memory layout dump:\n");
	fprintf(output,         "  memory size (blocks): %lu           \n", this->blocks.size());

	size_t total_size = 0;  

	for(std::list<memory::block*>::iterator it = this->blocks.begin(); it != this->blocks.end(); it++)
	{
		total_size = total_size + (*it)->size;
		fprintf(output, "  memory block @ 0x%.16lX: %10lu bytes,  0x%-.2X (flags),  content @ 0x%.16lX\n", (*it)->address, (*it)->size, (*it)->flags, (uintptr_t)(*it)->content);
	}

	fprintf(output,         "  memory size (bytes):  %lu bytes     \n", total_size);
}

machina::arch::pointer_t machina::memory::alloc( machina::arch::size_t size )
{
	for(std::list<machina::memory::block*>::iterator it = this->blocks.begin(); it != this->blocks.end(); it++)
	{
		if(((*it)->flags & machina::memory::block::free))
		{
			if((*it)->flags & machina::memory::block::deleted)
			{
				it = this->blocks.erase(it); it--;
			}
			
			if((*it)->flags & machina::memory::block::pure_physical)
			{
				it = this->blocks.erase(it); it--;
			}
			
			if((*it)->size == size)
			{
				if(((*it)->flags & machina::memory::block::pure_virtual) || !(*it)->content)
				{
					(*it)->resize(size);
				}
				
				(*it)->unset_flags(machina::memory::block::free);
				return (*it)->address;
			}
			else if((*it)->size > size)
			{
				machina::memory::block *part1 = (*it);
				machina::memory::block *part2 = new machina::memory::block((*(it))->size - size);
				part1->unset_flags(machina::memory::block::free);
				part2->set_flags(machina::memory::block::free);
				
				part1->resize(size);
				part2->map((*it)->address + size);
				
				this->blocks.insert(++it, part2);
				return part1->address;
			}
		}
	}
	
	machina::arch::pointer_t address = this->blocks.back()->address + this->blocks.back()->size;
	this->blocks.push_back(new machina::memory::block(size));
	this->blocks.back()->unset_flags(machina::memory::block::free);
	this->blocks.back()->map(address);
	
	return this->blocks.back()->address;
}

void machina::memory::free( machina::arch::pointer_t address )
{
	for(std::list<machina::memory::block*>::iterator it = this->blocks.begin(); it != this->blocks.end(); it++)
	{
		if((*it)->address <= address && ((*it)->address+(*it)->size) > address)
		{
			if((*it)->flags & machina::memory::block::deleted)
			{
				/**
				  * Error: throw Exception
				  */
				machina::exception::corrupted_memory cormem;
				char buffer[64]; sprintf(buffer, "free: access to deleted block of memory: @ 0x%.16lX\n", address);
				cormem.message = buffer;
				throw cormem;
			
				break;
			}
			
			if((*it)->flags & machina::memory::block::free)
			{
				/**
				  * Error: throw Exception
				  */
				machina::exception::double_free doufre;
				char buffer[64]; sprintf(buffer, "free: double free of memory: @ 0x%.16lX\n", address);
				doufre.message = buffer;
				throw doufre;
				break;
			}
			
			if((*it)->flags & machina::memory::block::static_fixed)
			{
				/**
				  * Error: throw Exception
				  */
				machina::exception::invalid_address invadd;
				char buffer[64]; sprintf(buffer, "free: access to static-fixed block of memory: @ 0x%.16lX\n", address);
				invadd.message = buffer;
				throw invadd;
				break;
			}
			
			/**
			  * Making the block pure-virtual
			  */ 
			delete (*it)->content; (*it)->content = nullptr; 
			(*it)->set_flags(machina::memory::block::free | machina::memory::block::pure_virtual);
			
			/**
			  * Marge the block with ist previous and next one if possible
			  */ 
			machina::memory::block *curr = *(it);
			machina::memory::block *prev = *(--it); it++;
			machina::memory::block *next = *(++it); it--;
			
			if(prev->flags & machina::memory::block::free)
			{
				if(!(prev->flags & machina::memory::block::static_fixed) && !(prev->flags & machina::memory::block::pure_physical))
				{
					curr->address = prev->address;
					curr->size = curr->size + prev->size;
					
					delete prev;
					this->blocks.remove(prev);
					prev = nullptr;
				}
			}
			
			if(next->flags & machina::memory::block::free)
			{
				if(!(next->flags & machina::memory::block::static_fixed) && !(next->flags & machina::memory::block::pure_physical))
				{
					curr->size = curr->size + next->size;
					
					delete next;
					this->blocks.remove(next);
					next = nullptr;
				}
			}
			
			break;
		}
	}
}

machina::arch::byte_t *machina::memory::resolve_address( machina::arch::pointer_t address )
{
	for(std::list<machina::memory::block*>::iterator it = this->blocks.begin(); it != this->blocks.end(); it++)
	{
		if((*it)->address <= address && ((*it)->address+(*it)->size) > address)
		{
			/**
			  * Requested address located in this block
			  */
			machina::arch::pointer_t offset = address - (*it)->address;
			
			machina::arch::byte_t *ptr = (*it)->at_offset(offset);
			
			return ptr;
		}
	}
	
	/**
	  * Error: throw Exception
	  */
	machina::exception::invalid_address invadd;
	char buffer[64]; sprintf(buffer, "address outside memory: @ 0x%.16lX\n", address);
	invadd.message = buffer;
	throw invadd;
}

machina::arch::int8_t machina::memory::read_int8( machina::arch::pointer_t address )
{
	return *((machina::arch::int8_t*)this->resolve_address(address));
}

machina::arch::int16_t machina::memory::read_int16( machina::arch::pointer_t address )
{
	return *((machina::arch::int16_t*)this->resolve_address(address));
}

machina::arch::int32_t machina::memory::read_int32( machina::arch::pointer_t address )
{
	return *((machina::arch::int32_t*)this->resolve_address(address));
}

machina::arch::int64_t machina::memory::read_int64( machina::arch::pointer_t address )
{
	return *((machina::arch::int64_t*)this->resolve_address(address));
}

machina::arch::float_t machina::memory::read_float( machina::arch::pointer_t address )
{
	return *((machina::arch::float_t*)this->resolve_address(address));
}

machina::arch::opcode_t *machina::memory::read_instruction( machina::arch::pointer_t address )
{
	return *((machina::arch::instruction_t*)this->resolve_address(address));
}

void machina::memory::write_int8( machina::arch::pointer_t address, machina::arch::int8_t value )
{
	*((machina::arch::int8_t*)this->resolve_address(address)) = value;
}

void machina::memory::write_int16( machina::arch::pointer_t address, machina::arch::int16_t value )
{
	*((machina::arch::int16_t*)this->resolve_address(address)) = value;
}

void machina::memory::write_int32( machina::arch::pointer_t address, machina::arch::int32_t value )
{
	*((machina::arch::int32_t*)this->resolve_address(address)) = value;
}

void machina::memory::write_int64( machina::arch::pointer_t address, machina::arch::int64_t value )
{
	*((machina::arch::int64_t*)this->resolve_address(address)) = value;
}

void machina::memory::write_float( machina::arch::pointer_t address, machina::arch::float_t value )
{
	*((machina::arch::float_t*)this->resolve_address(address)) = value;
}
