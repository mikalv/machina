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
		  * @brief	Opcode of the 'load immediate int8' instruction
		  */ 
		opcode_load_immediate_int8	= 0x01,

		/**
		  * @brief	Opcode of the 'load immediate int16' instruction
		  */ 
		opcode_load_immediate_int16	= 0x02,

		/**
		  * @brief	Opcode of the 'load immediate int32 instruction
		  */ 
		opcode_load_immediate_int32	= 0x03,

		/**
		  * @brief	Opcode of the 'load immediate int64' instruction
		  */ 
		opcode_load_immediate_int64	= 0x04,
		
		/**
		  * @brief	Opcode of the 'load immediate float' instruction
		  */ 
		opcode_load_immediate_float	= 0x05,

		/**
		  * @brief	Opcode of the 'load int8' instruction
		  */ 
		opcode_load_int8		= 0x06,

		/**
		  * @brief	Opcode of the 'load int16' instruction
		  */ 
		opcode_load_int16		= 0x07,

		/**
		  * @brief	Opcode of the 'load int32 instruction
		  */ 
		opcode_load_int32		= 0x08,

		/**
		  * @brief	Opcode of the 'load int64' instruction
		  */ 
		opcode_load_int64		= 0x09,
		
		/**
		  * @brief	Opcode of the 'load float' instruction
		  */ 
		opcode_load_float		= 0x0A,
		
		
		
		/**
		  * @brief	Opcode of the 'convert float to int64' instruction
		  */ 
		opcode_convert_float_to_int64	= 0x0B,
		
		/**
		  * @brief	Opcode of the 'convert int64 to flot' instruction
		  */
		opcode_convert_int64_to_float	= 0x0C,
		
		/**
		  * @brief	Opcode of the 'convert int64 to int32' instruction
		  */
		opcode_convert_int64_to_int32	= 0x0D,
		
		/**
		  * @brief	Opcode of the 'convert int32 to int16' instruction
		  */
		opcode_convert_int32_to_int16	= 0x0E,
		
		/**
		  * @brief	Opcode of the 'convert int16 to int8' instruction
		  */
		opcode_convert_int16_to_int8	= 0x0F,
		
		
		
		/**
		  * @brief	Opcode of the 'store immediate int8' instruction
		  */ 
		opcode_store_immediate_int8	= 0x10,

		/**
		  * @brief	Opcode of the 'store immediate int16' instruction
		  */ 
		opcode_store_immediate_int16	= 0x11,

		/**
		  * @brief	Opcode of the 'store immediate int32 instruction
		  */ 
		opcode_store_immediate_int32	= 0x12,

		/**
		  * @brief	Opcode of the 'store immediate int64' instruction
		  */ 
		opcode_store_immediate_int64	= 0x13,
		
		/**
		  * @brief	Opcode of the 'store immediate float' instruction
		  */ 
		opcode_store_immediate_float	= 0x14,

		/**
		  * @brief	Opcode of the 'store int8' instruction
		  */ 
		opcode_store_int8		= 0x15,

		/**
		  * @brief	Opcode of the 'store int16' instruction
		  */ 
		opcode_store_int16		= 0x16,

		/**
		  * @brief	Opcode of the 'store int32 instruction
		  */ 
		opcode_store_int32		= 0x17,

		/**
		  * @brief	Opcode of the 'store int64' instruction
		  */ 
		opcode_store_int64		= 0x18,
		
		/**
		  * @brief	Opcode of the 'store float' instruction
		  */ 
		opcode_store_float		= 0x19,

		
		
		/**
		  * @brief	Opcode of the 'convert int8 to int16' instruction
		  */
		opcode_convert_int8_to_int16	= 0x1A,
		
		/**
		  * @brief	Opcode of the 'convert int16 to int32' instruction
		  */
		opcode_convert_int16_to_int32	= 0x1B,
		
		/**
		  * @brief	Opcode of the 'convert int32 to int64' instruction
		  */
		opcode_convert_int32_to_int64	= 0x1C,
		
		
		
		/**
		  * @brief	Opcode of the 'alloc memory' instruction
		  */
		opcode_alloc_immediate		= 0x1D,
		
		/**
		  * @brief	Opcode of the 'alloc memory' instruction
		  */
		opcode_alloc			= 0x1E,
		
		/**
		  * @brief	Opcode of the 'free memory' instruction
		  */
		opcode_free			= 0x1F,
		
		
		
		/**
		  * @brief	Opcode of the 'jmp' instruction
		  */ 
		opcode_jmp			= 0x20,

		/**
		  * @brief	Opcode of the 'jmpz' instruction
		  */ 
		opcode_jmpz			= 0x21,
		
		/**
		  * @brief	Opcode of the 'jmpnz' instruction
		  */ 
		opcode_jmpnz			= 0x22,
		
		/**
		  * @brief	Opcode of the 'jmpgz' instruction
		  */ 
		opcode_jmpgz			= 0x23,
		
		/**
		  * @brief	Opcode of the 'jmplz' instruction
		  */ 
		opcode_jmplz			= 0x24,
		
		/**
		  * @brief	Opcode of the 'jmpeq' instruction
		  */ 
		opcode_jmpeq			= 0x25,
		
		/**
		  * @brief	Opcode of the 'jmpneq' instruction
		  */ 
		opcode_jmpneq			= 0x26,
		
		/**
		  * @brief	Opcode of the 'call with immediate address' instruction
		  */ 
		opcode_call_immediate		= 0x27,
		
		/**
		  * @brief	Opcode of the 'call' instruction
		  */ 
		opcode_call			= 0x28,

		/**
		  * @brief	Opcode of the 'return' instruction
		  */ 
		opcode_ret			= 0x29,
		
		/**
		  * @brief	Opcode of the 'halt' instruction
		  */ 
		opcode_halt			= 0x2A,

		
		
		/**
		  * @brief	Opcode of the 'add immediate' instruction
		  */ 
		opcode_add_immediate_int8	= 0x30,
		
		/**
		  * @brief	Opcode of the 'add immediate' instruction
		  */ 
		opcode_add_immediate_int16	= 0x31,
		
		/**
		  * @brief	Opcode of the 'add immediate' instruction
		  */ 
		opcode_add_immediate_int32	= 0x32,
		
		/**
		  * @brief	Opcode of the 'add immediate' instruction
		  */ 
		opcode_add_immediate_int64	= 0x33,
		
		/**
		  * @brief	Opcode of the 'add immediate' instruction
		  */ 
		opcode_add_immediate_float	= 0x34,
		
		/**
		  * @brief	Opcode of the 'add' instruction
		  */ 
		opcode_add_int8			= 0x35,
		
		/**
		  * @brief	Opcode of the 'add' instruction
		  */ 
		opcode_add_int16		= 0x36,
		
		/**
		  * @brief	Opcode of the 'add' instruction
		  */ 
		opcode_add_int32		= 0x37,
		
		/**
		  * @brief	Opcode of the 'add' instruction
		  */ 
		opcode_add_int64		= 0x38,
		
		/**
		  * @brief	Opcode of the 'add' instruction
		  */ 
		opcode_add_float		= 0x39,
		
		
		
		/**
		  * @brief	Opcode of the 'sub immediate' instruction
		  */ 
		opcode_sub_immediate_int8	= 0x3A,
		
		/**
		  * @brief	Opcode of the 'sub immediate' instruction
		  */ 
		opcode_sub_immediate_int16	= 0x3B,
		
		/**
		  * @brief	Opcode of the 'sub immediate' instruction
		  */ 
		opcode_sub_immediate_int32	= 0x3C,
		
		/**
		  * @brief	Opcode of the 'sub immediate' instruction
		  */ 
		opcode_sub_immediate_int64	= 0x3D,
		
		/**
		  * @brief	Opcode of the 'sub immediate' instruction
		  */ 
		opcode_sub_immediate_float	= 0x3E,
		
		/**
		  * @brief	Opcode of the 'sub' instruction
		  */ 
		opcode_sub_int8			= 0x3F,
		
		/**
		  * @brief	Opcode of the 'sub' instruction
		  */ 
		opcode_sub_int16		= 0x40,
		
		/**
		  * @brief	Opcode of the 'sub' instruction
		  */ 
		opcode_sub_int32		= 0x41,
		
		/**
		  * @brief	Opcode of the 'sub' instruction
		  */ 
		opcode_sub_int64		= 0x42,
		
		/**
		  * @brief	Opcode of the 'sub' instruction
		  */ 
		opcode_sub_float		= 0x43,
		
		
		
		/**
		  * @brief	Opcode of the 'mul immediate' instruction
		  */ 
		opcode_mul_immediate_int8	= 0x44,
		
		/**
		  * @brief	Opcode of the 'mul immediate' instruction
		  */ 
		opcode_mul_immediate_int16	= 0x45,
		
		/**
		  * @brief	Opcode of the 'mul immediate' instruction
		  */ 
		opcode_mul_immediate_int32	= 0x46,
		
		/**
		  * @brief	Opcode of the 'mul immediate' instruction
		  */ 
		opcode_mul_immediate_int64	= 0x47,
		
		/**
		  * @brief	Opcode of the 'mul immediate' instruction
		  */ 
		opcode_mul_immediate_float	= 0x48,
		
		/**
		  * @brief	Opcode of the 'mul' instruction
		  */ 
		opcode_mul_int8			= 0x49,
		
		/**
		  * @brief	Opcode of the 'mul' instruction
		  */ 
		opcode_mul_int16		= 0x4A,
		
		/**
		  * @brief	Opcode of the 'mul' instruction
		  */ 
		opcode_mul_int32		= 0x4B,
		
		/**
		  * @brief	Opcode of the 'mul' instruction
		  */ 
		opcode_mul_int64		= 0x4C,
		
		/**
		  * @brief	Opcode of the 'mul' instruction
		  */ 
		opcode_mul_float		= 0x4D,
		
		
		
		/**
		  * @brief	Opcode of the 'div immediate' instruction
		  */ 
		opcode_div_immediate_int8	= 0x4E,
		
		/**
		  * @brief	Opcode of the 'div immediate' instruction
		  */ 
		opcode_div_immediate_int16	= 0x4F,
		
		/**
		  * @brief	Opcode of the 'div immediate' instruction
		  */ 
		opcode_div_immediate_int32	= 0x50,
		
		/**
		  * @brief	Opcode of the 'div immediate' instruction
		  */ 
		opcode_div_immediate_int64	= 0x51,
		
		/**
		  * @brief	Opcode of the 'div immediate' instruction
		  */ 
		opcode_div_immediate_float	= 0x52,
		
		/**
		  * @brief	Opcode of the 'div' instruction
		  */ 
		opcode_div_int8			= 0x53,
		
		/**
		  * @brief	Opcode of the 'div' instruction
		  */ 
		opcode_div_int16		= 0x54,
		
		/**
		  * @brief	Opcode of the 'div' instruction
		  */ 
		opcode_div_int32		= 0x55,
		
		/**
		  * @brief	Opcode of the 'div' instruction
		  */ 
		opcode_div_int64		= 0x56,
		
		/**
		  * @brief	Opcode of the 'div' instruction
		  */ 
		opcode_div_float		= 0x57,
		
		
		
		/**
		  * @brief	Opcode of the 'mod immediate' instruction
		  */ 
		opcode_mod_immediate_int8	= 0x58,
		
		/**
		  * @brief	Opcode of the 'mod immediate' instruction
		  */ 
		opcode_mod_immediate_int16	= 0x59,
		
		/**
		  * @brief	Opcode of the 'mod immediate' instruction
		  */ 
		opcode_mod_immediate_int32	= 0x5A,
		
		/**
		  * @brief	Opcode of the 'mod immediate' instruction
		  */ 
		opcode_mod_immediate_int64	= 0x5B,
		
		/**
		  * @brief	Opcode of the 'mod' instruction
		  */ 
		opcode_mod_int8			= 0x5C,
		
		/**
		  * @brief	Opcode of the 'mod' instruction
		  */ 
		opcode_mod_int16		= 0x5D,
		
		/**
		  * @brief	Opcode of the 'mod' instruction
		  */ 
		opcode_mod_int32		= 0x5E,
		
		/**
		  * @brief	Opcode of the 'mod' instruction
		  */ 
		opcode_mod_int64		= 0x5F,
		
		
		
		/**
		  * @brief	Opcode of the 'and immediate' instruction
		  */ 
		opcode_and_immediate_int8	= 0x60,
		
		/**
		  * @brief	Opcode of the 'and immediate' instruction
		  */ 
		opcode_and_immediate_int16	= 0x61,
		
		/**
		  * @brief	Opcode of the 'and immediate' instruction
		  */ 
		opcode_and_immediate_int32	= 0x62,
		
		/**
		  * @brief	Opcode of the 'and immediate' instruction
		  */ 
		opcode_and_immediate_int64	= 0x63,
		
		/**
		  * @brief	Opcode of the 'and' instruction
		  */ 
		opcode_and_int8			= 0x64,
		
		/**
		  * @brief	Opcode of the 'and' instruction
		  */ 
		opcode_and_int16		= 0x65,
		
		/**
		  * @brief	Opcode of the 'and' instruction
		  */ 
		opcode_and_int32		= 0x66,
		
		/**
		  * @brief	Opcode of the 'and' instruction
		  */ 
		opcode_and_int64		= 0x67,
		
		
		
		/**
		  * @brief	Opcode of the 'or immediate' instruction
		  */ 
		opcode_or_immediate_int8	= 0x68,
		
		/**
		  * @brief	Opcode of the 'or immediate' instruction
		  */ 
		opcode_or_immediate_int16	= 0x69,
		
		/**
		  * @brief	Opcode of the 'or immediate' instruction
		  */ 
		opcode_or_immediate_int32	= 0x6A,
		
		/**
		  * @brief	Opcode of the 'or immediate' instruction
		  */ 
		opcode_or_immediate_int64	= 0x6B,
		
		/**
		  * @brief	Opcode of the 'or' instruction
		  */ 
		opcode_or_int8			= 0x6C,
		
		/**
		  * @brief	Opcode of the 'or' instruction
		  */ 
		opcode_or_int16			= 0x6D,
		
		/**
		  * @brief	Opcode of the 'or' instruction
		  */ 
		opcode_or_int32			= 0x6E,

		/**
		  * @brief	Opcode of the 'or' instruction
		  */ 
		opcode_or_int64			= 0x6F,
		
		
		
		/**
		  * @brief	Opcode of the 'xor immediate' instruction
		  */ 
		opcode_xor_immediate_int8	= 0x70,
		
		/**
		  * @brief	Opcode of the 'xor immediate' instruction
		  */ 
		opcode_xor_immediate_int16	= 0x71,
		
		/**
		  * @brief	Opcode of the 'xor immediate' instruction
		  */ 
		opcode_xor_immediate_int32	= 0x72,
		
		/**
		  * @brief	Opcode of the 'xor immediate' instruction
		  */ 
		opcode_xor_immediate_int64	= 0x73,
		
		/**
		  * @brief	Opcode of the 'xor' instruction
		  */ 
		opcode_xor_int8			= 0x74,
		
		/**
		  * @brief	Opcode of the 'xor' instruction
		  */ 
		opcode_xor_int16		= 0x75,
		
		/**
		  * @brief	Opcode of the 'xor' instruction
		  */ 
		opcode_xor_int32		= 0x76,
		
		/**
		  * @brief	Opcode of the 'xor' instruction
		  */ 
		opcode_xor_int64		= 0x77,
		
		
		
		/**
		  * @brief	Opcode of the 'not' instruction
		  */ 
		opcode_not_int8			= 0x78,
		
		/**
		  * @brief	Opcode of the 'not' instruction
		  */ 
		opcode_not_int16		= 0x79,
		
		/**
		  * @brief	Opcode of the 'not' instruction
		  */ 
		opcode_not_int32		= 0x7A,
		
		/**
		  * @brief	Opcode of the 'not' instruction
		  */ 
		opcode_not_int64		= 0x7B,
		
		
		
		/**
		  * @brief	Opcode of the 'cmp immediate' instruction
		  */ 
		opcode_cmp_immediate_int8	= 0x7C,
		
		/**
		  * @brief	Opcode of the 'cmp immediate' instruction
		  */ 
		opcode_cmp_immediate_int16	= 0x7D,
		
		/**
		  * @brief	Opcode of the 'cmp immediate' instruction
		  */ 
		opcode_cmp_immediate_int32	= 0x7E,
		
		/**
		  * @brief	Opcode of the 'cmp immediate' instruction
		  */ 
		opcode_cmp_immediate_int64	= 0x7F,
		
		/**
		  * @brief	Opcode of the 'cmp immediate' instruction
		  */ 
		opcode_cmp_immediate_float	= 0x80,
		
		/**
		  * @brief	Opcode of the 'cmp' instruction
		  */ 
		opcode_cmp_int8			= 0x81,
		
		/**
		  * @brief	Opcode of the 'cmp' instruction
		  */ 
		opcode_cmp_int16		= 0x82,
		
		/**
		  * @brief	Opcode of the 'cmp' instruction
		  */ 
		opcode_cmp_int32		= 0x83,
		
		/**
		  * @brief	Opcode of the 'cmp' instruction
		  */ 
		opcode_cmp_int64		= 0x84,
		
		/**
		  * @brief	Opcode of the 'cmp' instruction
		  */ 
		opcode_cmp_float		= 0x85,
		
		
		
		/**
		  * @brief	Opcode of the 'inc' instruction
		  */ 
		opcode_inc_int8			= 0x86,
		
		/**
		  * @brief	Opcode of the 'inc' instruction
		  */ 
		opcode_inc_int16		= 0x87,
		
		/**
		  * @brief	Opcode of the 'inc' instruction
		  */ 
		opcode_inc_int32		= 0x88,
		
		/**
		  * @brief	Opcode of the 'inc' instruction
		  */ 
		opcode_inc_int64		= 0x89,
		
		/**
		  * @brief	Opcode of the 'inc' instruction
		  */ 
		opcode_inc_float		= 0x8A,
		
		/**
		  * @brief	Opcode of the 'dec' instruction
		  */ 
		opcode_dec_int8			= 0x8B,
		
		/**
		  * @brief	Opcode of the 'dec' instruction
		  */ 
		opcode_dec_int16		= 0x8C,
		
		/**
		  * @brief	Opcode of the 'dec' instruction
		  */ 
		opcode_dec_int32		= 0x8D,
		
		/**
		  * @brief	Opcode of the 'dec' instruction
		  */ 
		opcode_dec_int64		= 0x8E,
		
		/**
		  * @brief	Opcode of the 'dec' instruction
		  */ 
		opcode_dec_float		= 0x8F,

		
		
		/**
		  * @brief	Opcode of the 'duplictae' instruction
		  */ 
		opcode_dup			= 0x90,

		/**
		  * @brief	Opcode of the 'swap' instruction
		  */ 
		opcode_swap			= 0x91,
		
		/**
		  * @brief	Opcode of the 'rol' instruction
		  */ 
		opcode_rol			= 0x92,
		
		/**
		  * @brief	Opcode of the 'roln' instruction
		  */
		opcode_roln			= 0x93,
		
		/**
		  * @brief	Opcode of the 'drop' instruction
		  */
		opcode_drop			= 0x94,
		
		
		
		/**
		  * @brief	Opcode of the 'frame' instruction
		  */
		opcode_frame			= 0xA0,
		
		/**
		  * @brief	Opcode of the 'obtain' instruction
		  */
		opcode_obtain			= 0xA1,
		
		/**
		  * @brief	Opcode of the 'place' instruction
		  */
		opcode_place			= 0xA2,
		
		/**
		  * @brief	Opcode of the 'cleanup' instruction
		  */
		opcode_cleanup			= 0xA3,
		
		
		
		/**
		  * @brief	Opcode of the 'out immediate' instruction
		  */
		opcode_out_immediate		= 0xB0,
		
		/**
		  * @brief	Opcode of the 'out' instruction
		  */
		opcode_out			= 0xB1,
	};
}

#endif
