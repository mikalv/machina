#ifndef MACHINA_MEMORY_HPP
#define MACHINA_MEMORY_HPP

#include "arch.hpp"

#include <cstring>
#include <list>

#include <iostream>

/**
  * @brief  Namespace of 'machina'
  */ 
namespace machina
{
	/**
	  * @brief	Structure describing memory
	  */
	struct memory
	{
		/**
		  * @brief	Structure describing a block of memory
		  */ 
		struct block
		{
			/**
			  * @brief	The content of the memory-block
			  */
			machina::arch::byte_t			*content;
			
			/**
			  * @brief	The size of the memory-block
			  */
			machina::arch::size_t			size;
			
			/**
			  * @brief	The address, the memory-block starts
			  */
			machina::arch::pointer_t		address;
			
			/**
			  * @brief	Flags of the memory block e.g. used/free
			  */ 
			machina::arch::byte_t			flags;
			
			/**
			  * @brief	Flag indicating a free block of memory
			  */
			static const machina::arch::byte_t	free 		= 0x01;
			
			/**
			  * @brief	Flag indicating a pure virtual block of memory (without content)
			  */
			static const machina::arch::byte_t	pure_virtual 	= 0x02;
			
			/**
			  * @brief	Flag indicating a pure physical block of memory (without address)
			  */
			static const machina::arch::byte_t	pure_physical 	= 0x04;
			
			/**
			  * @brief	Flag indicating a static-fixed block of memory (cannot freed)
			  * 		Should be used for initial memory containing program-code
			  */
			static const machina::arch::byte_t	static_fixed 	= 0x08;
			
			/**
			  * @brief	Flag indicating a deleted block of memory (cannot be used anymore)
			  */
			static const machina::arch::byte_t	deleted 	= 0x10;
			
			/**
			  * @brief	Creates a block of memory with given size (content remains uninitialized)
			  * 
			  * @param	size		The size of the block
			  */
			block( machina::arch::size_t size );
			
			/**
			  * @brief	Creates a block of memory with given initial content
			  *
			  * @param	initial		The initial content
			  * @param	size		The size of the block
			  */ 
			block( machina::arch::byte_t *initial, machina::arch::size_t size );
			
			/**
			  * @brief	The destructor
			  */ 
			~block(  );
			
			/**
			  * @brief	Resizes the memory-block
			  *
			  * @param	new_size	The new size of the memory-block
			  */ 
			void resize( machina::arch::size_t new_size );
			
			/**
			  * @brief	Maps the memory-block to a given address
			  *
			  * @param	address		The address
			  */ 
			void map( machina::arch::pointer_t address );
			
			/**
			  * @brief	Sets flags
			  *
			  * @param	flags		The flags
			  */
			void set_flags( const machina::arch::byte_t flags );
			
			/**
			  * @brief	Un-sets flags
			  *
			  * @param	flags		The flags
			  */ 
			void unset_flags( const machina::arch::byte_t flags );
			
			/**
			  * @brief	Gets a pointer to the content with given offset
			  *
			  * @param	offset		The offset
			  * @return			Pointer to the content, or nullpointer if the offset is out of range
			  */ 
			machina::arch::byte_t *at_offset( machina::arch::pointer_t offset );
		};
		
		/**
		  * @brief	The memory-blocks
		  */
		std::list<memory::block*>	blocks;
		
		/**
		  * @brief	Creates a memory
		  *
		  * @param	initial		The initial content of the memory (copied into the first block)
		  * @param	size		The size of the initial memory
		  */ 
		memory( machina::arch::byte_t *initial, machina::arch::size_t size );
		
		/**
		  * @brief	Print a dump of the memory layout
		  *
		  * @param	output		The output stream the dump is written to
		  */ 
		void dump( FILE *output );
		
		/**
		  * @brief	Allocates memory
		  *
		  * @param	size		The size of the requested memory block
		  */ 
		machina::arch::pointer_t alloc( machina::arch::size_t size );
		
		/**
		  * @brief	Frees memory
		  *
		  * @param	address		The address of the memory block (any address within the block)
		  */ 
		void free( machina::arch::pointer_t address );
		
		/**
		  * @brief	Resolves an address
		  *		Searches for the memory-block containing the requested address
		  *		Computes the offset
		  * 
		  * @param	address 	The address
		  * @return			Pointer to the content of the requested address
		  */
		machina::arch::byte_t *resolve_address( machina::arch::pointer_t address );
		
		/**
		  * @brief	Reads an int8 from memory
		  *
		  * @param	address		The address to the int8 in memory
		  * @return			int8 (byte)
		  */
		machina::arch::int8_t read_int8( machina::arch::pointer_t address );
		
		/**
		  * @brief	Reads an int16 from memory
		  *
		  * @param	address		The address to the int16 in memory
		  * @return			int16 (short integer)
		  */
		machina::arch::int16_t read_int16( machina::arch::pointer_t address );
		
		/**
		  * @brief	Reads an int32 from memory
		  *
		  * @param	address		The address to the int32 in memory
		  * @return			int32 (integer)
		  */
		machina::arch::int32_t read_int32( machina::arch::pointer_t address );
		
		/**
		  * @brief	Reads an int64 from memory
		  *
		  * @param	address		The address to the int64 in memory
		  * @return			int64 (long integer)
		  */
		machina::arch::int64_t read_int64( machina::arch::pointer_t address );
		
		/**
		  * @brief	Reads an float from memory
		  *
		  * @param	address		The address to the float in memory
		  * @return			float
		  */
		machina::arch::float_t read_float( machina::arch::pointer_t address );
		
		/**
		  * @brief	Reads an instruction from memory
		  *
		  * @param	address		The address to the instruction in memory
		  * @return 			Instruction
		  */
		machina::arch::opcode_t *read_instruction( machina::arch::pointer_t address );
		
		/**
		  * @brief	Writes an int8 to memory
		  *
		  * @param	address		The address to the int8 in memory
		  * @param	value		The int8 to be written
		  */
		void write_int8( machina::arch::pointer_t address, machina::arch::int8_t value );
		
		/**
		  * @brief	Writes an int16 to memory
		  *
		  * @param	address		The address to the int16 in memory
		  * @param	value		The int16 to be written
		  */
		void write_int16( machina::arch::pointer_t address, machina::arch::int16_t value );
		
		/**
		  * @brief	Writes an int32 to memory
		  *
		  * @param	address		The address to the int32 in memory
		  * @param	value		The int32 to be written
		  */
		void write_int32( machina::arch::pointer_t address, machina::arch::int32_t value );
		
		/**
		  * @brief	Writes an int64 to memory
		  *
		  * @param	address		The address to the int64 in memory
		  * @param	value		The int64 to be written
		  */
		void write_int64( machina::arch::pointer_t address, machina::arch::int64_t value );
		
		/**
		  * @brief	Writes an float to memory
		  *
		  * @param	address		The address to the float in memory
		  * @param	value		The float to be written
		  */
		void write_float( machina::arch::pointer_t address, machina::arch::float_t value );
	};
	
}

#endif