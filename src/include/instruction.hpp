#ifndef MACHINA_INSTRUCTION_HPP
#define MACHINA_INSTRUCTION_HPP

#include "arch.hpp"

/**
  * @brief  Namespace of 'machina'
  */ 
namespace machina
{
	/**
	  * @brief	Size of a normal, single byte instruction
	  */ 
	static const machina::arch::size_t	instruction_size_byte 	   = sizeof(machina::arch::opcode_t);
	
	/**
	  * @brief	Size of a multibyte instruction (with immediate operands)
	  */ 
	static const machina::arch::size_t	instruction_size_multibyte = sizeof(machina::arch::opcode_t) + sizeof(machina::arch::operand_t);
	
	/**
	  * @brief  Union describing an instruction
	  */ 
	union instruction 
	{
		/**
		  * @brief  The whole instruction
		  */
		machina::arch::instruction_t     whole;
		
		/**
		  * @brief  The parts of the instruction
		  */ 
		machina::arch::byte_t            parts[sizeof(machina::arch::instruction_t)];
		
		/**
		  * @brief  The constructor
		  */
		instruction( machina::arch::instruction_t whole )
		{
			memcpy(this->whole, whole, sizeof(machina::arch::instruction_t));
		}
		
		/**
		  * @brief  Gets the opcode of the instruction
		  * 
		  * @return             The opcode
		  */ 
		inline machina::arch::opcode_t opcode(  )
		{
			return (machina::arch::opcode_t)this->parts[0];
		}
		
		/**
		  * @brief  Gets the operand of the instruction
		  *
		  * @return             The operand
		  */ 
		inline machina::arch::int8_t operand_as_int8(  )
		{
			return ((machina::arch::int8_t*)(this->parts + sizeof(machina::arch::byte_t)))[0];
		}
		
		/**
		  * @brief  Gets the operand of the instruction
		  *
		  * @return             The operand
		  */ 
		inline machina::arch::int16_t operand_as_int16(  )
		{
			return ((machina::arch::int16_t*)(this->parts + sizeof(machina::arch::byte_t)))[0];
		}
		
		/**
		  * @brief  Gets the operand of the instruction
		  *
		  * @return             The operand
		  */ 
		inline machina::arch::int32_t operand_as_int32(  )
		{
			return ((machina::arch::int32_t*)(this->parts + sizeof(machina::arch::byte_t)))[0];
		}
		
		/**
		  * @brief  Gets the operand of the instruction
		  *
		  * @return             The operand
		  */ 
		inline machina::arch::int64_t operand_as_int64(  )
		{
			return ((machina::arch::int64_t*)(this->parts + sizeof(machina::arch::byte_t)))[0];
		}
		
		/**
		  * @brief  Gets the operand of the instruction
		  *
		  * @return             The operand
		  */ 
		inline machina::arch::pointer_t operand_as_addr(  )
		{
			return ((machina::arch::pointer_t*)(this->parts + sizeof(machina::arch::byte_t)))[0];
		}
		
		/**
		  * @brief  Gets the operand of the instruction
		  *
		  * @return             The operand
		  */ 
		inline machina::arch::float_t operand_as_float(  )
		{
			return ((machina::arch::float_t*)(this->parts + sizeof(machina::arch::byte_t)))[0];
		}
	};
}

#endif
