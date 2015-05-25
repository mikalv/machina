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
		#ifdef	MACHINA_ARCH_64
			/**
			  * @brief	Type used for sizes
			  */  
			typedef uint64_t                            		size_t;
			
			/**
			  * @brief	Type used for pointers
			  */  
			typedef uint64_t                            		pointer_t;
			
			/**
			  * @brief	Type used for instructions
			  */ 
			typedef uint64_t                           		instruction_t;
			
			/**
			  * @brief	Type used for bytes
			  */ 
			typedef int8_t                              		byte_t;
			
			/**
			  * @brief	Type used for integers
			  */ 
			typedef int16_t                             		short_t;
			
			/**
			  * @brief	Type used for integers
			  */ 
			typedef int32_t                             		int_t;
			
			/**
			  * @brief	Type used for long integers
			  */ 
			typedef int64_t                             		long_t;
			
			/**
			  * @brief	Type used for opcodes
			  */ 
			typedef uint8_t                             		opcode_t;
			
			/**
			  * @brief	Type used for operands
			  */ 
			typedef int8_t						operand_t[sizeof(instruction_t) - 1];
		
		
		#elif MACHINA_ARCH_32
			/**
			  * @brief	Type used for sizes
			  */  
			typedef uint32_t                            		size_t;
			
			/**
			  * @brief	Type used for pointers
			  */  
			typedef uint32_t                            		pointer_t;
			
			/**
			  * @brief	Type used for instructions
			  */ 
			typedef uint32_t                           		instruction_t;
			
			/**
			  * @brief	Type used for bytes
			  */ 
			typedef int8_t                              		byte_t;
			
			/**
			  * @brief	Type used for integers
			  */ 
			typedef int16_t                             		short_t;
			
			/**
			  * @brief	Type used for integers
			  */ 
			typedef int32_t                             		int_t;
			
			/**
			  * @brief	Type used for long integers
			  */ 
			typedef int32_t                             		long_t;
			
			/**
			  * @brief	Type used for opcodes
			  */ 
			typedef uint8_t                             		opcode_t;
			
			/**
			  * @brief	Type used for operands
			  */ 
			typedef int8_t						operand_t[sizeof(instruction_t) - 1];
		
		#else
			#error "Error unknown architecture!"
		#endif
			
			/**
			  * @brief	The null pointer
			  */ 
			static const pointer_t					null = 0x0;
	}
}

#endif
