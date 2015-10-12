#include "include/machina.hpp"
#include "include/binary.hpp"

#include <iostream>
#include <fstream>

#include <ctime>
#include <cstring>
#include <cstdio>

int main( int argc, char *argv[] )
{
	/**
	  * Parse the command line
	  */ 
	const char *image_file = nullptr, *dump_file = nullptr;
	
	bool info = false, verify = false, run = false, dump = false;
	
	for(int index = 1; index < argc; index++)
	{
		if(!strcmp(argv[index], "--image"))
		{
			image_file = argv[++index];
		}
		else if(!strcmp(argv[index], "--info"))
		{
			info = true;
		}
		else if(!strcmp(argv[index], "--verify"))
		{
			verify = true;
		}
		else if(!strcmp(argv[index], "--run"))
		{
			run = true;
		}
		else if(!strcmp(argv[index], "--dump"))
		{
			dump = true;
		}
		else if(!strcmp(argv[index], "--dumpfile"))
		{
			dump_file = argv[++index];
		}
		else if(!strcmp(argv[index], "--about"))
		{
			std::cout << "Machina - Virtual Machine - Bytecode Interpreter" << std::endl;
			std::cout << "Machina is a virtual machine based on a simple stack machine" << std::endl << std::endl;
			
			std::cout << "Supported command line options: " << std::endl;
			std::cout << "  --image [file]    Specify the program image to load" << std::endl;
			std::cout << "  --info            Print the info data read from the program image" << std::endl;
			std::cout << "  --verify          Verify the program image" << std::endl;
			std::cout << "  --run             Load an run the program from the image" << std::endl;
			std::cout << "  --dump            Give a machine dump after program execution" << std::endl;
			std::cout << "  --dumpfile [file] Specify the file the dump is written to (if not specified the dump goes to stdout)" << std::endl;
			std::cout << "  --about           Prints this text" << std::endl;

			std::cout << std::endl << "'Cui ergo ista didici?' Non est quod timeas, ne operam perdideris, si tibi didicisti. (Seneca ep. 7)" << std::endl;
			
			exit(0);
		}
		else
		{
			std::cerr << "Error: unrecognized command line option " << argv[index] << std::endl;
			exit(1);
		}
	}
	
	if(!image_file)
	{
		std::cerr << "Error: no program image specified" << std::endl;
		exit(1);
	}
	
	if(info)
	{
		/**
		  * Read the program image from file
		  */ 
		std::ifstream file(image_file, std::ifstream::in);
		
		if(file.fail())
		{
			std::cerr << "Error: " << image_file << ": No such file or directory" << std::endl;
			exit(1);
		}
		
		file.seekg(0, file.end);
		machina::arch::size_t size = file.tellg();
		file.seekg(0, file.beg);
		
		char *image = new char[size];
		
		file.read(image, size);
		file.close();
		
		if(image)
		{
			/**
			  * Get the info structure
			  */ 
			machina::binary::info *program_info = machina::binary::read_info(image);
			
			std::cout << "Program information (" << image_file << ")" << std::endl;
			std::cout << "  Author:       " << program_info->author << std::endl;
			std::cout << "  Project:      " << program_info->project << std::endl;
			std::cout << "  Version:      " << program_info->version << std::endl;
			std::cout << "  Description:  " << program_info->description << std::endl;
			
			/**
			  * Get the program footer for build-time
			  */ 
			machina::binary::footer *program_footer = machina::binary::read_footer(image);
			
			std::cout << std::endl << "  The program was built at " << ctime(&(program_footer->time)) << std::endl;
		}
		
		delete[] image;
	}
	
	if(verify)
	{
		/**
		  * Read the program image from file
		  */ 
		std::ifstream file(image_file, std::ifstream::in);
		
		if(file.fail())
		{
			std::cerr << "Error: " << image_file << ": No such file or directory" << std::endl;
			exit(1);
		}
		
		file.seekg(0, file.end);
		machina::arch::size_t size = file.tellg();
		file.seekg(0, file.beg);
		
		char *image = new char[size];
		
		file.read(image, size);
		file.close();
		
		std::cout << "Verifying program image (" << image_file << ")" << std::endl;
		
		if(image && machina::binary::check(image) && machina::binary::verify(image))
		{
			/**
			  * Get the program footer for build-time
			  */ 
			machina::binary::footer *program_footer = machina::binary::read_footer(image);
			
			std::cout << "  Magic string and checksum correct, the image is a valid machina program image." << std::endl;
			std::cout << "  Checksum: " << program_footer->checksum << std::endl;
		}
		else
		{
			std::cout << "  The image could not be verified" << std::endl;
			exit(1);
		}
		
		std::cout << std::endl;
		
		delete[] image;
	}
	
	if(run)
	{
		/**
		  * Instance of 'machina' virtual machine 
		  */ 
		machina::virtual_machine vm;
			
		/**
		  * Load program
		  */ 
		vm.load(image_file);
		
		/**
		  * Dump to stdout
		  */ 
		if(dump && !dump_file)
		{
			/**
			  * Dump the machine state
			  */ 
			vm.dump(stdout);
			vm.trace(stdout);
		}
		else if(dump && dump_file)
		{
			FILE *file = fopen(dump_file, "w");
			
			/**
			  * Dump the machine state
			  */ 
			vm.dump(file);
			vm.trace(file);
			
			fclose(file);
		}
	}

	return 0;
}
