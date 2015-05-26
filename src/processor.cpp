#include "include/processor.hpp"
#include "include/opcode.hpp"

#include <iostream>

using machina::processor;

void processor::dump( FILE *output )
{
#ifdef MACHINA_ARCH_64
	fprintf(output,         "Machina processor dump:\n");
	fprintf(output,         "   status:          0x%X          \n", this->status);
	fprintf(output,         "   call-stack size: %lu           \n", this->call_stack.size());
	
	if(this->call_stack.empty())
	{
		fprintf(output, "   call-stack top:  (empty)       \n" );
	}
	else
	{
		fprintf(output, "   call-stack top:  0x%.16lX      \n", this->call_stack.top());
	}
	
	fprintf(output,         "   data-stack size: %lu           \n", this->data_stack.size());
	
	if(this->data_stack.empty())
	{
		fprintf(output, "   data-stack top:  (empty)       \n");
	}
	else
	{
		fprintf(output, "   data-stack top:  0x%.16lX      \n", this->data_stack.top());
	}
	
#elif MACHINA_ARCH_32
	fprintf(output,         "Machina processor dump:\n");
	fprintf(output,         "   status:          0x%X          \n", this->status);
	fprintf(output,         "   call-stack size: %lu           \n", this->call_stack.size());
	
	if(this->call_stack.empty())
	{
		fprintf(output, "   call-stack top:  (empty)       \n" );
	}
	else
	{
		fprintf(output, "   call-stack top:  0x%.16X       \n", this->call_stack.top());
	}
	
	fprintf(output,         "   data-stack size: %lu           \n", this->data_stack.size());
	
	if(this->data_stack.empty())
	{
		fprintf(output, "   data-stack top:  (empty)       \n");
	}
	else
	{
		fprintf(output, "   data-stack top:  0x%.16X       \n", this->data_stack.top());
	}
	
#endif
}

void processor::trace( FILE *output )
{
#ifdef MACHINA_ARCH_64
	fprintf(output, "Machina processor call-stack trace:\n");
	
	for(machina::arch::size_t index = 0; !this->call_stack.empty(); index++)
	{
		fprintf(output, "   [%lu] 0x%.16lX  ->  0x%.16lX \n", index, this->call_stack.top(), this->memory->read_long(this->call_stack.top()));
		
		this->call_stack.pop();
	}
	
#elif MACHINA_ARCH_32
	fprintf(output, "Machina processor call-stack trace:\n");
	
	for(machina::arch::size_t index = 0; !this->call_stack.empty(); index++)
	{
		fprintf(output, "   [%u] 0x%.16X  ->  0x%.16X    \n", index, this->call_stack.top(), this->memory->read_long(this->call_stack.top()));
		
		this->call_stack.pop();
	}
	
#endif
}

void processor::step(  )
{
	machina::instruction instr = this->fetch();

	switch(instr.opcode())
	{
		/**
		  * The nop instruction
		  */
		case machina::opcode_nop:
			this->next(machina::instruction_byte);
		break;
		
		/**
		  * Load instructions for immediate values
		  */
		case machina::opcode_load_immediate_byte:
			this->exec_load_immediate_byte(instr.operand());
			this->next(machina::instruction_multibyte);
		break;
		
		case machina::opcode_load_immediate_short:
			this->exec_load_immediate_short(instr.operand());
			this->next(machina::instruction_multibyte);
		break;
		
		case machina::opcode_load_immediate_int:
			this->exec_load_immediate_int(instr.operand());
			this->next(machina::instruction_multibyte);
		break;
		
		case machina::opcode_load_immediate_long:
			this->exec_load_immediate_long(instr.operand());
			this->next(machina::instruction_multibyte);
		break;
		
		/**
		  * Load instructions for memory values
		  */
		case machina::opcode_load_byte:
			this->exec_load_byte();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_load_short:
			this->exec_load_short();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_load_int:
			this->exec_load_int();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_load_long:
			this->exec_load_long();
			this->next(machina::instruction_byte);
		break;
		
		/**
		  * Store instructions with immediate value as address
		  */ 
		case machina::opcode_store_immediate_byte:
			this->exec_store_immediate_byte(instr.operand());
			this->next(machina::instruction_multibyte);
		break;
		
		case machina::opcode_store_immediate_short:
			this->exec_store_immediate_short(instr.operand());
			this->next(machina::instruction_multibyte);
		break;
		
		case machina::opcode_store_immediate_int:
			this->exec_store_immediate_int(instr.operand());
			this->next(machina::instruction_multibyte);
		break;
		
		case machina::opcode_store_immediate_long:
			this->exec_store_immediate_long(instr.operand());
			this->next(machina::instruction_multibyte);
		break;
		
		/**
		  * Store instructions
		  */ 
		case machina::opcode_store_byte:
			this->exec_store_byte();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_store_short:
			this->exec_store_short();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_store_int:
			this->exec_store_int();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_store_long:
			this->exec_store_long();
			this->next(machina::instruction_byte);
		break;
		
		/**
		  * Control Unit operations
		  */
		case machina::opcode_jmp:
			this->exec_jmp(instr.operand());
		break;
		
		case machina::opcode_jmpz:
			this->exec_jmpz(instr.operand());
		break;
		
		case machina::opcode_jmpnz:
			this->exec_jmpnz(instr.operand());
		break;
		
		case machina::opcode_jmpgz:
			this->exec_jmpgz(instr.operand());
		break;
		
		case machina::opcode_jmplz:
			this->exec_jmplz(instr.operand());
		break;
		
		case machina::opcode_jmpeq:
			this->exec_jmpeq(instr.operand());
		break;
		
		case machina::opcode_jmpneq:			
			this->exec_jmpneq(instr.operand());
		break;
		
		case machina::opcode_call:
			this->exec_call();
		break;
		
		case machina::opcode_call_immediate:
			this->exec_call(instr.operand());
		break;
		
		case machina::opcode_ret:
			this->exec_ret();
		break;
		
		
		/**
		  * Call-stack operations
		  */
		case machina::opcode_frame:
			this->exec_frame(instr.operand());
			this->next(machina::instruction_multibyte);
		break;
		
		case machina::opcode_obtain:
			this->exec_obtain(instr.operand());
			this->next(machina::instruction_multibyte);
		break;
		
		case machina::opcode_place:
			this->exec_place(instr.operand());
			this->next(machina::instruction_multibyte);
		break;
		
		case machina::opcode_cleanup:
			this->exec_cleanup(instr.operand());
			this->next(machina::instruction_multibyte);
		break;
		
		
		/**
		  * ALU operations
		  */
		case machina::opcode_inc_byte:
			this->exec_inc_byte();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_inc_short:
			this->exec_inc_short();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_inc_int:
			this->exec_inc_int();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_inc_long:
			this->exec_inc_long();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_dec_byte:
			this->exec_dec_byte();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_dec_short:
			this->exec_dec_short();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_dec_int:
			this->exec_dec_int();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_dec_long:
			this->exec_dec_long();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_add_byte:
			this->exec_add_byte();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_add_short:
			this->exec_add_short();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_add_int:
			this->exec_add_int();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_add_long:
			this->exec_add_long();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_sub_byte:
			this->exec_sub_byte();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_sub_short:
			this->exec_sub_short();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_sub_int:
			this->exec_sub_int();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_sub_long:
			this->exec_sub_long();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_mul_byte:
			this->exec_mul_byte();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_mul_short:
			this->exec_mul_short();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_mul_int:
			this->exec_mul_int();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_mul_long:
			this->exec_mul_long();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_div_byte:
			this->exec_div_byte();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_div_short:
			this->exec_div_short();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_div_int:
			this->exec_div_int();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_div_long:
			this->exec_div_long();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_mod_byte:
			this->exec_mod_byte();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_mod_short:
			this->exec_mod_short();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_mod_int:
			this->exec_mod_int();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_mod_long:
			this->exec_mod_long();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_and_byte:
			this->exec_and_byte();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_and_short:
			this->exec_and_short();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_and_int:
			this->exec_and_int();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_and_long:
			this->exec_and_long();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_or_byte:
			this->exec_or_byte();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_or_short:
			this->exec_or_short();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_or_int:
			this->exec_or_int();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_or_long:
			this->exec_or_long();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_xor_byte:
			this->exec_xor_byte();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_xor_short:
			this->exec_xor_short();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_xor_int:
			this->exec_xor_int();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_xor_long:
			this->exec_xor_long();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_not_byte:
			this->exec_not_byte();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_not_short:
			this->exec_not_short();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_not_int:
			this->exec_not_int();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_not_long:
			this->exec_not_long();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_dup:
			this->exec_dup();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_swap:
			this->exec_swap();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_rol:
			this->exec_rol();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_roln:
			this->exec_roln(instr.operand());
			this->next(machina::instruction_multibyte);
		break;
		
		case machina::opcode_out:
			this->exec_out();
			this->next(machina::instruction_byte);
		break;
		
		case machina::opcode_halt:
			this->exec_halt();
			this->next(machina::instruction_byte);
		break;
	}
}

void processor::run(  )
{
	while(!(this->status & machina::processor::halted))
	{		
		this->step();
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


void processor::exec_load_immediate_byte( machina::arch::byte_t value )
{
	//std::cout << "load " << std::hex << value << std::endl;
	
	this->data_stack.push(value);
}

void processor::exec_load_immediate_short( machina::arch::short_t value )
{
	//std::cout << "load " << std::hex << value << std::endl;

	this->data_stack.push(value);
}

void processor::exec_load_immediate_int( machina::arch::int_t value )
{
	//std::cout << "load " << std::hex << value << std::endl;
	
	this->data_stack.push(value);
}

void processor::exec_load_immediate_long( machina::arch::long_t value )
{
	//std::cout << "load " << std::hex << value << std::endl;

	this->data_stack.push(value);
}

void processor::exec_load_byte(  )
{
	machina::arch::byte_t value;
	machina::arch::pointer_t address;
	
	address = this->data_stack.top();
	this->data_stack.pop();
	
	value = this->memory->read_byte(address);
	
	//std::cout << "load " << std::hex << value << std::endl;
	
	this->data_stack.push(value);
}

void processor::exec_load_short(  )
{
	machina::arch::short_t value;
	machina::arch::pointer_t address;
	
	address = this->data_stack.top();
	this->data_stack.pop();
	
	value = this->memory->read_short(address);
	
	//std::cout << "load " << std::hex << value << std::endl;

	this->data_stack.push(value);
}

void processor::exec_load_int(  )
{
	machina::arch::int_t value;
	machina::arch::pointer_t address;
	
	address = this->data_stack.top();
	this->data_stack.pop();
	
	value = this->memory->read_int(address);
	
	//std::cout << "load " << std::hex << value << std::endl;

	this->data_stack.push(value);
}

void processor::exec_load_long(  )
{
	machina::arch::long_t value;
	machina::arch::pointer_t address;
	
	address = this->data_stack.top();
	this->data_stack.pop();
	
	value = this->memory->read_long(address);
	
	//std::cout << "load " << std::hex << value << std::endl;

	this->data_stack.push(value);
}

void processor::exec_store_immediate_byte( machina::arch::pointer_t address )
{
	machina::arch::byte_t value;
	
	value = this->data_stack.top();
	this->data_stack.pop();
	
	//std::cout << "store " << std::hex << value << " @ " << address << std::endl;

	this->memory->write_byte(address, value);
}

void processor::exec_store_immediate_short( machina::arch::pointer_t address )
{
	machina::arch::short_t value;
	
	value = this->data_stack.top();
	this->data_stack.pop();
	
	//std::cout << "store " << std::hex << value << " @ " << address << std::endl;

	this->memory->write_short(address, value);
}

void processor::exec_store_immediate_int( machina::arch::pointer_t address )
{
	machina::arch::int_t value;
	
	value = this->data_stack.top();
	this->data_stack.pop();
	
	//std::cout << "store " << std::hex << value << " @ " << address << std::endl;

	this->memory->write_int(address, value);
}

void processor::exec_store_immediate_long( machina::arch::pointer_t address )
{
	machina::arch::long_t value;
	
	value = this->data_stack.top();
	this->data_stack.pop();
	
	//std::cout << "store " << std::hex << value << " @ " << address << std::endl;

	this->memory->write_long(address, value);
}

void processor::exec_store_byte(  )
{
	machina::arch::byte_t value;
	machina::arch::pointer_t address;
	
	value = this->data_stack.top();
	this->data_stack.pop();
	address = this->data_stack.top();
	this->data_stack.pop();
	
	//std::cout << "store " << std::hex << value << " @ " << address << std::endl;

	this->memory->write_byte(address, value);
}

void processor::exec_store_short(  )
{
	machina::arch::short_t value;
	machina::arch::pointer_t address;
	
	value = this->data_stack.top();
	this->data_stack.pop();
	address = this->data_stack.top();
	this->data_stack.pop();
	
	//std::cout << "store " << std::hex << value << " @ " << address << std::endl;

	this->memory->write_short(address, value);
}

void processor::exec_store_int(  )
{
	machina::arch::int_t value;
	machina::arch::pointer_t address;
	
	value = this->data_stack.top();
	this->data_stack.pop();
	address = this->data_stack.top();
	this->data_stack.pop();
	
	//std::cout << "store " << std::hex << value << " @ " << address << std::endl;

	this->memory->write_int(address, value);
}

void processor::exec_store_long(  )
{
	machina::arch::long_t value;
	machina::arch::pointer_t address;
	
	value = this->data_stack.top();
	this->data_stack.pop();
	address = this->data_stack.top();
	this->data_stack.pop();
	
	//std::cout << "store " << std::hex << value << " @ " << address << std::endl;

	this->memory->write_long(address, value);
}

void processor::exec_inc_byte(  )
{
	//std::cout << "inc " << std::hex << this->data_stack.top() << std::endl;
	
	machina::arch::byte_t tmp0 = this->data_stack.top();
	this->data_stack.pop();
	tmp0 += 1;
	this->data_stack.push(tmp0);
}

void processor::exec_inc_short(  )
{
	//std::cout << "inc " << std::hex << this->data_stack.top() << std::endl;
	
	machina::arch::short_t tmp0 = this->data_stack.top();
	this->data_stack.pop();
	tmp0 += 1;
	this->data_stack.push(tmp0);
}

void processor::exec_inc_int(  )
{
	//std::cout << "inc " << std::hex << this->data_stack.top() << std::endl;
	
	machina::arch::int_t tmp0 = this->data_stack.top();
	this->data_stack.pop();
	tmp0 += 1;
	this->data_stack.push(tmp0);
}

void processor::exec_inc_long(  )
{
	//std::cout << "inc " << std::hex << this->data_stack.top() << std::endl;
	
	machina::arch::long_t tmp0 = this->data_stack.top();
	this->data_stack.pop();
	tmp0 += 1;
	this->data_stack.push(tmp0);
}

void processor::exec_dec_byte(  )
{
	//std::cout << "dec " << std::hex << this->data_stack.top() << std::endl;
	
	machina::arch::byte_t tmp0 = this->data_stack.top();
	this->data_stack.pop();
	tmp0 -= 1;
	this->data_stack.push(tmp0);
}

void processor::exec_dec_short(  )
{
	//std::cout << "dec " << std::hex << this->data_stack.top() << std::endl;
	
	machina::arch::short_t tmp0 = this->data_stack.top();
	this->data_stack.pop();
	tmp0 -= 1;
	this->data_stack.push(tmp0);
}

void processor::exec_dec_int(  )
{
	//std::cout << "dec " << std::hex << this->data_stack.top() << std::endl;
	
	machina::arch::int_t tmp0 = this->data_stack.top();
	this->data_stack.pop();
	tmp0 -= 1;
	this->data_stack.push(tmp0);
}

void processor::exec_dec_long(  )
{
	//std::cout << "dec " << std::hex << this->data_stack.top() << std::endl;
	
	machina::arch::long_t tmp0 = this->data_stack.top();
	this->data_stack.pop();
	tmp0 -= 1;
	this->data_stack.push(tmp0);
}

void processor::exec_add_byte(  )
{
	machina::arch::byte_t tmp0, tmp1, result;
	
	tmp0 = this->data_stack.top();
	this->data_stack.pop();
	tmp1 = this->data_stack.top();
	this->data_stack.pop();
	
	result = tmp1 + tmp0;
	
	//std::cout << "add " << std::hex << tmp1 << "  " << tmp0 << std::endl;
	
	this->data_stack.push(result);
}

void processor::exec_add_short(  )
{
	machina::arch::short_t tmp0, tmp1, result;
	
	tmp0 = this->data_stack.top();
	this->data_stack.pop();
	tmp1 = this->data_stack.top();
	this->data_stack.pop();
	
	result = tmp1 + tmp0;
	
	//std::cout << "add " << std::hex << tmp1 << "  " << tmp0 << std::endl;
	
	this->data_stack.push(result);
}

void processor::exec_add_int(  )
{
	machina::arch::int_t tmp0, tmp1, result;
	
	tmp0 = this->data_stack.top();
	this->data_stack.pop();
	tmp1 = this->data_stack.top();
	this->data_stack.pop();
	
	result = tmp1 + tmp0;
	
	//std::cout << "add " << std::hex << tmp1 << "  " << tmp0 << std::endl;
	
	this->data_stack.push(result);
}

void processor::exec_add_long(  )
{
	machina::arch::long_t tmp0, tmp1, result;
	
	tmp0 = this->data_stack.top();
	this->data_stack.pop();
	tmp1 = this->data_stack.top();
	this->data_stack.pop();
	
	result = tmp1 + tmp0;
	
	//std::cout << "add " << std::hex << tmp1 << "  " << tmp0 << std::endl;
	
	this->data_stack.push(result);
}

void processor::exec_sub_byte(  )
{
	machina::arch::byte_t tmp0, tmp1, result;
	
	tmp0 = this->data_stack.top();
	this->data_stack.pop();
	tmp1 = this->data_stack.top();
	this->data_stack.pop();
	
	result = tmp1 - tmp0;
	
	//std::cout << "sub " << std::hex << tmp1 << "  " << tmp0 << std::endl;

	this->data_stack.push(result);
}

void processor::exec_sub_short(  )
{
	machina::arch::short_t tmp0, tmp1, result;
	
	tmp0 = this->data_stack.top();
	this->data_stack.pop();
	tmp1 = this->data_stack.top();
	this->data_stack.pop();
	
	result = tmp1 - tmp0;
	
	//std::cout << "sub " << std::hex << tmp1 << "  " << tmp0 << std::endl;

	this->data_stack.push(result);
}

void processor::exec_sub_int(  )
{
	machina::arch::int_t tmp0, tmp1, result;
	
	tmp0 = this->data_stack.top();
	this->data_stack.pop();
	tmp1 = this->data_stack.top();
	this->data_stack.pop();
	
	result = tmp1 - tmp0;
	
	//std::cout << "sub " << std::hex << tmp1 << "  " << tmp0 << std::endl;

	this->data_stack.push(result);
}

void processor::exec_sub_long(  )
{
	machina::arch::long_t tmp0, tmp1, result;
	
	tmp0 = this->data_stack.top();
	this->data_stack.pop();
	tmp1 = this->data_stack.top();
	this->data_stack.pop();
	
	result = tmp1 - tmp0;
	
	//std::cout << "sub " << std::hex << tmp1 << "  " << tmp0 << std::endl;

	this->data_stack.push(result);
}

void processor::exec_mul_byte(  )
{
	machina::arch::byte_t tmp0, tmp1, result;
	
	tmp0 = this->data_stack.top();
	this->data_stack.pop();
	tmp1 = this->data_stack.top();
	this->data_stack.pop();
	
	result = tmp1 * tmp0;
	
	//std::cout << "mul " << std::hex << tmp1 << "  " << tmp0 << std::endl;

	this->data_stack.push(result);
}

void processor::exec_mul_short(  )
{
	machina::arch::short_t tmp0, tmp1, result;
	
	tmp0 = this->data_stack.top();
	this->data_stack.pop();
	tmp1 = this->data_stack.top();
	this->data_stack.pop();
	
	result = tmp1 * tmp0;
	
	//std::cout << "mul " << std::hex << tmp1 << "  " << tmp0 << std::endl;

	this->data_stack.push(result);
}

void processor::exec_mul_int(  )
{
	machina::arch::int_t tmp0, tmp1, result;
	
	tmp0 = this->data_stack.top();
	this->data_stack.pop();
	tmp1 = this->data_stack.top();
	this->data_stack.pop();
	
	result = tmp1 * tmp0;
	
	//std::cout << "mul " << std::hex << tmp1 << "  " << tmp0 << std::endl;

	this->data_stack.push(result);
}

void processor::exec_mul_long(  )
{
	machina::arch::long_t tmp0, tmp1, result;
	
	tmp0 = this->data_stack.top();
	this->data_stack.pop();
	tmp1 = this->data_stack.top();
	this->data_stack.pop();
	
	result = tmp1 * tmp0;
	
	//std::cout << "mul " << std::hex << tmp1 << "  " << tmp0 << std::endl;

	this->data_stack.push(result);
}

void processor::exec_div_byte(  )
{
	machina::arch::byte_t tmp0, tmp1, result;
	
	tmp0 = this->data_stack.top();
	this->data_stack.pop();
	tmp1 = this->data_stack.top();
	this->data_stack.pop();
	
	result = tmp1 / tmp0;
	
	//std::cout << "div " << std::hex << tmp1 << "  " << tmp0 << std::endl;

	this->data_stack.push(result);
}

void processor::exec_div_short(  )
{
	machina::arch::short_t tmp0, tmp1, result;
	
	tmp0 = this->data_stack.top();
	this->data_stack.pop();
	tmp1 = this->data_stack.top();
	this->data_stack.pop();
	
	result = tmp1 / tmp0;
	
	//std::cout << "div " << std::hex << tmp1 << "  " << tmp0 << std::endl;

	this->data_stack.push(result);
}

void processor::exec_div_int(  )
{
	machina::arch::int_t tmp0, tmp1, result;
	
	tmp0 = this->data_stack.top();
	this->data_stack.pop();
	tmp1 = this->data_stack.top();
	this->data_stack.pop();
	
	result = tmp1 / tmp0;
	
	//std::cout << "div " << std::hex << tmp1 << "  " << tmp0 << std::endl;

	this->data_stack.push(result);
}

void processor::exec_div_long(  )
{
	machina::arch::long_t tmp0, tmp1, result;
	
	tmp0 = this->data_stack.top();
	this->data_stack.pop();
	tmp1 = this->data_stack.top();
	this->data_stack.pop();
	
	result = tmp1 / tmp0;
	
	//std::cout << "div " << std::hex << tmp1 << "  " << tmp0 << std::endl;

	this->data_stack.push(result);
}

void processor::exec_mod_byte(  )
{
	machina::arch::byte_t tmp0, tmp1, result;
	
	tmp0 = this->data_stack.top();
	this->data_stack.pop();
	tmp1 = this->data_stack.top();
	this->data_stack.pop();
	
	result = tmp1 % tmp0;
	
	//std::cout << "mod " << std::hex << tmp1 << "  " << tmp0 << std::endl;

	this->data_stack.push(result);
}

void processor::exec_mod_short(  )
{
	machina::arch::short_t tmp0, tmp1, result;
	
	tmp0 = this->data_stack.top();
	this->data_stack.pop();
	tmp1 = this->data_stack.top();
	this->data_stack.pop();
	
	result = tmp1 % tmp0;
	
	//std::cout << "mod " << std::hex << tmp1 << "  " << tmp0 << std::endl;

	this->data_stack.push(result);
}

void processor::exec_mod_int(  )
{
	machina::arch::int_t tmp0, tmp1, result;
	
	tmp0 = this->data_stack.top();
	this->data_stack.pop();
	tmp1 = this->data_stack.top();
	this->data_stack.pop();
	
	result = tmp1 % tmp0;
	
	//std::cout << "mod " << std::hex << tmp1 << "  " << tmp0 << std::endl;

	this->data_stack.push(result);
}

void processor::exec_mod_long(  )
{
	machina::arch::long_t tmp0, tmp1, result;
	
	tmp0 = this->data_stack.top();
	this->data_stack.pop();
	tmp1 = this->data_stack.top();
	this->data_stack.pop();
	
	result = tmp1 % tmp0;
	
	//std::cout << "mod " << std::hex << tmp1 << "  " << tmp0 << std::endl;

	this->data_stack.push(result);
}

void processor::exec_and_byte(  )
{
	machina::arch::byte_t tmp0, tmp1, result;
	
	tmp0 = this->data_stack.top();
	this->data_stack.pop();
	tmp1 = this->data_stack.top();
	this->data_stack.pop();
	
	result = tmp1 & tmp0;
	
	//std::cout << "and " << std::hex << tmp1 << "  " << tmp0 << std::endl;

	this->data_stack.push(result);
}

void processor::exec_and_short(  )
{
	machina::arch::short_t tmp0, tmp1, result;
	
	tmp0 = this->data_stack.top();
	this->data_stack.pop();
	tmp1 = this->data_stack.top();
	this->data_stack.pop();
	
	result = tmp1 & tmp0;
	
	//std::cout << "and " << std::hex << tmp1 << "  " << tmp0 << std::endl;

	this->data_stack.push(result);
}

void processor::exec_and_int(  )
{
	machina::arch::int_t tmp0, tmp1, result;
	
	tmp0 = this->data_stack.top();
	this->data_stack.pop();
	tmp1 = this->data_stack.top();
	this->data_stack.pop();
	
	result = tmp1 & tmp0;
	
	//std::cout << "and " << std::hex << tmp1 << "  " << tmp0 << std::endl;

	this->data_stack.push(result);
}

void processor::exec_and_long(  )
{
	machina::arch::long_t tmp0, tmp1, result;
	
	tmp0 = this->data_stack.top();
	this->data_stack.pop();
	tmp1 = this->data_stack.top();
	this->data_stack.pop();
	
	result = tmp1 & tmp0;
	
	//std::cout << "and " << std::hex << tmp1 << "  " << tmp0 << std::endl;

	this->data_stack.push(result);
}

void processor::exec_or_byte(  )
{
	machina::arch::byte_t tmp0, tmp1, result;
	
	tmp0 = this->data_stack.top();
	this->data_stack.pop();
	tmp1 = this->data_stack.top();
	this->data_stack.pop();
	
	result = tmp1 | tmp0;
	
	//std::cout << "or " << std::hex << tmp1 << "  " << tmp0 << std::endl;

	this->data_stack.push(result);
}

void processor::exec_or_short(  )
{
	machina::arch::short_t tmp0, tmp1, result;
	
	tmp0 = this->data_stack.top();
	this->data_stack.pop();
	tmp1 = this->data_stack.top();
	this->data_stack.pop();
	
	result = tmp1 | tmp0;
	
	//std::cout << "or " << std::hex << tmp1 << "  " << tmp0 << std::endl;

	this->data_stack.push(result);
}

void processor::exec_or_int(  )
{
	machina::arch::int_t tmp0, tmp1, result;
	
	tmp0 = this->data_stack.top();
	this->data_stack.pop();
	tmp1 = this->data_stack.top();
	this->data_stack.pop();
	
	result = tmp1 | tmp0;
	
	//std::cout << "or " << std::hex << tmp1 << "  " << tmp0 << std::endl;

	this->data_stack.push(result);
}

void processor::exec_or_long(  )
{
	machina::arch::long_t tmp0, tmp1, result;
	
	tmp0 = this->data_stack.top();
	this->data_stack.pop();
	tmp1 = this->data_stack.top();
	this->data_stack.pop();
	
	result = tmp1 | tmp0;
	
	//std::cout << "or " << std::hex << tmp1 << "  " << tmp0 << std::endl;

	this->data_stack.push(result);
}

void processor::exec_xor_byte(  )
{
	machina::arch::byte_t tmp0, tmp1, result;
	
	tmp0 = this->data_stack.top();
	this->data_stack.pop();
	tmp1 = this->data_stack.top();
	this->data_stack.pop();
	
	result = tmp1 ^ tmp0;
	
	//std::cout << "xor " << std::hex << tmp1 << "  " << tmp0 << std::endl;

	this->data_stack.push(result);
}

void processor::exec_xor_short(  )
{
	machina::arch::short_t tmp0, tmp1, result;
	
	tmp0 = this->data_stack.top();
	this->data_stack.pop();
	tmp1 = this->data_stack.top();
	this->data_stack.pop();
	
	result = tmp1 ^ tmp0;
	
	//std::cout << "xor " << std::hex << tmp1 << "  " << tmp0 << std::endl;

	this->data_stack.push(result);
}

void processor::exec_xor_int(  )
{
	machina::arch::int_t tmp0, tmp1, result;
	
	tmp0 = this->data_stack.top();
	this->data_stack.pop();
	tmp1 = this->data_stack.top();
	this->data_stack.pop();
	
	result = tmp1 ^ tmp0;
	
	//std::cout << "xor " << std::hex << tmp1 << "  " << tmp0 << std::endl;

	this->data_stack.push(result);
}

void processor::exec_xor_long(  )
{
	machina::arch::long_t tmp0, tmp1, result;
	
	tmp0 = this->data_stack.top();
	this->data_stack.pop();
	tmp1 = this->data_stack.top();
	this->data_stack.pop();
	
	result = tmp1 ^ tmp0;
	
	//std::cout << "xor " << std::hex << tmp1 << "  " << tmp0 << std::endl;

	this->data_stack.push(result);
}

void processor::exec_not_byte(  )
{
	machina::arch::byte_t tmp0, result;
	
	tmp0 = this->data_stack.top();
	this->data_stack.pop();
	
	result = ~tmp0;
	
	//std::cout << "not " << std::hex << tmp0 << std::endl;

	this->data_stack.push(result);
}


void processor::exec_not_short(  )
{
	machina::arch::short_t tmp0, result;
	
	tmp0 = this->data_stack.top();
	this->data_stack.pop();
	
	result = ~tmp0;
	
	//std::cout << "not " << std::hex << tmp0 << std::endl;

	this->data_stack.push(result);
}


void processor::exec_not_int(  )
{
	machina::arch::int_t tmp0, result;
	
	tmp0 = this->data_stack.top();
	this->data_stack.pop();
	
	result = ~tmp0;
	
	//std::cout << "not " << std::hex << tmp0 << std::endl;

	this->data_stack.push(result);
}


void processor::exec_not_long(  )
{
	machina::arch::long_t tmp0, result;
	
	tmp0 = this->data_stack.top();
	this->data_stack.pop();
	
	result = ~tmp0;
	
	//std::cout << "not " << std::hex << tmp0 << std::endl;

	this->data_stack.push(result);
}


void processor::exec_swap(  )
{
	machina::arch::long_t tmp0, tmp1;
	
	tmp0 = this->data_stack.top();
	this->data_stack.pop();
	tmp1 = this->data_stack.top();
	this->data_stack.pop();
	
	//std::cout << "swap " << std::hex << tmp1 << "  " << tmp0 << std::endl;
	
	this->data_stack.push(tmp0);
	this->data_stack.push(tmp1);
}

void processor::exec_dup(  )
{
	machina::arch::long_t tmp0;
	
	tmp0 = this->data_stack.top();
	this->data_stack.pop();
	
	//std::cout << "dup " << std::hex << tmp0 << std::endl;
	
	this->data_stack.push(tmp0);
	this->data_stack.push(tmp0);
}

void processor::exec_rol(  )
{
	machina::arch::long_t tmp0, tmp1, tmp2;
	
	tmp0 = this->data_stack.top();
	this->data_stack.pop();
	tmp1 = this->data_stack.top();
	this->data_stack.pop();
	tmp2 = this->data_stack.top();
	this->data_stack.pop();
	
	//std::cout << "rol " << std::hex << tmp0 << " " << tmp1 << "  " << tmp2 << std::endl;
	
	this->data_stack.push(tmp0);
	this->data_stack.push(tmp2);
	this->data_stack.push(tmp1);
}

void processor::exec_roln( machina::arch::size_t n )
{
	machina::arch::long_t *tmpn = new machina::arch::long_t[n];
	
	for(machina::arch::size_t i = 0; i < n; i++)
	{
		tmpn[i] = this->data_stack.top();
		this->data_stack.pop();
	}
	
	//std::cout << "roln " << std::hex << tmpn[0] << " ";
	
	this->data_stack.push(tmpn[0]);
	
	for(machina::arch::size_t i = (n-1); i > 0; i--)
	{
		//std::cout << tmpn[i] << " ";
		
		this->data_stack.push(tmpn[i]);
	}
	
	//std::cout << std::endl;
	
	delete tmpn;
}

 
void processor::exec_frame( machina::arch::size_t size )
{
	//std::cout << "frame " << std::dec << size << std::endl;
	
	for(machina::arch::size_t n = 0; n < size; n++)
	{
		this->call_stack.push(machina::arch::null);
	}
}

void processor::exec_obtain( machina::arch::size_t index )
{
	//std::cout << "obtain " << std::dec << index << std::endl;
	
	std::stack<machina::arch::pointer_t> tmp_stack;
	
	for(machina::arch::size_t n = 0; n < index; n++)
	{
		tmp_stack.push(this->call_stack.top());
		this->call_stack.pop();
	}
	
	this->data_stack.push(this->call_stack.top());
	
	for(machina::arch::size_t n = 0; n < index; n++)
	{
		this->call_stack.push(tmp_stack.top());
		tmp_stack.pop();
	}
}

void processor::exec_place( machina::arch::size_t index )
{
	//std::cout << "place " << std::dec << index << std::endl;
	
	std::stack<machina::arch::pointer_t> tmp_stack;
	
	for(machina::arch::size_t n = 0; n < index; n++)
	{
		tmp_stack.push(this->call_stack.top());
		this->call_stack.pop();
	}
	
	this->call_stack.top() = this->data_stack.top();
	this->data_stack.pop();
	
	for(machina::arch::size_t n = 0; n < index; n++)
	{
		this->call_stack.push(tmp_stack.top());
		tmp_stack.pop();
	}
}

void processor::exec_cleanup( machina::arch::size_t size )
{
	//std::cout << "cleanup " << std::dec << size << std::endl;
	
	for(machina::arch::size_t n = 0; n < size; n++)
	{
		this->call_stack.pop();
	}
}


void processor::exec_jmp( machina::arch::pointer_t address )
{
	//std::cout << "jmp " << std::hex << address << std::endl;

	this->ip = address;
}

void processor::exec_jmpz( machina::arch::pointer_t address )
{
	//std::cout << "jmpz " << std::hex << address << std::endl;
	
	machina::arch::long_t tmp0;
	
	tmp0 = this->data_stack.top();
	this->data_stack.pop();
	
	if(tmp0 == 0)
	{
		this->ip = address;
	}
	else
	{
		this->next(machina::instruction_multibyte);
	}
}

void processor::exec_jmpnz( machina::arch::pointer_t address )
{
	//std::cout << "jmpnz " << std::hex << address << std::endl;
	
	machina::arch::long_t tmp0;
	
	tmp0 = this->data_stack.top();
	this->data_stack.pop();
	
	if(tmp0 != 0)
	{
		this->ip = address;
	}
	else
	{
		this->next(machina::instruction_multibyte);
	}
}

void processor::exec_jmplz( machina::arch::pointer_t address )
{
	//std::cout << "jmplz " << std::hex << address << std::endl;

	machina::arch::long_t tmp0;
	
	tmp0 = this->data_stack.top();
	this->data_stack.pop();
	
	if(tmp0 < 0)
	{
		this->ip = address;
	}
	else
	{
		this->next(machina::instruction_multibyte);
	}
}

void processor::exec_jmpgz( machina::arch::pointer_t address )
{
	//std::cout << "jmpgz " << std::hex << address << std::endl;

	machina::arch::long_t tmp0;
	
	tmp0 = this->data_stack.top();
	this->data_stack.pop();
	
	if(tmp0 > 0)
	{
		this->ip = address;
	}
	else
	{
		this->next(machina::instruction_multibyte);
	}
}

void processor::exec_jmpeq( machina::arch::pointer_t address )
{
	//std::cout << "jmpeq " << std::hex << address << std::endl;

	machina::arch::long_t tmp0, tmp1;
	
	tmp0 = this->data_stack.top();
	this->data_stack.pop();
	tmp1 = this->data_stack.top();
	this->data_stack.pop();
	
	if(tmp0 == tmp1)
	{
		this->ip = address;
	}
	else
	{
		this->next(machina::instruction_multibyte);
	}
}

void processor::exec_jmpneq( machina::arch::pointer_t address )
{
	//std::cout << "jmpneq " << std::hex << address << std::endl;

	machina::arch::long_t tmp0, tmp1;
	
	tmp0 = this->data_stack.top();
	this->data_stack.pop();
	tmp1 = this->data_stack.top();
	this->data_stack.pop();
	
	if(tmp0 != tmp1)
	{
		this->ip = address;
	}
	else
	{
		this->next(machina::instruction_multibyte);
	}
}
				
void processor::exec_call(  )
{
	machina::arch::pointer_t address;
	
	address = this->data_stack.top();
	this->data_stack.pop();
	
	//std::cout << "call " << std::hex << address << std::endl;
	
	this->call_stack.push(this->ip + machina::instruction_byte);
	this->ip = address;
}
				
void processor::exec_call( machina::arch::pointer_t address )
{
	//std::cout << "call " << std::hex << address << std::endl;

	this->call_stack.push(this->ip + machina::instruction_multibyte);
	this->ip = address;
}
				
void processor::exec_ret(  )
{
	//std::cout << "ret to " << std::hex << this->call_stack.top() << std::endl;

	this->ip = this->call_stack.top();
	this->call_stack.pop();
}

void processor::exec_out(  )
{
	machina::arch::byte_t tmp0 = this->data_stack.top();
	this->data_stack.pop();
	
	fputc(tmp0, stdout);
}

void processor::exec_halt(  )
{
	//std::cout << "halt" << std::endl;
	
	this->status |= processor::halted;
}