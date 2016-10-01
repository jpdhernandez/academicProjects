// Final Project Milestone 1
// File: Date.cpp
// Description: A implementation file for Date.cpp whcih contains the class definition
// Student: Julian Philip Hernandez; 036054120; jphernandez2
// CLASS DESCRIPTION:
//   The date class encapsulates a date vlaue in three integers for year, month and day,
//   and is readable in istreams and printable by ostream using the following formate for
//   both reading and writing:   YYYY/MM/DD

#include <iomanip>
#include <iostream>
#include <fstream>
using namespace std;
#include "Date.h"
#include "general.h"
#include <cstring>
namespace sict{

	// Default constructor that sets object to safe empty state
	Date::Date()
	{
		setEmpty();
	}

	// Three arg constructor that sets values of object attributes
	Date::Date(int year, int month, int day)
	{
		year_ = year;
		mon_ = month;
		day_ = day;
		errCode(NO_ERROR);
	}

	// Sets attributes to safe empty state
	void Date::setEmpty()
	{
		year_ = 0;
		mon_ = 0;
		day_ = 0;
		errCode(NO_ERROR);
	}

	// Sets the readErrorCode_ value
	void Date::errCode(int errorCode) 
	{
		if (errorCode >= 0 && errorCode <= 4)
		readErrorCode_ = errorCode;
	}

	// Query that rturns the value of readErrorCode;
	int Date::errCode() const
	{
		return readErrorCode_;
	}
	// Query that returns true if errCode() != 0
	bool Date::bad()const
	{
		return readErrorCode_;
	}
	
	// This function returns a unique int based on the date
	// The value is used to compare two dates
	// If the value() of the date is larger than two,
	// then the date one is after date two
	int Date::value()const
	{
		return year_ * 372 + mon_ * 31 + day_;
	}

	// This function returns the number of days in a month
	int Date::mdays()const
	{
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int mon = mon_ >= 1 && mon_ <= 12 ? mon_ : 13;
		mon--;
		return days[mon] + int((mon == 1)*((year_ % 4 == 0) && (year_ % 100 != 0)) || (year_ % 400 == 0));
	}

	// Reads the date is following format: YYYY?MM?DD (e.g. 2016/03/24 or 2016-03-24) from the console
	// This function will not prompt the user. If the istream (istr) fails at any point, it will set 
	// the readErrorCode_ to CIN_FAILED and will NOT clear the istream object. If the numbers are 
	// successfully read in, it will validate them to be in range, in the order of year, month and day
	// (see general header-file and mday() method for acceptable ranges for years and days respectively
	// Month can be between 1 and 12 inclusive). If any of the numbers is not in range, it will set the 
	// readErrorCode_ to the appropriate error code and stop further validation. . Irrespective of the 
	// result of the process, this function will return the incoming istr argument. 
	istream& Date::read(istream& istr)
	{
	/*	istr >> year_;
		istr.ignore();
		istr >> mon_; 
		istr.ignore();  
		istr >> day_;
		istr.ignore(1000,'\n');*/
		char sep;
		istr >> year_ >> sep >> mon_ >> sep >> day_;
		if (istr.fail())
		{
			errCode(CIN_FAILED);
		}
		else if (year_ < MIN_YEAR || year_ > MAX_YEAR) 
		{
			errCode(YEAR_ERROR);
		}
		else if (mon_ > 12 || mon_ < 0)
		{
			errCode(MON_ERROR);
		}
		else if (day_ > mdays() || mdays() < 1)
		{
			errCode(DAY_ERROR);
		}
		return istr;
	}

	// Prints out the date in the following format: YYYY/MM/DD
	ostream& Date::write(ostream& ostr) const
	{
		ostr << year_ << "/" << setw(2) << setfill('0') << mon_ << "/" << setw(2) << day_;
		return ostr;
	}

	// Helper extraction operator overload that reads the date from the console
	istream& operator>>(istream& istr, Date& date)
	{
		date.read(istr);
		return istr;
	}

	// Helper insertion operator overlaod that prints the date into the console
	ostream& operator<<(ostream& ostr, const Date& date)
	{
		date.write(ostr);
		return ostr;
	}

	// Overloaded comparison operators; see Date.h for details
	bool Date::operator==(const Date& D)const
	{
		return this->value() == D.value();
	}
	bool Date::operator!=(const Date& D)const
	{
		return this->value() != D.value();
	}
	bool Date::operator<(const Date& D)const
	{
		return this->value() < D.value();
	}
	bool Date::operator>(const Date& D)const
	{
		return this->value() > D.value();
	}
	bool Date::operator<=(const Date& D)const
	{
		return this->value() <= D.value();
	}
	bool Date::operator>=(const Date& D)const
	{
		return this->value() >= D.value();
	}
}
