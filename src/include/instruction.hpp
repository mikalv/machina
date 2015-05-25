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
	static const arch::size_t	instruction_byte 	= sizeof(arch::opcode_t);
		
	/**
	  * @brief	Size of a multibyte instruction
	  */ 
	static const arch::size_t	instruction_multibyte 	= sizeof(arch::opcode_t) + sizeof(arch::operand_t);
	
	/**
	  * @brief  Union describing an instruction
	  */ 
	union instruction 
	{
		/**
		  * @brief  The whole instruction
		  */
		arch::instruction_t     whole;
		
		/**
		  * @brief  The parts of the instruction
		  */ 
		arch::byte_t            parts[sizeof(arch::instruction_t)];
		
		/**
		* @brief  The constructor
		*/
		instruction( arch::instruction_t whole )
		{
			this->whole = whole;
		}
		
		/**
		  * @brief  Gets the opcode of the instruction
		  * 
		  * @return             The opcode
		  */ 
		inline arch::opcode_t opcode(  )
		{
			return (arch::opcode_t)this->parts[0];
		}
		
		/**
		  * @brief  Gets the operand of the instruction
		  *
		  * @return             The operand
		  */ 
		inline arch::long_t operand(  )
		{
			return (((arch::long_t*)this->parts)[0] & 0xFFFFFFFFFFFFFF00) >> 8;
		}
	};
}

#endif
