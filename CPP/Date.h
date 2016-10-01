// Final Project Milestone 1
// File: Date.h
// Description: A header file for Date.cpp whcih contains the class declaration
// Student: Julian Philip Hernandez; 036054120; jphernandez2
// Class desc: Holds the expiry date of the perishable items

#ifndef SICT_DATE_H__
#define SICT_DATE_H__
#include <iostream>
// The possible values for variable readErrorCode_
#define NO_ERROR 0    // No error the date is valid
#define CIN_FAILED 1  // istream failed when entering information
#define YEAR_ERROR 2  // Year value is invalid
#define MON_ERROR 3   // Month value is invalid
#define DAY_ERROR 4   // Day value is invalid

namespace sict
{
  class Date
  {
  private:
	  int year_;           // Holds the year; a four digit integer between MIN_YEAR and MAX_YEAR, defined in “general.h”
	  int mon_;            // Month of the year, between 1 to 12
	  int day_;            // Day of the month, note that in a leap year February is 29 days, (see mday() member function) 
	  int readErrorCode_;  // This variable holds an error code that tells whether date value is valid/ not, and which part is erroneous if so. 
	  int value()const;    
	  void errCode(int errorCode);
  public:
	  Date();
	  Date(int year, int month, int day);
	  
	  int mdays()const;
	  void setEmpty();

	  // These operators return the comparison result of the return value of the value() function applied
	  // to left and right operands (The Date objects on the left and right side of the operators).
	  // For example operator< returns true if this->value() is less than D.value() or else it returns false.
	  bool operator==(const Date& D)const;
	  bool operator!=(const Date& D)const;
	  bool operator<(const Date& D)const;
	  bool operator>(const Date& D)const;
	  bool operator<=(const Date& D)const;
	  bool operator>=(const Date& D)const;

	  // Queries:
	  int errCode() const;
	  bool bad()const;

	  // IO methods:
	  std::istream& read(std::istream& istr);
	  std::ostream& write(std::ostream& ostr)const;
  };
  
  // Helper overloads:
  std::istream& operator>>(std::istream& istr, Date& date);
  std::ostream& operator<<(std::ostream& ostr, const Date& date);
}
#endif