#ifndef MACHINA_PROCESSOR_HPP
#define MACHINA_PROCESSOR_HPP

#include "arch.hpp"
#include "memory.hpp"
#include "instruction.hpp"

#include <stack>
#include <cstdio>

/**
  * @brief	Namespace of 'machina'
  */ 
namespace machina
{	
	/**
	  * @brief	Class describing a virtual processor
	  */  
	class processor 
	{
		public:
			/**
			  * @brief	Flag indicating the processor is running 
			  */
			static const machina::arch::byte_t	running = 0x00;
			
			/**
			  * @brief	Flag indicating the processor is halted 
			  */
			static const machina::arch::byte_t	halted	= 0x01;
			
			/**
			  * @brief	Constructor
			  * 
			  * @param	memory		Pointer to the memory
			  */ 
                        processor( machina::memory *memory )
			{
				this->status = running;
				this->memory = memory;
				
				this->ip = 0x0;
			}
			
			/**
			  * @brief	Constructor
			  * 
			  * @param	memory		Pointer to the memory
			  * @param	entry		The entry point for the execution
			  */ 
                        processor( machina::memory *memory, machina::arch::pointer_t entry )
			{
				this->status = running;
				this->memory = memory;
				
				this->ip = entry;
			}
			
			/**
			  * @brief	Executes the next instruction
			  */
			void step(  );
			
			/**
			  * @brief	Executes until the processor enters halt-state or an exeception occurs
			  */ 
			void run(  );
			
			/**
			  * @brief	Dumps the processors state
			  * 
			  * @param	output		Filestream used for output
			  */ 
			void dump( FILE *output );
			
			/**
			  * @brief	Dumps a call/stack trace
			  * 
			  * @param	output		Filestream used for output
			  */
			void trace( FILE *output );
		
		private:
			/**
			  * @brief	The status of the virtual processor
			  */ 
			machina::arch::byte_t			status;
			
			/**
			  * @brief	The instruction pointer
			  */ 
			machina::arch::pointer_t		ip;
            
			/**
			  * @brief	The data-stack of the processor
			  */ 
			std::stack<machina::arch::long_t>	data_stack;
            
			/**
			  * @brief	The call-stack of the processor
			  */
			std::stack<machina::arch::pointer_t>	call_stack;
			
			/**
			  * @brief	Connects the processor with the memory of the 'machina' virtual machine
			  */ 
			machina::memory				*memory;
			
			
			
			/**
			  * @brief	Fetches the next instruction
			  * 
			  * @return			The fetched instruction
			  */
			machina::instruction fetch(  );
			
			/**
			  * @brief	Sets the instruction pointer to the address of the next instruction
			  * 
			  * @param	offset			The offset the instruction pointer is incremented by (typically the size of the current instruction)
			  */
			void next( machina::arch::size_t offset );
			
			
			
			/**
			  * @brief	Loads an immediate value (byte)
			  *
			  * @param	value			Value to be loaded
			  */ 
			void exec_load_immediate_byte( machina::arch::byte_t value );
			
			/**
			  * @brief	Loads an immediate value (short integer)
			  *
			  * @param	value			Value to be loaded
			  */ 
			void exec_load_immediate_short( machina::arch::short_t value );
			
			/**
			  * @brief	Loads an immediate value (integer)
			  *
			  * @param	value			Value to be loaded
			  */ 
			void exec_load_immediate_int( machina::arch::int_t value );
			
			/**
			  * @brief	Loads an immediate value (long integer)
			  *
			  * @param	value			Value to be loaded
			  */ 
			void exec_load_immediate_long( machina::arch::long_t value );
			
			/**
			  * @brief	Loads an value (byte) from memory
			  */ 
			void exec_load_byte(  );
			
			/**
			  * @brief	Loads an value (short integer) from memory
			  */ 
			void exec_load_short(  );
			
			/**
			  * @brief	Loads an value (integer) from memory
			  */ 
			void exec_load_int(  );
			
			/**
			  * @brief	Loads an value (long integer) from memory
			  */ 
			void exec_load_long(  );
			
			
			/**
			  * @brief	Stores a value (byte) to memory with an address given as immediate value
			  *
			  * @param	address			Address of the memory
			  */ 
			void exec_store_immediate_byte( machina::arch::pointer_t address );
			
			/**
			  * @brief	Stores a value (short integer) to memory with an address given as immediate value
			  *
			  * @param	address			Address of the memory
			  */ 
			void exec_store_immediate_short( machina::arch::pointer_t address );
			
			/**
			  * @brief	Stores a value (integer) to memory with an address given as immediate value
			  *
			  * @param	address			Address of the memory
			  */ 
			void exec_store_immediate_int( machina::arch::pointer_t address );
			
			/**
			  * @brief	Stores a value (long integer) to memory with an address given as immediate value
			  *
			  * @param	address			Address of the memory
			  */ 
			void exec_store_immediate_long( machina::arch::pointer_t address );
			
			/**
			  * @brief	Stores a value (byte) to memory
			  */ 
			void exec_store_byte(  );
			
			/**
			  * @brief	Stores a value (short integer) to memory
			  */ 
			void exec_store_short(  );
			
			/**
			  * @brief	Stores a value (integer) to memory
			  */ 
			void exec_store_int(  );
			
			/**
			  * @brief	Stores a value (long integer) to memory
			  */ 
			void exec_store_long(  );
			
			
			/**
			  * @brief	Executes the 'inc' instruction
			  */
			void exec_inc_byte(  );
			
			/**
			  * @brief	Executes the 'inc' instruction
			  */
			void exec_inc_short(  );
			
			/**
			  * @brief	Executes the 'inc' instruction
			  */
			void exec_inc_int(  );
			
			/**
			  * @brief	Executes the 'inc' instruction
			  */
			void exec_inc_long(  );
			
			/**
			  * @brief	Executes the 'dec' instruction
			  */
			void exec_dec_byte(  );
			
			/**
			  * @brief	Executes the 'dec' instruction
			  */
			void exec_dec_short(  );
			
			/**
			  * @brief	Executes the 'dec' instruction
			  */
			void exec_dec_int(  );
			
			/**
			  * @brief	Executes the 'dec' instruction
			  */
			void exec_dec_long(  );
				
			/**
			  * @brief	Executes the 'add' instruction
			  */
			void exec_add_byte(  );
			
			/**
			  * @brief	Executes the 'add' instruction
			  */
			void exec_add_short(  );
			
			/**
			  * @brief	Executes the 'add' instruction
			  */
			void exec_add_int(  );
			
			/**
			  * @brief	Executes the 'add' instruction
			  */
			void exec_add_long(  );
			
			/**
			  * @brief	Executes the 'sub' instruction
			  */
			void exec_sub_byte(  );
			
			/**
			  * @brief	Executes the 'sub' instruction
			  */
			void exec_sub_short(  );
			
			/**
			  * @brief	Executes the 'sub' instruction
			  */
			void exec_sub_int(  );
			
			/**
			  * @brief	Executes the 'sub' instruction
			  */
			void exec_sub_long(  );
			
			/**
			  * @brief	Executes the 'mul' instruction
			  */
			void exec_mul_byte(  );
			
			/**
			  * @brief	Executes the 'mul' instruction
			  */
			void exec_mul_short(  );
			/**
			 * 
			  * @brief	Executes the 'mul' instruction
			  */
			void exec_mul_int(  );
			
			/**
			  * @brief	Executes the 'mul' instruction
			  */
			void exec_mul_long(  );			
		
			/**
			  * @brief	Executes the 'div' instruction
			  */
			void exec_div_byte(  );
			
			/**
			  * @brief	Executes the 'div' instruction
			  */
			void exec_div_short(  );
			
			/**
			  * @brief	Executes the 'div' instruction
			  */
			void exec_div_int(  );
			
			/**
			  * @brief	Executes the 'div' instruction
			  */
			void exec_div_long(  );
			
			/**
			  * @brief	Executes the 'mod' instruction
			  */
			void exec_mod_byte(  );
			
			/**
			  * @brief	Executes the 'mod' instruction
			  */
			void exec_mod_short(  );
			
			/**
			  * @brief	Executes the 'mod' instruction
			  */
			void exec_mod_int(  );
			
			/**
			  * @brief	Executes the 'mod' instruction
			  */
			void exec_mod_long(  );
			
			/**
			  * @brief	Executes the 'and' instruction
			  */
			void exec_and_byte(  );
			
			/**
			  * @brief	Executes the 'and' instruction
			  */
			void exec_and_short(  );
			
			/**
			  * @brief	Executes the 'and' instruction
			  */
			void exec_and_int(  );
			
			/**
			  * @brief	Executes the 'and' instruction
			  */
			void exec_and_long(  );
			
			/**
			  * @brief	Executes the 'or' instruction
			  */
			void exec_or_byte(  );
			
			/**
			  * @brief	Executes the 'or' instruction
			  */
			void exec_or_short(  );
			
			/**
			  * @brief	Executes the 'or' instruction
			  */
			void exec_or_int(  );
			
			/**
			  * @brief	Executes the 'or' instruction
			  */
			void exec_or_long(  );
			
			/**
			  * @brief	Executes the 'xor' instruction
			  */
			void exec_xor_byte(  );
			
			/**
			  * @brief	Executes the 'xor' instruction
			  */
			void exec_xor_short(  );
			
			/**
			  * @brief	Executes the 'xor' instruction
			  */
			void exec_xor_int(  );
			
			/**
			  * @brief	Executes the 'xor' instruction
			  */
			void exec_xor_long(  );
			
			/**
			  * @brief	Executes the 'not' instruction
			  */
			void exec_not_byte(  );
			
			/**
			  * @brief	Executes the 'not' instruction
			  */
			void exec_not_short(  );
			
			/**
			  * @brief	Executes the 'not' instruction
			  */
			void exec_not_int(  );
			
			/**
			  * @brief	Executes the 'not' instruction
			  */
			void exec_not_long(  );
			
			/**
			  * @brief	Executes the 'swap' instruction
			  */
			void exec_swap(  );
			
			/**
			  * @brief	Executes the 'dup' instruction
			  */
			void exec_dup(  );
			
			/**
			  * @brief	Executes the 'rol' instruction
			  */
			void exec_rol(  );
			
			/**
			  * @brief	Executes the 'roln' instruction
			  * 
			  * @param	n			Number of stack items to be rolled
			  */
			void exec_roln( machina::arch::size_t n );
			
			
			
			/**
			  * @brief	Executes the 'frame' instruction
			  *
			  * @param	size			Size of the new stack frame
			  */ 
			void exec_frame( machina::arch::size_t size );
			
			/**
			  * @brief	Executes the 'obtain' instruction
			  *
			  * @param	index			Index of the element on the stack
			  */
			void exec_obtain( machina::arch::size_t index );
			
			/**
			  * @brief	Executes the 'place' instruction
			  *
			  * @param	index			Index of the element on the stack
			  */
			void exec_place( machina::arch::size_t index );
			
			/**
			  * @brief	Executes the 'cleanup' instruction
			  *
			  * @param	size			Size of the stack frame to be removed
			  */
			void exec_cleanup( machina::arch::size_t size );
			
			
			
			/**
			  * @brief	Executes the 'jmp' instruction
			  * 
			  * @param	address			The destionation address
			  */ 
			void exec_jmp( machina::arch::pointer_t address );
			
			/**
			  * @brief	Executes the 'jmpz' instruction
			  * 
			  * @param	address			The destionation address
			  */ 
			void exec_jmpz( machina::arch::pointer_t address );
			
			/**
			  * @brief	Executes the 'jmpnz' instruction
			  * 
			  * @param	address			The destionation address
			  */ 
			void exec_jmpnz( machina::arch::pointer_t address );
			
			/**
			  * @brief	Executes the 'jmplz' instruction
			  * 
			  * @param	address			The destionation address
			  */ 
			void exec_jmplz( machina::arch::pointer_t address );
			
			/**
			  * @brief	Executes the 'jmpgz' instruction
			  * 
			  * @param	address			The destionation address
			  */ 
			void exec_jmpgz( machina::arch::pointer_t address );
			
			/**
			  * @brief	Executes the 'jmpeq' instruction
			  * 
			  * @param	address			The destionation address
			  */ 
			void exec_jmpeq( machina::arch::pointer_t address );
			
			/**
			  * @brief	Executes the 'jmpneq' instruction
			  * 
			  * @param	address			The destionation address
			  */ 
			void exec_jmpneq( machina::arch::pointer_t address );
				
			/**
			  * @brief	Executes the 'call' instruction
			  */ 
			void exec_call(  );
				
			/**
			  * @brief	Executes the 'call' instruction
			  * 
			  * @param	address			The destionation address
			  */ 
			void exec_call( machina::arch::pointer_t address );
				
			/**
			  * @brief	Executes the 'ret' instruction
			  */
			void exec_ret(  );
			
			/**
			  * @brief	Executes the 'halt' instruction
			  */
			void exec_halt(  );
	};
}

#endif 
