#include "include/machina.hpp"
#include "include/opcode.hpp"
#include "include/arch.hpp"

#include <iostream>

/**
  * Program 'square'
  */ 
static machina::arch::opcode_t	square[] =
{
		/**
		  * Variable n (type long)
		  */
/** 0x0000 */	0x0A,                                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		
		/**
		  * Function 'square'
		  */
/** 0x0008 */	machina::opcode_load_long,
/** 0x0009 */	machina::opcode_dup,
/** 0x000A */	machina::opcode_mul_long,
/** 0x000B */	machina::opcode_ret,
		
		/**
		  * Funcion 'start' - program entry
		  */
/** 0x000C */	machina::opcode_load_immediate_long,  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/** 0x0014 */	machina::opcode_call_immediate,       0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/** 0x001C */	machina::opcode_store_immediate_long, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

/** 0x0024 */	machina::opcode_load_immediate_long,  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/** 0x002C */	machina::opcode_load_long,
/** 0x002D */	machina::opcode_load_immediate_long,  0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00,
/** 0x0035 */	machina::opcode_sub_long,
/** 0x0036 */   machina::opcode_jmplz,                0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

/** 0x003E */	machina::opcode_load_immediate_long,  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/** 0x0046 */	machina::opcode_load_long,

/** 0x0047 */	machina::opcode_halt,
};

static machina::arch::opcode_t	hello[] =
{
		/**
		  * Variable s (type string)
		  */
/** 0x0000 */	0x48,                                 0x65, 0x6C, 0x6C, 0x6F, 0x20, 0x57, 0x6F,
/** 0x0008 */	0x72,                                 0x6C, 0x64, 0x21, 0x0A, 0x00, 

/** 0x000E */	machina::opcode_load_immediate_long,  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/** 0x0016 */	machina::opcode_dup,
/** 0x0017 */	machina::opcode_load_byte,
/** 0x0018 */	machina::opcode_dup,
/** 0x0019 */	machina::opcode_jmpz,                 0x2B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/** 0x0021 */	machina::opcode_out,
/** 0x0022 */	machina::opcode_inc_long,
/** 0x0023 */	machina::opcode_jmp,                  0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/** 0x002B */	machina::opcode_halt,
};

int main(  )
{
	/**
	  * Instance of 'machina' virtual machine 
	  */ 
	machina::virtual_machine vm;
	
	std::cout << "Loading demo program 'hello' (" << std::dec << sizeof(hello) << " bytes) ... " << std::endl; 
	
	/**
	  * Load program 'hello'
	  */ 
	vm.load(hello, sizeof(hello), 0xE);
	
	/**
	  * Dump the machine state
	  */ 
	vm.dump(stdout);
	vm.trace(stdout);
	
	std::cout << std::endl << std::endl;
	std::cout << "Loading demo program 'square' (" << std::dec << sizeof(square) << " bytes) ... " << std::endl;
	
	/**
	  * Load program 'hello'
	  */ 
	vm.load(square, sizeof(square), 0xC);
	
	/**
	  * Dump the machine state
	  */ 
	vm.dump(stdout);
	vm.trace(stdout);
}
