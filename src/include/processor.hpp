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
			  * @brief	The operand-stack of the processor
			  */ 
			std::stack<machina::arch::int64_t>	operand_stack;
            
			/**
			  * @brief	The frame-stack of the processor
			  */
			std::stack<machina::arch::pointer_t>	frame_stack;
			
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
			  * @brief	Loads an immediate value (int8 - byte)
			  *
			  * @param	value			Value to be loaded
			  */ 
			void exec_load_immediate_int8( machina::arch::int8_t value );
			
			/**
			  * @brief	Loads an immediate value (int16 - short integer)
			  *
			  * @param	value			Value to be loaded
			  */ 
			void exec_load_immediate_int16( machina::arch::int16_t value );
			
			/**
			  * @brief	Loads an immediate value (int32 - integer)
			  *
			  * @param	value			Value to be loaded
			  */ 
			void exec_load_immediate_int32( machina::arch::int32_t value );
			
			/**
			  * @brief	Loads an immediate value (int64 - long integer)
			  *
			  * @param	value			Value to be loaded
			  */ 
			void exec_load_immediate_int64( machina::arch::int64_t value );
			
			/**
			  * @brief	Loads an immediate value (float)
			  *
			  * @param	value			Value to be loaded
			  */ 
			void exec_load_immediate_float( machina::arch::float_t value );
			
			/**
			  * @brief	Loads an value (int8) from memory
			  */ 
			void exec_load_int8(  );
			
			/**
			  * @brief	Loads an value (int16) from memory
			  */ 
			void exec_load_int16(  );
			
			/**
			  * @brief	Loads an value (int32) from memory
			  */ 
			void exec_load_int32(  );
			
			/**
			  * @brief	Loads an value (int64) from memory
			  */ 
			void exec_load_int64(  );
			
			/**
			  * @brief	Loads an value (float) from memory
			  */ 
			void exec_load_float(  );
			
			
			/**
			  * @brief	Converts a value (float) to another type (int64)
			  */ 
			void exec_convert_float_to_int64(  );
			
			/**
			  * @brief	Converts a value (int64) to another type (float)
			  */
			void exec_convert_int64_to_float(  );
			
			/**
			  * @brief	Converts a value (int64) to another type (int32)
			  */
			void exec_convert_int64_to_int32(  );
			
			/**
			  * @brief	Converts a value (int32) to another type (int16)
			  */
			void exec_convert_int32_to_int16(  );
			
			/**
			  * @brief	Converts a value (int16) to another type (int8)
			  */
			void exec_convert_int16_to_int8(  );
			
			/**
			  * @brief	Stores a value (int8) to memory with an address given as immediate value
			  *
			  * @param	address			Address of the memory
			  */ 
			void exec_store_immediate_int8( machina::arch::pointer_t address );
			
			/**
			  * @brief	Stores a value (int16) to memory with an address given as immediate value
			  *
			  * @param	address			Address of the memory
			  */ 
			void exec_store_immediate_int16( machina::arch::pointer_t address );
			
			/**
			  * @brief	Stores a value (int32) to memory with an address given as immediate value
			  *
			  * @param	address			Address of the memory
			  */ 
			void exec_store_immediate_int32( machina::arch::pointer_t address );
			
			/**
			  * @brief	Stores a value (int64) to memory with an address given as immediate value
			  *
			  * @param	address			Address of the memory
			  */ 
			void exec_store_immediate_int64( machina::arch::pointer_t address );
			
			/**
			  * @brief	Stores a value (float) to memory with an address given as immediate value
			  *
			  * @param	address			Address of the memory
			  */ 
			void exec_store_immediate_float( machina::arch::pointer_t address );
			
			/**
			  * @brief	Stores a value (int8) to memory
			  */ 
			void exec_store_int8(  );
			
			/**
			  * @brief	Stores a value (int16) to memory
			  */ 
			void exec_store_int16(  );
			
			/**
			  * @brief	Stores a value (int32) to memory
			  */ 
			void exec_store_int32(  );
			
			/**
			  * @brief	Stores a value (int64) to memory
			  */ 
			void exec_store_int64(  );
			
			/**
			  * @brief	Stores a value (float) to memory
			  */ 
			void exec_store_float(  );
			
			
			/**
			  * @brief	Converts a value (int8) to another type (int16)
			  */
			void exec_convert_int8_to_int16(  );
			
			/**
			  * @brief	Converts a value (int16) to another type (int32)
			  */
			void exec_convert_int16_to_int32(  );
			
			/**
			  * @brief	Converts a value (int32) to another type (int64)
			  */
			void exec_convert_int32_to_int64(  );
			
			
			/**
			  * @brief	Executes the 'inc' instruction
			  */
			void exec_inc_int8(  );
			
			/**
			  * @brief	Executes the 'inc' instruction
			  */
			void exec_inc_int16(  );
			
			/**
			  * @brief	Executes the 'inc' instruction
			  */
			void exec_inc_int32(  );
			
			/**
			  * @brief	Executes the 'inc' instruction
			  */
			void exec_inc_int64(  );
			
			/**
			  * @brief	Executes the 'inc' instruction
			  */
			void exec_inc_float(  );
			
			/**
			  * @brief	Executes the 'dec' instruction
			  */
			void exec_dec_int8(  );
			
			/**
			  * @brief	Executes the 'dec' instruction
			  */
			void exec_dec_int16(  );
			
			/**
			  * @brief	Executes the 'dec' instruction
			  */
			void exec_dec_int32(  );
			
			/**
			  * @brief	Executes the 'dec' instruction
			  */
			void exec_dec_int64(  );
			
			/**
			  * @brief	Executes the 'dec' instruction
			  */
			void exec_dec_float(  );
			
			
			/**
			  * @brief	Executes the 'add' instruction
			  */
			void exec_add_immediate_int8( machina::arch::int8_t value );
			
			/**
			  * @brief	Executes the 'add' instruction
			  */
			void exec_add_immediate_int16( machina::arch::int16_t value );
			
			/**
			  * @brief	Executes the 'add' instruction
			  */
			void exec_add_immediate_int32( machina::arch::int32_t value );
			
			/**
			  * @brief	Executes the 'add' instruction
			  */
			void exec_add_immediate_int64( machina::arch::int64_t value );
			
			/**
			  * @brief	Executes the 'add' instruction
			  */
			void exec_add_immediate_float( machina::arch::float_t value );
			
			/**
			  * @brief	Executes the 'add' instruction
			  */
			void exec_add_int8(  );
			
			/**
			  * @brief	Executes the 'add' instruction
			  */
			void exec_add_int16(  );
			
			/**
			  * @brief	Executes the 'add' instruction
			  */
			void exec_add_int32(  );
			
			/**
			  * @brief	Executes the 'add' instruction
			  */
			void exec_add_int64(  );
			
			/**
			  * @brief	Executes the 'add' instruction
			  */
			void exec_add_float(  );
			
			
			/**
			  * @brief	Executes the 'sub' instruction
			  */
			void exec_sub_immediate_int8( machina::arch::int8_t value );
			
			/**
			  * @brief	Executes the 'sub' instruction
			  */
			void exec_sub_immediate_int16( machina::arch::int16_t value );
			
			/**
			  * @brief	Executes the 'sub' instruction
			  */
			void exec_sub_immediate_int32( machina::arch::int32_t value );
			
			/**
			  * @brief	Executes the 'sub' instruction
			  */
			void exec_sub_immediate_int64( machina::arch::int64_t value );
			
			/**
			  * @brief	Executes the 'sub' instruction
			  */
			void exec_sub_immediate_float( machina::arch::float_t value );
			
			/**
			  * @brief	Executes the 'sub' instruction
			  */
			void exec_sub_int8(  );
			
			/**
			  * @brief	Executes the 'sub' instruction
			  */
			void exec_sub_int16(  );
			
			/**
			  * @brief	Executes the 'sub' instruction
			  */
			void exec_sub_int32(  );
			
			/**
			  * @brief	Executes the 'sub' instruction
			  */
			void exec_sub_int64(  );
			
			/**
			  * @brief	Executes the 'sub' instruction
			  */
			void exec_sub_float(  );
			
			
			
			/**
			  * @brief	Executes the 'mul' instruction
			  */
			void exec_mul_immediate_int8( machina::arch::int8_t value );
			
			/**
			  * @brief	Executes the 'mul' instruction
			  */
			void exec_mul_immediate_int16( machina::arch::int16_t value );
			
			/**
			  * @brief	Executes the 'mul' instruction
			  */
			void exec_mul_immediate_int32( machina::arch::int32_t value );
			
			/**
			  * @brief	Executes the 'mul' instruction
			  */
			void exec_mul_immediate_int64( machina::arch::int64_t value );
			
			/**
			  * @brief	Executes the 'mul' instruction
			  */
			void exec_mul_immediate_float( machina::arch::float_t value );
			
			/**
			  * @brief	Executes the 'mul' instruction
			  */
			void exec_mul_int8(  );
			
			/**
			  * @brief	Executes the 'mul' instruction
			  */
			void exec_mul_int16(  );
			
			/**
			  * @brief	Executes the 'mul' instruction
			  */
			void exec_mul_int32(  );
			
			/**
			  * @brief	Executes the 'mul' instruction
			  */
			void exec_mul_int64(  );
			
			/**
			  * @brief	Executes the 'mul' instruction
			  */
			void exec_mul_float(  );
			
			
			
			/**
			  * @brief	Executes the 'div' instruction
			  */
			void exec_div_immediate_int8( machina::arch::int8_t value );
			
			/**
			  * @brief	Executes the 'div' instruction
			  */
			void exec_div_immediate_int16( machina::arch::int16_t value );
			
			/**
			  * @brief	Executes the 'div' instruction
			  */
			void exec_div_immediate_int32( machina::arch::int32_t value );
			
			/**
			  * @brief	Executes the 'div' instruction
			  */
			void exec_div_immediate_int64( machina::arch::int64_t value );
			
			/**
			  * @brief	Executes the 'div' instruction
			  */
			void exec_div_immediate_float( machina::arch::float_t value );
			
			/**
			  * @brief	Executes the 'div' instruction
			  */
			void exec_div_int8(  );
			
			/**
			  * @brief	Executes the 'div' instruction
			  */
			void exec_div_int16(  );
			
			/**
			  * @brief	Executes the 'div' instruction
			  */
			void exec_div_int32(  );
			
			/**
			  * @brief	Executes the 'div' instruction
			  */
			void exec_div_int64(  );
			
			/**
			  * @brief	Executes the 'div' instruction
			  */
			void exec_div_float(  );
			
			
			
			/**
			  * @brief	Executes the 'mod' instruction
			  */
			void exec_mod_immediate_int8( machina::arch::int8_t value );
			
			/**
			  * @brief	Executes the 'mod' instruction
			  */
			void exec_mod_immediate_int16( machina::arch::int16_t value );
			
			/**
			  * @brief	Executes the 'mod' instruction
			  */
			void exec_mod_immediate_int32( machina::arch::int32_t value );
			
			/**
			  * @brief	Executes the 'mod' instruction
			  */
			void exec_mod_immediate_int64( machina::arch::int64_t value );
			
			/**
			  * @brief	Executes the 'mod' instruction
			  */
			void exec_mod_int8(  );
			
			/**
			  * @brief	Executes the 'mod' instruction
			  */
			void exec_mod_int16(  );
			
			/**
			  * @brief	Executes the 'mod' instruction
			  */
			void exec_mod_int32(  );
			
			/**
			  * @brief	Executes the 'mod' instruction
			  */
			void exec_mod_int64(  );
			
			
			
			/**
			  * @brief	Executes the 'and' instruction
			  */
			void exec_and_immediate_int8( machina::arch::int8_t value );
			
			/**
			  * @brief	Executes the 'and' instruction
			  */
			void exec_and_immediate_int16( machina::arch::int16_t value );
			
			/**
			  * @brief	Executes the 'and' instruction
			  */
			void exec_and_immediate_int32( machina::arch::int32_t value );
			
			/**
			  * @brief	Executes the 'and' instruction
			  */
			void exec_and_immediate_int64( machina::arch::int64_t value );
			
			/**
			  * @brief	Executes the 'and' instruction
			  */
			void exec_and_int8(  );
			
			/**
			  * @brief	Executes the 'and' instruction
			  */
			void exec_and_int16(  );
			
			/**
			  * @brief	Executes the 'and' instruction
			  */
			void exec_and_int32(  );
			
			/**
			  * @brief	Executes the 'and' instruction
			  */
			void exec_and_int64(  );
			
			
			
			/**
			  * @brief	Executes the 'or' instruction
			  */
			void exec_or_immediate_int8( machina::arch::int8_t value );
			
			/**
			  * @brief	Executes the 'or' instruction
			  */
			void exec_or_immediate_int16( machina::arch::int16_t value );
			
			/**
			  * @brief	Executes the 'or' instruction
			  */
			void exec_or_immediate_int32( machina::arch::int32_t value );
			
			/**
			  * @brief	Executes the 'or' instruction
			  */
			void exec_or_immediate_int64( machina::arch::int64_t value );
			
			/**
			  * @brief	Executes the 'or' instruction
			  */
			void exec_or_int8(  );
			
			/**
			  * @brief	Executes the 'or' instruction
			  */
			void exec_or_int16(  );
			
			/**
			  * @brief	Executes the 'or' instruction
			  */
			void exec_or_int32(  );
			
			/**
			  * @brief	Executes the 'or' instruction
			  */
			void exec_or_int64(  );
			
			
			
			/**
			  * @brief	Executes the 'xor' instruction
			  */
			void exec_xor_immediate_int8( machina::arch::int8_t value );
			
			/**
			  * @brief	Executes the 'xor' instruction
			  */
			void exec_xor_immediate_int16( machina::arch::int16_t value );
			
			/**
			  * @brief	Executes the 'xor' instruction
			  */
			void exec_xor_immediate_int32( machina::arch::int32_t value );
			
			/**
			  * @brief	Executes the 'xor' instruction
			  */
			void exec_xor_immediate_int64( machina::arch::int64_t value );
			
			/**
			  * @brief	Executes the 'xor' instruction
			  */
			void exec_xor_int8(  );
			
			/**
			  * @brief	Executes the 'xor' instruction
			  */
			void exec_xor_int16(  );
			
			/**
			  * @brief	Executes the 'xor' instruction
			  */
			void exec_xor_int32(  );
			
			/**
			  * @brief	Executes the 'xor' instruction
			  */
			void exec_xor_int64(  );
			
			
			
			/**
			  * @brief	Executes the 'not' instruction
			  */
			void exec_not_int8(  );
			
			/**
			  * @brief	Executes the 'not' instruction
			  */
			void exec_not_int16(  );
			
			/**
			  * @brief	Executes the 'not' instruction
			  */
			void exec_not_int32(  );
			
			/**
			  * @brief	Executes the 'not' instruction
			  */
			void exec_not_int64(  );
			
			
			
			/**
			  * @brief	Executes the 'cmp' instruction
			  */
			void exec_cmp_immediate_int8( machina::arch::int8_t value );
			
			/**
			  * @brief	Executes the 'cmp' instruction
			  */
			void exec_cmp_immediate_int16( machina::arch::int16_t value );
			
			/**
			  * @brief	Executes the 'cmp' instruction
			  */
			void exec_cmp_immediate_int32( machina::arch::int32_t value );
			
			/**
			  * @brief	Executes the 'cmp' instruction
			  */
			void exec_cmp_immediate_int64( machina::arch::int64_t value );
			
			/**
			  * @brief	Executes the 'cmp' instruction
			  */
			void exec_cmp_immediate_float( machina::arch::float_t value );
			
			/**
			  * @brief	Executes the 'cmp' instruction
			  */
			void exec_cmp_int8(  );
			
			/**
			  * @brief	Executes the 'cmp' instruction
			  */
			void exec_cmp_int16(  );
			
			/**
			  * @brief	Executes the 'cmp' instruction
			  */
			void exec_cmp_int32(  );
			
			/**
			  * @brief	Executes the 'cmp' instruction
			  */
			void exec_cmp_int64(  );
			
			/**
			  * @brief	Executes the 'cmp' instruction
			  */
			void exec_cmp_float(  );
			
			
			
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
			  * @brief	Executes the 'drop' instruction
			  */
			void exec_drop(  );
			
			
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
			  * 
			  * @param	address			The destionation address
			  */ 
			void exec_call_immediate( machina::arch::pointer_t address );
			
			/**
			  * @brief	Executes the 'call' instruction
			  */ 
			void exec_call(  );
				
				
			/**
			  * @brief	Executes the 'ret' instruction
			  */
			void exec_ret(  );
			
			
			/**
			  * @brief	Executes the 'out' instruction
			  * 
			  * @param	value			The value to write to the output
			  */ 
			void exec_out_immediate( machina::arch::int8_t value );
			
			/**
			  * @brief	Executes the 'out' instruction
			  */ 
			void exec_out(  );
			
			
			/**
			  * @brief	Executes the 'halt' instruction
			  */
			void exec_halt(  );
	};
}

#endif 
