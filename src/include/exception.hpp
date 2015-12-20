#ifndef MACHINA_EXCEPTION_HPP
#define MACHINA_EXCEPTION_HPP

/**
  * @brief  Namespace of 'machina'
  */
namespace machina 
{
	/**
	  * @brief	Namspace containing exceptions
	  */ 
	namespace exception
	{
		/**
		  * @brief	Invalid-opcode-exception
		  */ 
		struct invalid_opcode
		{
			/**
			  * @brief	Message containing information on the exception
			  */
			std::string message;
		};
		
		/**
		  * @brief	Double-free-exception
		  */
		struct double_free
		{
			/**
			  * @brief	Message containing information on the exception
			  */
			std::string message;
		};
		
		/**
		  * @brief	Corrupted-memory-exception
		  */
		struct corrupted_memory
		{
			/**
			  * @brief	Message containing information on the exception
			  */
			std::string message;
		};
		
		/**
		  * @brief	Out-of-exception
		  */
		struct out_of_memory
		{
			/**
			  * @brief	Message containing information on the exception
			  */
			std::string message;
		};
		
		/**
		  * @brief	Invalid-address-exception
		  */
		struct invalid_address
		{
			/**
			  * @brief	Message containing information on the exception
			  */
			std::string message;
		};
	}
}

#endif