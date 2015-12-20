#include "include/processor.hpp"
#include "include/opcode.hpp"
#include "include/exception.hpp"

#include <iostream>

using machina::processor;

void processor::dump( FILE *output )
{
	fprintf(output,         "Machina processor dump:\n");
	fprintf(output,         "  status:             0x%X          \n", this->status);
	fprintf(output,         "  frame-stack size:   %lu           \n", this->frame_stack.size());
	
	if(this->frame_stack.empty())
	{
		fprintf(output, "  frame-stack top:    (empty)       \n" );
	}
	else
	{
		fprintf(output, "  frame-stack top:    0x%.16lX      \n", this->frame_stack.top());
	}
	
	fprintf(output,         "  operand-stack size: %lu           \n", this->operand_stack.size());
	
	if(this->operand_stack.empty())
	{
		fprintf(output, "  operand-stack top:  (empty)       \n");
	}
	else
	{
		fprintf(output, "  operand-stack top:  0x%.16lX      \n", this->operand_stack.top());
	}
}

void processor::trace( FILE *output )
{
	fprintf(output, "Machina processor frame-stack trace:\n");
	
	for(machina::arch::size_t index = 0; !this->frame_stack.empty(); index++)
	{
		try
		{
			fprintf(output, "  [%lu] 0x%.16lX  -->  0x%.16lX \n", index, this->frame_stack.top(), this->memory->read_int64(this->frame_stack.top()));
		}
		catch(machina::exception::invalid_address &invadd)
		{
			fprintf(output, "  [%lu] 0x%.16lX  -->   (outside memory) \n", index, this->frame_stack.top());
		}
		
		this->frame_stack.pop();
	}
}

#define OP_CASE(operation,operand,size) 		\
	case machina::opcode_##operation:		\
		this->exec_##operation(operand);	\
		this->next((size));			\
	break;	
	
#define NOP_CASE(operation,size)			\
	case machina::opcode_##operation:		\
		this->next((size));			\
	break;

void processor::step(  )
{
	machina::instruction instr = this->fetch();
	
	machina::exception::invalid_opcode invopc; //char buffer[64];
	
	switch(instr.opcode())
	{
		/**
		  * The nop instruction
		  */
		NOP_CASE(nop, machina::instruction_size_byte)
		
		/**
		  * Load instructions for immediate values
		  */
		OP_CASE(load_immediate_int8,  instr.operand_as_int8(),  machina::instruction_size_multibyte)
		OP_CASE(load_immediate_int16, instr.operand_as_int16(), machina::instruction_size_multibyte)
		OP_CASE(load_immediate_int32, instr.operand_as_int32(), machina::instruction_size_multibyte)
		OP_CASE(load_immediate_int64, instr.operand_as_int64(), machina::instruction_size_multibyte)
		OP_CASE(load_immediate_float, instr.operand_as_float(), machina::instruction_size_multibyte)
		
		/**
		  * Load instructions for mediate values
		  */
		OP_CASE(load_int8,  , machina::instruction_size_byte)
		OP_CASE(load_int16, , machina::instruction_size_byte)
		OP_CASE(load_int32, , machina::instruction_size_byte)
		OP_CASE(load_int64, , machina::instruction_size_byte)
		OP_CASE(load_float, , machina::instruction_size_byte)
		
		/**
		  * Type conversions
		  */
		OP_CASE(convert_float_to_int64, , machina::instruction_size_byte)
		OP_CASE(convert_int64_to_float, , machina::instruction_size_byte)
		OP_CASE(convert_int64_to_int32, , machina::instruction_size_byte)
		OP_CASE(convert_int32_to_int16, , machina::instruction_size_byte)
		OP_CASE(convert_int16_to_int8,  , machina::instruction_size_byte)
		OP_CASE(convert_int8_to_int16,  , machina::instruction_size_byte)
		OP_CASE(convert_int16_to_int32, , machina::instruction_size_byte)
		OP_CASE(convert_int32_to_int64, , machina::instruction_size_byte)
		
		/**
		  * Store instructions for immediate values as address
		  */
		OP_CASE(store_immediate_int8,  instr.operand_as_addr(), machina::instruction_size_multibyte)
		OP_CASE(store_immediate_int16, instr.operand_as_addr(), machina::instruction_size_multibyte)
		OP_CASE(store_immediate_int32, instr.operand_as_addr(), machina::instruction_size_multibyte)
		OP_CASE(store_immediate_int64, instr.operand_as_addr(), machina::instruction_size_multibyte)
		OP_CASE(store_immediate_float, instr.operand_as_addr(), machina::instruction_size_multibyte)
		
		/**
		  * Store instructions for mediate values as address
		  */
		OP_CASE(store_int8,  , machina::instruction_size_byte)
		OP_CASE(store_int16, , machina::instruction_size_byte)
		OP_CASE(store_int32, , machina::instruction_size_byte)
		OP_CASE(store_int64, , machina::instruction_size_byte)
		OP_CASE(store_float, , machina::instruction_size_byte)
		
		/**
		  * Memory management
		  */
		OP_CASE(alloc_immediate, instr.operand_as_int64(), machina::instruction_size_multibyte)
		OP_CASE(alloc,                                   , machina::instruction_size_byte)
		OP_CASE(free,                                    , machina::instruction_size_byte)
		
		/**
		  * Control Unit operations 
		  */
		OP_CASE(jmp,            instr.operand_as_addr(), 0)
		OP_CASE(jmpz,           instr.operand_as_addr(), 0)
		OP_CASE(jmpnz,          instr.operand_as_addr(), 0)
		OP_CASE(jmpgz,          instr.operand_as_addr(), 0)
		OP_CASE(jmplz,          instr.operand_as_addr(), 0)
		OP_CASE(jmpeq,          instr.operand_as_addr(), 0)
		OP_CASE(jmpneq,         instr.operand_as_addr(), 0)
		OP_CASE(call_immediate, instr.operand_as_addr(), 0)
		OP_CASE(call,                                  , 0)
		OP_CASE(ret,                                   , 0)
		OP_CASE(halt,                                  , 0)
		
		/**
		  * Call-stack operations
		  */
		OP_CASE(frame,   instr.operand_as_int64(), machina::instruction_size_multibyte)
		OP_CASE(obtain,  instr.operand_as_int64(), machina::instruction_size_multibyte)
		OP_CASE(place,   instr.operand_as_int64(), machina::instruction_size_multibyte)
		OP_CASE(cleanup, instr.operand_as_int64(), machina::instruction_size_multibyte)
		
		/**
		  * ALU operations
		  */
		OP_CASE(inc_int8,  , machina::instruction_size_byte)
		OP_CASE(inc_int16, , machina::instruction_size_byte)
		OP_CASE(inc_int32, , machina::instruction_size_byte)
		OP_CASE(inc_int64, , machina::instruction_size_byte)
		OP_CASE(inc_float, , machina::instruction_size_byte)
		
		OP_CASE(dec_int8,  , machina::instruction_size_byte)
		OP_CASE(dec_int16, , machina::instruction_size_byte)
		OP_CASE(dec_int32, , machina::instruction_size_byte)
		OP_CASE(dec_int64, , machina::instruction_size_byte)
		OP_CASE(dec_float, , machina::instruction_size_byte)
		
		OP_CASE(add_immediate_int8,  instr.operand_as_int8(),  machina::instruction_size_multibyte)
		OP_CASE(add_immediate_int16, instr.operand_as_int16(), machina::instruction_size_multibyte)
		OP_CASE(add_immediate_int32, instr.operand_as_int32(), machina::instruction_size_multibyte)
		OP_CASE(add_immediate_int64, instr.operand_as_int64(), machina::instruction_size_multibyte)
		OP_CASE(add_immediate_float, instr.operand_as_float(), machina::instruction_size_multibyte)
		
		OP_CASE(add_int8,  , machina::instruction_size_byte)
		OP_CASE(add_int16, , machina::instruction_size_byte)
		OP_CASE(add_int32, , machina::instruction_size_byte)
		OP_CASE(add_int64, , machina::instruction_size_byte)
		OP_CASE(add_float, , machina::instruction_size_byte)
		
		OP_CASE(sub_immediate_int8,  instr.operand_as_int8(),  machina::instruction_size_multibyte)
		OP_CASE(sub_immediate_int16, instr.operand_as_int16(), machina::instruction_size_multibyte)
		OP_CASE(sub_immediate_int32, instr.operand_as_int32(), machina::instruction_size_multibyte)
		OP_CASE(sub_immediate_int64, instr.operand_as_int64(), machina::instruction_size_multibyte)
		OP_CASE(sub_immediate_float, instr.operand_as_float(), machina::instruction_size_multibyte)
		
		OP_CASE(sub_int8,  , machina::instruction_size_byte)
		OP_CASE(sub_int16, , machina::instruction_size_byte)
		OP_CASE(sub_int32, , machina::instruction_size_byte)
		OP_CASE(sub_int64, , machina::instruction_size_byte)
		OP_CASE(sub_float, , machina::instruction_size_byte)
		
		OP_CASE(mul_immediate_int8,  instr.operand_as_int8(),  machina::instruction_size_multibyte)
		OP_CASE(mul_immediate_int16, instr.operand_as_int16(), machina::instruction_size_multibyte)
		OP_CASE(mul_immediate_int32, instr.operand_as_int32(), machina::instruction_size_multibyte)
		OP_CASE(mul_immediate_int64, instr.operand_as_int64(), machina::instruction_size_multibyte)
		OP_CASE(mul_immediate_float, instr.operand_as_float(), machina::instruction_size_multibyte)
		
		OP_CASE(mul_int8,  , machina::instruction_size_byte)
		OP_CASE(mul_int16, , machina::instruction_size_byte)
		OP_CASE(mul_int32, , machina::instruction_size_byte)
		OP_CASE(mul_int64, , machina::instruction_size_byte)
		OP_CASE(mul_float, , machina::instruction_size_byte)
		
		OP_CASE(div_immediate_int8,  instr.operand_as_int8(),  machina::instruction_size_multibyte)
		OP_CASE(div_immediate_int16, instr.operand_as_int16(), machina::instruction_size_multibyte)
		OP_CASE(div_immediate_int32, instr.operand_as_int32(), machina::instruction_size_multibyte)
		OP_CASE(div_immediate_int64, instr.operand_as_int64(), machina::instruction_size_multibyte)
		OP_CASE(div_immediate_float, instr.operand_as_float(), machina::instruction_size_multibyte)
		
		OP_CASE(div_int8,  , machina::instruction_size_byte)
		OP_CASE(div_int16, , machina::instruction_size_byte)
		OP_CASE(div_int32, , machina::instruction_size_byte)
		OP_CASE(div_int64, , machina::instruction_size_byte)
		OP_CASE(div_float, , machina::instruction_size_byte)
		
		OP_CASE(mod_immediate_int8,  instr.operand_as_int8(),  machina::instruction_size_multibyte)
		OP_CASE(mod_immediate_int16, instr.operand_as_int16(), machina::instruction_size_multibyte)
		OP_CASE(mod_immediate_int32, instr.operand_as_int32(), machina::instruction_size_multibyte)
		OP_CASE(mod_immediate_int64, instr.operand_as_int64(), machina::instruction_size_multibyte)
		
		OP_CASE(mod_int8,  , machina::instruction_size_byte)
		OP_CASE(mod_int16, , machina::instruction_size_byte)
		OP_CASE(mod_int32, , machina::instruction_size_byte)
		OP_CASE(mod_int64, , machina::instruction_size_byte)
		
		OP_CASE(and_immediate_int8,  instr.operand_as_int8(),  machina::instruction_size_multibyte)
		OP_CASE(and_immediate_int16, instr.operand_as_int16(), machina::instruction_size_multibyte)
		OP_CASE(and_immediate_int32, instr.operand_as_int32(), machina::instruction_size_multibyte)
		OP_CASE(and_immediate_int64, instr.operand_as_int64(), machina::instruction_size_multibyte)
		
		OP_CASE(and_int8,  , machina::instruction_size_byte)
		OP_CASE(and_int16, , machina::instruction_size_byte)
		OP_CASE(and_int32, , machina::instruction_size_byte)
		OP_CASE(and_int64, , machina::instruction_size_byte)
		
		OP_CASE(or_immediate_int8,  instr.operand_as_int8(),  machina::instruction_size_multibyte)
		OP_CASE(or_immediate_int16, instr.operand_as_int16(), machina::instruction_size_multibyte)
		OP_CASE(or_immediate_int32, instr.operand_as_int32(), machina::instruction_size_multibyte)
		OP_CASE(or_immediate_int64, instr.operand_as_int64(), machina::instruction_size_multibyte)
		
		OP_CASE(or_int8,  , machina::instruction_size_byte)
		OP_CASE(or_int16, , machina::instruction_size_byte)
		OP_CASE(or_int32, , machina::instruction_size_byte)
		OP_CASE(or_int64, , machina::instruction_size_byte)
		
		OP_CASE(xor_immediate_int8,  instr.operand_as_int8(),  machina::instruction_size_multibyte)
		OP_CASE(xor_immediate_int16, instr.operand_as_int16(), machina::instruction_size_multibyte)
		OP_CASE(xor_immediate_int32, instr.operand_as_int32(), machina::instruction_size_multibyte)
		OP_CASE(xor_immediate_int64, instr.operand_as_int64(), machina::instruction_size_multibyte)
		
		OP_CASE(xor_int8,  , machina::instruction_size_byte)
		OP_CASE(xor_int16, , machina::instruction_size_byte)
		OP_CASE(xor_int32, , machina::instruction_size_byte)
		OP_CASE(xor_int64, , machina::instruction_size_byte)
		
		OP_CASE(not_int8,  , machina::instruction_size_byte)
		OP_CASE(not_int16, , machina::instruction_size_byte)
		OP_CASE(not_int32, , machina::instruction_size_byte)
		OP_CASE(not_int64, , machina::instruction_size_byte)
		
		OP_CASE(cmp_immediate_int8,  instr.operand_as_int8(),  machina::instruction_size_multibyte)
		OP_CASE(cmp_immediate_int16, instr.operand_as_int16(), machina::instruction_size_multibyte)
		OP_CASE(cmp_immediate_int32, instr.operand_as_int32(), machina::instruction_size_multibyte)
		OP_CASE(cmp_immediate_int64, instr.operand_as_int64(), machina::instruction_size_multibyte)
		OP_CASE(cmp_immediate_float, instr.operand_as_float(), machina::instruction_size_multibyte)
		
		OP_CASE(cmp_int8,  , machina::instruction_size_byte)
		OP_CASE(cmp_int16, , machina::instruction_size_byte)
		OP_CASE(cmp_int32, , machina::instruction_size_byte)
		OP_CASE(cmp_int64, , machina::instruction_size_byte)
		OP_CASE(cmp_float, , machina::instruction_size_byte)
		
		/**
		  * Stack manipulation operations
		  */
		OP_CASE(dup,                          , machina::instruction_size_byte)
		OP_CASE(swap,                         , machina::instruction_size_byte)
		OP_CASE(rol,                          , machina::instruction_size_byte)
		OP_CASE(roln, instr.operand_as_int64(), machina::instruction_size_multibyte)
		OP_CASE(drop,                         , machina::instruction_size_byte)		
		
		/**
		  * Output operations
		  */
		OP_CASE(out_immediate, instr.operand_as_int8(), machina::instruction_size_multibyte)
		OP_CASE(out,                                  , machina::instruction_size_byte)
		
		default:
			char buffer[64]; sprintf(buffer, " : 0x%.2X  0x%.16lX\n", instr.opcode(), instr.operand_as_int64());
			invopc.message = buffer;
			throw invopc;
		break;
	}
}

void processor::run(  )
{
	while(!(this->status & machina::processor::halted))
	{
		try
		{
			this->step();
		}
		catch(machina::exception::invalid_opcode &invopc)
		{
			std::cerr << std::endl << "invalid opcode [exception]: @ 0x" << std::hex << this->ip << " : " << invopc.message << std::endl;
			this->status = this->status | machina::processor::halted | machina::processor::aborted;
		}
		catch(machina::exception::double_free &doufre)
		{
			std::cerr << std::endl << "double free [exception]: @ 0x" << std::hex << this->ip << " : " << doufre.message << std::endl;
			this->status = this->status | machina::processor::halted | machina::processor::aborted;
		}
		catch(machina::exception::corrupted_memory &cormem)
		{
			std::cerr << std::endl << "corrupted memory [exception]: @ 0x" << std::hex << this->ip << " : " << cormem.message << std::endl;
			this->status = this->status | machina::processor::halted | machina::processor::aborted;
		}
		catch(machina::exception::out_of_memory &oomem)
		{
			std::cerr << std::endl << "out of memory [exception]: @ 0x" << std::hex << this->ip << " : " << oomem.message << std::endl;
			this->status = this->status | machina::processor::halted | machina::processor::aborted;
		}
		catch(machina::exception::invalid_address &invadd)
		{
			std::cerr << std::endl << "invalid address [exception]: @ 0x" << std::hex << this->ip << " : " << invadd.message << std::endl;
			this->status = this->status | machina::processor::halted | machina::processor::aborted;
		}
	}
}

machina::instruction processor::fetch(  )
{
	return machina::instruction(this->memory->read_instruction(this->ip));
}

void processor::next( machina::arch::size_t offset )
{
	this->ip += offset;
}
