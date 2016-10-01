// Final Project Milestone 2
// File	ErrorMessage.h
// Version 1.0
// Date	10/Mar/2016
// Author	Fardad Soleimanloo
// Student Julian Philip Hernandez; 036054120; jphernandez2
// Description
// This is the header  file for the ErrorMessage Class
#ifndef SICT_ERRORMESSAGE_H__
#define SICT_ERRORMESSAGE_H__
#include <iostream>
namespace sict
{
	class ErrorMessage
	{
		char* message_;
		
	public:
		ErrorMessage();
		ErrorMessage(const char* errorMessage);

		// A deleted copy constructor to prevents an ErrorMessage object from being copied
		ErrorMessage(const ErrorMessage& em) = delete;
		// A delted assignment operator overload to prevent an ErrorMessage obj from being assigned to another
		ErrorMessage& operator=(const ErrorMessage& em) = delete;
		
		ErrorMessage& operator=(const char* errorMessage);
		virtual ~ErrorMessage();
		void clear();
		bool isClear() const;
		void message(const char* value);
		const char* message()const;
	};

	// helper operator
	std::ostream& operator<<(std::ostream& ostr, ErrorMessage& em);
}
#endif

