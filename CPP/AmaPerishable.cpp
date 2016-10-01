#include "AmaPerishable.h"
#include <fstream>
using namespace std;
namespace sict
{
	AmaPerishable::AmaPerishable(): AmaProduct('P') {}

	const Date& AmaPerishable::expiry()const
	{
		return expiry_;
	}

	void AmaPerishable::expiry(const Date &value)
	{
		expiry_ = value;
	}


	fstream& AmaPerishable::store(fstream& file, bool addNewLine)const
	{
		AmaProduct::store(file, false);
		file << ',';
		file << expiry() << endl;
		return file;
	}

	fstream& AmaPerishable::load(fstream& file)
	{
		AmaProduct::load(file);
		expiry_.read(file);
		file.ignore();
		return file;
	}

	ostream& AmaPerishable::write(ostream& ostr, bool linear)const
	{
		AmaProduct::write(ostr, linear);
		if (err_.isClear() && !Product::isEmpty())
		{
			linear == true ? ostr << expiry() : ostr << endl << "Expiry date: " << expiry();
		}
		return ostr;
	}

	istream& AmaPerishable::read(istream& istr)
	{
		AmaProduct::read(istr);
		Date tempDate;
		if (err_.isClear())
		{
			cout << "Expiry date (YYYY/MM/DD): ";
			tempDate.Date::read(istr);
			if (tempDate.errCode() == CIN_FAILED)
			{
				err_.message("Invalid Date Entry");
				istr.setstate(ios::failbit);
			}
			else if (tempDate.errCode() == YEAR_ERROR)
			{
				err_.message("Invalid Year in Date Entry");
				istr.setstate(ios::failbit);
			}
			else if (tempDate.errCode() == MON_ERROR)
			{
				err_.message("Invalid Month in Date Entry");
				istr.setstate(ios::failbit);
			}
			else if (tempDate.errCode() == DAY_ERROR)
			{
				err_.message("Invalid Day in Date Entry");
				istr.setstate(ios::failbit);
			}
			expiry(tempDate);
		}
		return istr;
	}
}
