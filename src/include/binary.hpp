#ifndef MACHINA_BINARY_HPP
#define MACHINA_BINARY_HPP

#include "arch.hpp"

#include <ctime>

namespace machina
{
	namespace binary
	{
		/**
		  * @brief	Structure describing the file header of an executable binary
		  */ 
		struct header
		{
			/**
			  * @brief	The magic number
			  */
			char				magic[8] 	= { 'M', 'V', 'S', 'M', '|', 'B', 'I', 0x0 };
	
			/**
			  * @brief	Meta information
			  */
			char				meta1[7] 	= { 'H', 'E', 'A', 'D', 'E', 'R', 0x0 };

			/**
			  * @brief	Meta information
			  */
			char				meta2[5]	= { 'S', 'I', 'Z', 'E', 0x0 };

			/**
			  * @brief	The size of the code + data section
			  */
			machina::arch::size_t		size;

			/**
			  * @brief	Meta information
			  */
			char				meta3[6]	= { 'E', 'N', 'T', 'R', 'Y', 0x0 };
			
			/**
			  * @brief	The program entry point
			  */
			machina::arch::pointer_t	entry;
			
			/**
			  * @brief	Meta information
			  */
			char				meta4[7]	= { 'O', 'F', 'F', 'S', 'E', 'T', 0x0 };
			
			/**
			  * @brief	The offset of the code + data section within the binary
			  */
			machina::arch::pointer_t	offset;
		} __attribute__((packed));
		
		/**
		  * @brief	 Structure describing the information structure of an executable binary
		  */
		struct info
		{
			/**
			  * @brief	Meta information
			  */
			char				meta1[5]	= { 'I', 'N', 'F', 'O', 0x0 };
			
			/**
			  * @brief	Meta information
			  */
			char				meta2[7]	= { 'A', 'U', 'T', 'H', 'O', 'R', 0x0 };
			
			/**
			  * @brief	The program author
			  */
			char				author[24];
			
			/**
			  * @brief	Meta information
			  */
			char				meta3[8]	= { 'P', 'R', 'O', 'J', 'E', 'C', 'T', 0x0 };
			
			/**
			  * @brief	The project name
			  */
			char				project[24];
			
			/**
			  * @brief	Meta information
			  */
			char				meta4[8]	= { 'V', 'E', 'R', 'S', 'I', 'O', 'N', 0x0 };
			
			/**
			  * @brief	The program version
			  */
			char				version[12];
			
			/**
			  * @brief	Meta information
			  */
			char				meta5[12]	= { 'D', 'E', 'S', 'C', 'R', 'I', 'P', 'T', 'I', 'O', 'N', 0x0 };
			
			/**
			  * @brief	Short program description
			  */
			char				description[160];
		} __attribute__((packed));
		
		/**
		  * @brief	Structure describing the file footer of an executable binary 
		  */
		struct footer
		{
			/**
			  * @brief	Meta information
			  */
			char				meta1[7]	= { 'F', 'O', 'O', 'T', 'E', 'R', 0x0 };

			/**
			  * @brief	Meta information
			  */
			char				meta2[5]	= { 'T', 'I', 'M', 'E', 0x0 };

			/**
			  * @brief	The build-time
			  */
			time_t				time;
			
			/**
			  * @brief	Meta information
			  */
			char				meta3[9]	= { 'C', 'H', 'E', 'C', 'K', 'S', 'U', 'M', 0x0 };
			
			/**
			  * @brief	The image checksum
			  */
			machina::arch::size_t		checksum;
		} __attribute__((packed));
		
		/**
		  * @brief	Checks whether the image is an machina program image
		  * 
		  * @param	image		The image to check
		  * @return			true if the image is an machina program image
		  */ 
		bool check( const char *image );
		
		/**
		  * @brief	Verifies the program image (computes the checksum)
		  * 
		  * @param	image		The image to verify
		  * @return			true if the image is verified
		  */ 
		bool verify( const char *image );
		
		/**
		  * @brief	Reads the header of a program image
		  * 
		  * @param	image		The image
		  * @return			Pointer to the header within image
		  */
		machina::binary::header *read_header( const char *image );
		
		/**
		  * @brief	Reads the information structure of a program image
		  * 
		  * @param	image		The image
		  * @return			Pointer to the info structure within image
		  */
		machina::binary::info *read_info( const char *image );
		
		/**
		  * @brief	Reads the footer of a program image
		  * 
		  * @param	image		The image
		  * @return			Pointer to the footer within image
		  */
		machina::binary::footer *read_footer( const char *image );
		
		/**
		  * @brief	Reads the program from a program image
		  * 
		  * @param	image		The image
		  * @return			Pointer to the program (code+data) within image
		  */
		machina::arch::opcode_t *read_program( const char *image );
	}
}

#endif