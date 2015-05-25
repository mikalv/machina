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
		  * Function 'sqare'
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

/** 0x003E */	machina::opcode_halt,
};

int main(  )
{
	/**
	  * Instance of 'machina' virtual machine 
	  */ 
	machina::virtual_machine vm;
	
	/**
	  * Load program 'square'
	  */ 
	vm.load(square, sizeof(square), 0xC);
	
	/**
	  * Dump the machine state
	  */ 
	vm.dump(stdout);
	vm.trace(stdout);
}
