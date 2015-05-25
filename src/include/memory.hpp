#ifndef MACHINA_MEMORY_HPP
#define MACHINA_MEMORY_HPP

#include "arch.hpp"

#include <cstring>

/**
  * @brief  Namespace of 'machina'
  */ 
namespace machina
{
	/**
	* @brief  Structure describing the memory
	*/ 
	struct memory 
	{
		/**
		  * @brief  The initial size of the memory
		  */ 
		static const machina::arch::size_t   initial_size    = 512;
		
		/**
		  * @brief  Pointer to the memory
		  */ 
		machina::arch::byte_t    *ptr;
		
		/**
		  * @brief  The size of the memory
		  */ 
		machina::arch::size_t    size;
		
		/**
		  * @brief  The default constructor
		  */ 
		memory(  )
		{
			this->ptr = new machina::arch::byte_t[initial_size];
			this->size = initial_size;
		}
		
		/**
		  * @brief  Constructor
		  *
		  * @param  ptr         Pointer to the memory
		  * @param  size        The size of the memory
		  */ 
		memory( machina::arch::byte_t *ptr, machina::arch::size_t size )
		{
			if((this->ptr = new machina::arch::byte_t[size]))
			{
				memcpy(this->ptr, ptr, size);
				this->size = size;
			}				
		}
		
		/**
		  * @brief  Resizes the memory
		  * 
		  * @param  new_size    The new size of the memory
		  * @return             The size of the memory
		  */ 
		machina::arch::size_t resize( machina::arch::size_t new_size )
		{
			/**
			  * @todo   Implement this
			  */
		
			new_size = new_size;
			
			return this->size;
		}
		
		/**
		  * @brief	Reads a byte from memory
		  *
		  * @param	addr		The address to the byte in memory
		  * @return			Byte 
		  */
		machina::arch::byte_t read_byte( machina::arch::pointer_t addr )
		{
			return *((arch::byte_t*)(this->ptr + addr));
		}
		
		/**
		  * @brief	Reads a short integer from memory
		  *
		  * @param	addr		The address to the short integer in memory
		  * @return 			Short integer
		  */
		machina::arch::short_t read_short( machina::arch::pointer_t addr )
		{
			return *((arch::short_t*)(this->ptr + addr));
		}
		
		/**
		  * @brief	Reads a integer from memory
		  *
		  * @param	addr		The address to the integer in memory
		  * @return 			Integer
		  */
		machina::arch::int_t read_int( machina::arch::pointer_t addr )
		{
			return *((arch::int_t*)(this->ptr + addr));
		}
		
		/**
		  * @brief	Reads a long integer from memory
		  *
		  * @param	addr		The address to the short integer in memory
		  * @return 			Long integer
		  */
		machina::arch::long_t read_long( machina::arch::pointer_t addr )
		{
			return *((arch::long_t*)(this->ptr + addr));
		}
		
		/**
		  * @brief	Reads an instruction from memory
		  *
		  * @param	addr		The address to the instruction in memory
		  * @return 			Instruction
		  */
		machina::arch::instruction_t read_instruction( machina::arch::pointer_t addr )
		{
			return *((arch::instruction_t*)(this->ptr + addr));
		}
		
		
		/**
		  * @brief	Writes a byte to memory
		  *
		  * @param	addr		The address to the byte in memory
		  * @param	value		The byte to be written
		  */
		void write_byte( machina::arch::pointer_t addr, machina::arch::byte_t value )
		{
			*((arch::byte_t*)(this->ptr + addr)) = value;
		}
		
		/**
		  * @brief	Writes a short integer to memory
		  *
		  * @param	addr		The address to the short integer in memory
		  * @param	value		The short integer to be written
		  */
		void write_short( machina::arch::pointer_t addr, machina::arch::short_t value )
		{
			*((arch::short_t*)(this->ptr + addr)) = value;
		}
		
		/**
		  * @brief	Writes a integer to memory
		  *
		  * @param	addr		The address to the integer in memory
		  * @param	value		The integer to be written
		  */
		void write_int( machina::arch::pointer_t addr, machina::arch::int_t value )
		{
			*((arch::int_t*)(this->ptr + addr)) = value;
		}
		
		/**
		  * @brief	Writes a long integer to memory
		  *
		  * @param	addr		The address to the long integer in memory
		  * @param	value		The long integer to be written
		  */
		void write_long( machina::arch::pointer_t addr, machina::arch::long_t value )
		{
			*((arch::long_t*)(this->ptr + addr)) = value;
		}
	};
}

#endif
