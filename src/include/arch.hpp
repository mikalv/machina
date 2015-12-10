#ifndef MACHINA_ARCH_HPP
#define MACHINA_ARCH_HPP

#include <cstdint>
#include <cstddef>

/**
  * @brief	Namespace of 'machina'
  */ 
namespace machina
{
	/**
	  * @brief	Namespace describing the 'machina' architecture
	  */ 
	namespace arch
	{
		/**
		  * @brief	Type used for sizes
		  */  
		typedef uint64_t                            		size_t;
		
		/**
		  * @brief	Type used for pointers
		  */  
		typedef uint64_t                            		pointer_t;
		
		/**
		  * @brief	Type used for bytes (8bit)
		  */ 
		typedef int8_t                              		byte_t;
		
		/**
		  * @brief	Type used for bytes (8bit)
		  */ 
		typedef int8_t                              		int8_t;
		
		/**
		  * @brief	Type used for short integers (16bit)
		  */ 
		typedef int16_t                             		int16_t;
		
		/**
		  * @brief	Type used for integers (32bit)
		  */ 
		typedef int32_t                             		int32_t;
		
		/**
		  * @brief	Type used for long integers (64bit)
		  */ 
		typedef int64_t                             		int64_t;
		
		/**
		  * @brief	Type used for floats
		  */
		typedef double						float_t;
		
		/**
		  * @brief	Type used for opcodes
		  */ 
		typedef uint8_t                             		opcode_t;
		
		/**
		  * @brief	Type used for operands
		  */ 
		typedef int64_t						operand_t;
		
		/**
		  * @brief	Type used for instructions
		  */ 
		typedef uint8_t                           		instruction_t[sizeof(opcode_t) + sizeof(operand_t)];
		
		/**
		  * @brief	The null pointer
		  */ 
		static const pointer_t					null = 0x0;
	}
}

#endif
