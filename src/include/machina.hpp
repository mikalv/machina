#ifndef MACHINA_HPP
#define MACHINA_HPP

#include "arch.hpp"
#include "memory.hpp"
#include "processor.hpp"

#include <cstdio>

/**
  * @brief  Namespace of 'machina'
  */ 
namespace machina
{
	/**
	  * @brief	Class describing the entire Virtual Machine 
	  */
	class virtual_machine
	{
		public:
			/**
			  * @brief	The default constructor
			  */ 
			virtual_machine(  );
			
			/**
			  * @brief	The default destructor
			  */ 
			~virtual_machine(  );
			
			/**
			  * @brief	Loads an image into the virtual machine 
			  * 
			  * @param	image		Pointer to memory containing the image
			  * @param	size		The size of the image
			  * @param	entry		The entry Point for the execution
			  */
			void load( machina::arch::opcode_t *image, machina::arch::size_t size, machina::arch::pointer_t entry );
			
			/**
			  * @brief	Loads a program for execution
			  *
			  * @param	path		Path to the file containing the program
			  */ 
			void load( const char *path );
			
			/**
			  * @brief	Resets the virtual machine
			  */ 
			void reset(  );
			
			/**
			  * @brief	Dumps the machine state
			  * 
			  * @param	output		Filestream used for output
			  */ 
			void dump( FILE *output );
			
			/**
			  * @brief	Dumps a call/stack trace
			  * 
			  * @param	output		Filestream used for output
			  */
			void trace( FILE *output );
		private:
			/**
			  * @brief	The memory of the virtual machine
			  */ 
			machina::memory		*memory;
			
			/**
			  * @brief	The processor of the virtual machine
			  */ 
			machina::processor	*processor;
	};
}

#endif
