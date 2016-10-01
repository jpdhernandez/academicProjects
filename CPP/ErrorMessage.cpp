// Final Project Milestone 2
// File	ErrorMessage.cpp
// Version 1.0
// Date	10/Mar/2016
// Author	Fardad Soleimanloo
// Student Julian Philip Hernandez; 036054120; jphernandez2
// Description
// This is the implementation file for the ErrorMessage Class
#include "ErrorMessage.h"
#include <cstring>
using namespace std;
namespace sict
{	
	// A default constructor that sets attribute to nullptr
	ErrorMessage::ErrorMessage()
	{
		message_ = nullptr;
	}

	// A constructor that sets the attribute to nullptr and uses message() setter
	// to set the class attribute to the value of the errorMessage argument
	ErrorMessage::ErrorMessage(const char* errorMessage)
	{
		message_ = nullptr;
		message(errorMessage);
	}

	// Overloaded assignment operator that sets the message_ to the value of errorMessage arg
	// and returns current object (*this) by calling the clear() and message() functions
	ErrorMessage& ErrorMessage::operator=(const char* errorMessage)
	{
		if (errorMessage != nullptr)
		{
			clear();
			message(errorMessage);
		}
		return *this;
	}

	// Destructor that takes care of de-allocating the memory pointed by message_
	ErrorMessage::~ErrorMessage()
	{
		delete[] message_;
	}

	// De-allocates the memory pointed by message_ and thens ets message) to nullptr
	void ErrorMessage::clear()
	{
		delete[] message_;
		message_ = nullptr;
	}

	// Returns true if message_ == nullptr
	bool ErrorMessage::isClear() const
	{
		return message_ == nullptr;
	}

	// A function that sets the message_ attribute of the ErrorMessage class to a new value
	// it de-allocs the memmory pointed by message_
	// allocs memory to the same length of value + 1 ekeping the address in message_
	// copies the value c-string into message_
	void ErrorMessage::message(const char* value)
	{
		int size = strlen(value) + 1;
		if (value != nullptr)
		{
			delete[] message_;
			message_ = new char[size];
			strcpy(message_, value); // Or strncpy
		}
	}
	
	// Getter function for message_ attribute
	const char* ErrorMessage::message()const
	{
		return message_;
	}

	// Overloaded insertion operator so that ErrorMessage class can be printed using cout
	// if ErrorMessage isClear(), nothing should be printed, otherwise it prints message_
	std::ostream& operator<<(std::ostream& ostr, ErrorMessage& em)
	{
		em.isClear() ? ostr << "" : ostr << em.message();
		return ostr;
	}
}
