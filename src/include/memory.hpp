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
		  * @brief	Reads an int8 from memory
		  *
		  * @param	addr		The address to the int8 in memory
		  * @return			int8 (byte)
		  */
		machina::arch::int8_t read_int8( machina::arch::pointer_t addr )
		{
			return *((machina::arch::int8_t*)(this->ptr + addr));
		}
		
		/**
		  * @brief	Reads an int16 from memory
		  *
		  * @param	addr		The address to the int16 in memory
		  * @return			int16 (short integer)
		  */
		machina::arch::int16_t read_int16( machina::arch::pointer_t addr )
		{
			return *((machina::arch::int16_t*)(this->ptr + addr));
		}
		
		/**
		  * @brief	Reads an int32 from memory
		  *
		  * @param	addr		The address to the int32 in memory
		  * @return			int32 (integer)
		  */
		machina::arch::int32_t read_int32( machina::arch::pointer_t addr )
		{
			return *((machina::arch::int32_t*)(this->ptr + addr));
		}
		
		/**
		  * @brief	Reads an int64 from memory
		  *
		  * @param	addr		The address to the int64 in memory
		  * @return			int64 (long integer)
		  */
		machina::arch::int64_t read_int64( machina::arch::pointer_t addr )
		{
			return *((machina::arch::int64_t*)(this->ptr + addr));
		}
		
		/**
		  * @brief	Reads an float from memory
		  *
		  * @param	addr		The address to the float in memory
		  * @return			float
		  */
		machina::arch::float_t read_float( machina::arch::pointer_t addr )
		{
			return *((machina::arch::float_t*)(this->ptr + addr));
		}
		
		/**
		  * @brief	Reads an instruction from memory
		  *
		  * @param	addr		The address to the instruction in memory
		  * @return 			Instruction
		  */
		machina::arch::opcode_t *read_instruction( machina::arch::pointer_t addr )
		{
			return *((machina::arch::instruction_t*)(this->ptr + addr));
		}
		
		
		/**
		  * @brief	Writes an int8 to memory
		  *
		  * @param	addr		The address to the int8 in memory
		  * @param	value		The int8 to be written
		  */
		void write_int8( machina::arch::pointer_t addr, machina::arch::int8_t value )
		{
			*((machina::arch::int8_t*)(this->ptr + addr)) = value;
		}
		
		/**
		  * @brief	Writes an int16 to memory
		  *
		  * @param	addr		The address to the int16 in memory
		  * @param	value		The int16 to be written
		  */
		void write_int16( machina::arch::pointer_t addr, machina::arch::int16_t value )
		{
			*((machina::arch::int16_t*)(this->ptr + addr)) = value;
		}
		
		/**
		  * @brief	Writes an int32 to memory
		  *
		  * @param	addr		The address to the int32 in memory
		  * @param	value		The int32 to be written
		  */
		void write_int32( machina::arch::pointer_t addr, machina::arch::int32_t value )
		{
			*((machina::arch::int32_t*)(this->ptr + addr)) = value;
		}
		
		/**
		  * @brief	Writes an int64 to memory
		  *
		  * @param	addr		The address to the int64 in memory
		  * @param	value		The int64 to be written
		  */
		void write_int64( machina::arch::pointer_t addr, machina::arch::int64_t value )
		{
			*((machina::arch::int64_t*)(this->ptr + addr)) = value;
		}
		
		/**
		  * @brief	Writes an float to memory
		  *
		  * @param	addr		The address to the float in memory
		  * @param	value		The float to be written
		  */
		void write_float( machina::arch::pointer_t addr, machina::arch::float_t value )
		{
			*((machina::arch::float_t*)(this->ptr + addr)) = value;
		}
	};
}

#endif
