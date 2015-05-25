#ifndef MACHINA_OPCODE_HPP
#define MACHINA_OPCODE_HPP

#include "arch.hpp"

/**
  * @brief	Namespace of 'machina'
  */ 
namespace machina
{
	/**
	  * @brief	The opcodes
	  */ 
	enum opcodes
	{
		/**
		  * @brief	Opcode of the 'nop' instruction
		  */ 
		opcode_nop			= 0x00,

		
		
		/**
		  * @brief	Opcode of the 'load immediate byte' instruction
		  */ 
		opcode_load_immediate_byte	= 0x01,

		/**
		  * @brief	Opcode of the 'load immediate short' instruction
		  */ 
		opcode_load_immediate_short	= 0x02,

		/**
		  * @brief	Opcode of the 'load immediate int' instruction
		  */ 
		opcode_load_immediate_int	= 0x03,

		/**
		  * @brief	Opcode of the 'load immediate long' instruction
		  */ 
		opcode_load_immediate_long	= 0x04,

		/**
		  * @brief	Opcode of the 'load byte' instruction
		  */ 
		opcode_load_byte		= 0x05,

		/**
		  * @brief	Opcode of the 'load short' instruction
		  */ 
		opcode_load_short		= 0x06,

		/**
		  * @brief	Opcode of the 'load int' instruction
		  */ 
		opcode_load_int			= 0x07,

		/**
		  * @brief	Opcode of the 'load long' instruction
		  */ 
		opcode_load_long		= 0x08,
		
		
		/**
		  * @brief	Opcode of the 'store immediate byte' instruction
		  */ 
		opcode_store_immediate_byte	= 0x09,

		/**
		  * @brief	Opcode of the 'store immediate short' instruction
		  */ 
		opcode_store_immediate_short	= 0x0A,

		/**
		  * @brief	Opcode of the 'store immediate int' instruction
		  */ 
		opcode_store_immediate_int	= 0x0B,

		/**
		  * @brief	Opcode of the 'store immediate long' instruction
		  */ 
		opcode_store_immediate_long	= 0x0C,

		/**
		  * @brief	Opcode of the 'store byte' instruction
		  */ 
		opcode_store_byte		= 0x0D,

		/**
		  * @brief	Opcode of the 'śtore short' instruction
		  */ 
		opcode_store_short		= 0x0E,

		/**
		  * @brief	Opcode of the 'store int' instruction
		  */ 
		opcode_store_int		= 0x0F,

		/**
		  * @brief	Opcode of the 'store long' instruction
		  */ 
		opcode_store_long		= 0x10,

		
		
		/**
		  * @brief	Opcode of the 'jmp' instruction
		  */ 
		opcode_jmp			= 0x11,

		/**
		  * @brief	Opcode of the 'jmpz' instruction
		  */ 
		opcode_jmpz			= 0x12,
		
		/**
		  * @brief	Opcode of the 'jmpnz' instruction
		  */ 
		opcode_jmpnz			= 0x13,
		
		/**
		  * @brief	Opcode of the 'jmpgz' instruction
		  */ 
		opcode_jmpgz			= 0x14,
		
		/**
		  * @brief	Opcode of the 'jmplz' instruction
		  */ 
		opcode_jmplz			= 0x15,
		
		/**
		  * @brief	Opcode of the 'jmpeq' instruction
		  */ 
		opcode_jmpeq			= 0x16,
		
		/**
		  * @brief	Opcode of the 'jmpneq' instruction
		  */ 
		opcode_jmpneq			= 0x17,
		
		/**
		  * @brief	Opcode of the 'call' instruction
		  */ 
		opcode_call			= 0x18,

		/**
		  * @brief	Opcode of the 'call with immediate address' instruction
		  */ 
		opcode_call_immediate		= 0x19,

		/**
		  * @brief	Opcode of the 'return' instruction
		  */ 
		opcode_ret			= 0x1A,

		
		
		/**
		  * @brief	Opcode of the 'add' instruction
		  */ 
		opcode_add_byte			= 0x1B,
		
		/**
		  * @brief	Opcode of the 'add' instruction
		  */ 
		opcode_add_short		= 0x1C,
		
		/**
		  * @brief	Opcode of the 'add' instruction
		  */ 
		opcode_add_int			= 0x1D,
		
		/**
		  * @brief	Opcode of the 'add' instruction
		  */ 
		opcode_add_long			= 0x1E,

		/**
		  * @brief	Opcode of the 'sub' instruction
		  */ 
		opcode_sub_byte			= 0x1F,
		
		/**
		  * @brief	Opcode of the 'sub' instruction
		  */ 
		opcode_sub_short		= 0x20,
		
		/**
		  * @brief	Opcode of the 'sub' instruction
		  */ 
		opcode_sub_int			= 0x21,
		
		/**
		  * @brief	Opcode of the 'sub' instruction
		  */ 
		opcode_sub_long			= 0x22,

		/**
		  * @brief	Opcode of the 'mul' instruction
		  */ 
		opcode_mul_byte			= 0x23,
		
		/**
		  * @brief	Opcode of the 'mul' instruction
		  */ 
		opcode_mul_short		= 0x24,
		
		/**
		  * @brief	Opcode of the 'mul' instruction
		  */ 
		opcode_mul_int			= 0x25,
		
		/**
		  * @brief	Opcode of the 'mul' instruction
		  */ 
		opcode_mul_long			= 0x26,
		
		/**
		  * @brief	Opcode of the 'div' instruction
		  */ 
		opcode_div_byte			= 0x27,
		
		/**
		  * @brief	Opcode of the 'div' instruction
		  */ 
		opcode_div_short		= 0x28,
		
		/**
		  * @brief	Opcode of the 'div' instruction
		  */ 
		opcode_div_int			= 0x29,
		
		/**
		  * @brief	Opcode of the 'div' instruction
		  */ 
		opcode_div_long			= 0x2A,

		/**
		  * @brief	Opcode of the 'modulo' instruction
		  */ 
		opcode_mod_byte			= 0x2B,
		
		/**
		  * @brief	Opcode of the 'modulo' instruction
		  */ 
		opcode_mod_short		= 0x2C,
		
		/**
		  * @brief	Opcode of the 'modulo' instruction
		  */ 
		opcode_mod_int			= 0x2D,
		
		/**
		  * @brief	Opcode of the 'modulo' instruction
		  */ 
		opcode_mod_long			= 0x2E,
		
		/**
		  * @brief	Opcode of the 'inc' instruction
		  */ 
		opcode_inc_byte			= 0x2F,
		
		/**
		  * @brief	Opcode of the 'inc' instruction
		  */ 
		opcode_inc_short		= 0x30,
		
		/**
		  * @brief	Opcode of the 'inc' instruction
		  */ 
		opcode_inc_int			= 0x31,
		
		/**
		  * @brief	Opcode of the 'inc' instruction
		  */ 
		opcode_inc_long			= 0x32,
		
		/**
		  * @brief	Opcode of the 'dec' instruction
		  */ 
		opcode_dec_byte			= 0x33,
		
		/**
		  * @brief	Opcode of the 'dec' instruction
		  */ 
		opcode_dec_short		= 0x34,
		
		/**
		  * @brief	Opcode of the 'dec' instruction
		  */ 
		opcode_dec_int			= 0x35,
		
		/**
		  * @brief	Opcode of the 'dec' instruction
		  */ 
		opcode_dec_long			= 0x36,

		/**
		  * @brief	Opcode of the 'and' instruction
		  */ 
		opcode_and_byte			= 0x37,
		
		/**
		  * @brief	Opcode of the 'and' instruction
		  */ 
		opcode_and_short		= 0x38,
		
		/**
		  * @brief	Opcode of the 'and' instruction
		  */ 
		opcode_and_int			= 0x39,
		
		/**
		  * @brief	Opcode of the 'and' instruction
		  */ 
		opcode_and_long			= 0x3A,

		/**
		  * @brief	Opcode of the 'or' instruction
		  */ 
		opcode_or_byte			= 0x3B,
		
		/**
		  * @brief	Opcode of the 'or' instruction
		  */ 
		opcode_or_short			= 0x3C,
		
		/**
		  * @brief	Opcode of the 'or' instruction
		  */ 
		opcode_or_int			= 0x3D,
		
		/**
		  * @brief	Opcode of the 'or' instruction
		  */ 
		opcode_or_long			= 0x3E,

		/**
		  * @brief	Opcode of the 'xor' instruction
		  */ 
		opcode_xor_byte			= 0x3F,
		
		/**
		  * @brief	Opcode of the 'xor' instruction
		  */ 
		opcode_xor_short		= 0x40,
		
		/**
		  * @brief	Opcode of the 'xor' instruction
		  */ 
		opcode_xor_int			= 0x41,
		
		/**
		  * @brief	Opcode of the 'xor' instruction
		  */ 
		opcode_xor_long			= 0x42,

		/**
		  * @brief	Opcode of the 'not' instruction
		  */ 
		opcode_not_byte			= 0x43,
		
		/**
		  * @brief	Opcode of the 'not' instruction
		  */ 
		opcode_not_short		= 0x44,
		
		/**
		  * @brief	Opcode of the 'not' instruction
		  */ 
		opcode_not_int			= 0x45,
		
		/**
		  * @brief	Opcode of the 'not' instruction
		  */ 
		opcode_not_long			= 0x46,

		
		
		/**
		  * @brief	Opcode of the 'duplictae' instruction
		  */ 
		opcode_dup			= 0x60,

		/**
		  * @brief	Opcode of the 'swap' instruction
		  */ 
		opcode_swap			= 0x61,
		
		/**
		  * @brief	Opcode of the 'rol' instruction
		  */ 
		opcode_rol			= 0x62,
		
		/**
		  * @brief	Opcode of the 'roln' instruction
		  */
		opcode_roln			= 0x63,
		
		
		
		/**
		  * @brief	Opcode of the 'frame' instruction
		  */
		opcode_frame			= 0x70,
		
		/**
		  * @brief	Opcode of the 'obtain' instruction
		  */
		opcode_obtain			= 0x71,
		
		/**
		  * @brief	Opcode of the 'place' instruction
		  */
		opcode_place			= 0x72,
		
		/**
		  * @brief	Opcode of the 'cleanup' instruction
		  */
		opcode_cleanup			= 0x73,
		
		
		
		/**
		  * @brief	Opcode of the 'halt' instruction
		  */ 
		opcode_halt			= 0xFF,
	};
}

#endif
