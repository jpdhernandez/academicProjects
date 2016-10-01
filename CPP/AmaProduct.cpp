#include "AmaProduct.h"
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;
namespace sict
{
	AmaProduct::AmaProduct(const char filetag) : fileTag_(filetag){}

	const char* AmaProduct::unit()const
	{
		return unit_;
	}

	void AmaProduct::unit(const char* value)
	{
		strncpy(unit_, value, 11);
		unit_[11] = 0;
	}

	fstream& AmaProduct::store(fstream& file, bool addNewLine)const
	{
		if (file.is_open())
		{
			file << fileTag_ << ',' << sku() << ','
				 << name() << ',' << price() << ','
				 << taxed() << ',' << quantity() << ','
				 << unit() << ',' << qtyNeeded();
			if (addNewLine == true) file << endl;
		}
		return file;
	}

	fstream& AmaProduct::load(fstream& file)
	{
		double temp_price;
		int temp_taxed;
		int temp_quantity;
		int temp_qtyNeeded;
		char temp_sku[MAX_SKU_LEN + 1];
		char temp_name[256];
		char temp_unit[11];
		if (file.is_open())
		{
				file.getline(temp_sku, MAX_SKU_LEN + 1, ',');
				file.getline(temp_name, 256, ',');
				file >> temp_price;
				file.ignore();
				file >> temp_taxed;
				file.ignore();
				file >> temp_quantity;
				file.ignore();
				file.getline(temp_unit, 11, ',');
				file >> temp_qtyNeeded;
				file.ignore();

				sku(temp_sku);
				name(temp_name);
				price(temp_price);
				taxed(temp_taxed);
				quantity(temp_quantity);
				unit(temp_unit);
				qtyNeeded(temp_qtyNeeded);
		}
		return file;
	}

	ostream& AmaProduct::write(ostream& os, bool linear)const
	{
		if (!err_.isClear())
		{
			os << err_.message();
		}
		else
		{
			if (linear == true)
			{
				os << setfill(' ') << left << setw(MAX_SKU_LEN) << sku() << '|'
					<< setw(20) << name() << '|'
					<< right << fixed << setprecision(2) << setw(7) << cost() << '|'
					<< setw(4) << quantity() << '|'
					<< left << setw(10) << unit() << '|'
					<< right << setw(4) << qtyNeeded() << '|';
			}
			else if (linear == false)
			{
				if (taxed() > 0)
				{
					os << "Sku: " << sku() << endl;
					os << "Name: " << name() << endl;
					os << "Price: " << price() << endl;
					os << "Price after tax: " << cost() << endl;
					os << "Quantity On Hand: " << quantity() << " " << unit() << endl;
					os << "Quantity Needed: " << qtyNeeded();
				}
				else
				{
					os << "Sku: " << sku() << endl;
					os << "Name: " << name() << endl;
					os << "Price: " << price() << endl;
					os << "Price after tax: N/A" << endl;
					os << "Quantity On Hand: " << quantity() << " " << unit() << endl;
					os << "Quantity Needed: " << qtyNeeded();
				}
			}
		}
		return os;
	}


	istream& AmaProduct::read(istream& is)
	{
		double temp_price;
		char temp_taxed;
		int temp_quantity;
		int temp_qtyNeeded;
		char temp_sku[MAX_SKU_LEN + 1];
		char temp_name[256];
		cout << "Sku: ";
		is >> temp_sku;
		cout << "Name: ";
		is >> temp_name;
		cout << "Unit: ";
		is >> unit_;
		cout << "Taxed? (y/n): ";
		is.ignore(2000, '\n');
		is >> temp_taxed;
		if (temp_taxed != 'Y' && temp_taxed != 'y' && temp_taxed != 'N' && temp_taxed != 'n')
		{
			err_.message("Only (Y)es or (N)o are acceptable");
			is.setstate(ios::failbit);
			cout << "Price: ";
		}
		else
		{
			is.clear();
			cout << "Price: ";
			is >> temp_price;
			if (is.fail())
			{
				err_.message("Invalid Price Entry");
				is.setstate(ios::failbit);
			}
			else
			{
				cout << "Quantity On hand: ";
				is >> temp_quantity;
				if (is.fail())
				{
					err_.message("Invalid Quantity Entry");
					is.setstate(ios::failbit);
				}
				else
				{
					cout << "Quantity Needed: ";
					is >> temp_qtyNeeded;
					if (is.fail())
					{
						err_.message("Invalid Quantity Needed Entry");
						is.setstate(ios::failbit);
					}
					else
					{
						sku(temp_sku);
						name(temp_name);
						price(temp_price);
						temp_taxed == 'y' || temp_taxed == 'Y' ? taxed(true) : taxed(false);
						quantity(temp_quantity);
						qtyNeeded(temp_qtyNeeded);
						err_.clear();
					}
				}
			}
		}
		return is;
	}
	
}