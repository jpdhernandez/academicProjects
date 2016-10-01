// Final Project Milestone 4
// File	Product.h
// Date	2016-Mar-19
// Author	Fardad Soleimanloo
// Student Julian Philip Hernandez; 036054120; jphernandez2
#include "Product.h"
#include <iostream>
#include <cstring>

namespace sict
{
	// Sets all attributes to safe reconizable empty state
	Product::Product():name_(nullptr),price_(0), taxed_(false), quantity_(0), qtyNeeded_(0)
	{
		sku(nullptr);
	}

	Product::Product(const char* s, const char* n, double p , int qN , bool t)
	{
		if (s && n)
		{
			sku(s);
			name(n);
			quantity(0);
			price(p);
			qtyNeeded(qN);
			taxed(t);
		}
	}

	void Product::copy(const Product& P)
	{
		if (!P.isEmpty())
		{
			sku(P.sku());
			price(P.price());
			taxed(P.taxed());
			quantity(P.quantity());
			qtyNeeded(P.qtyNeeded());
			name(P.name());
		}
	}

	Product::Product(const Product& P)
	{
		name(nullptr);
		copy(P);
	}

	Product& Product::operator=(const Product& P)
	{
		if (this != &P)
		{
			delete[] name_;
			copy(P);
		}
		return *this;
	}


	Product::~Product()
	{
		delete[] name_;
	}

	// Setter for sku_ attribute
	void Product::sku(const char* s)
	{
		if (s)
		{
			strncpy(sku_, s, MAX_SKU_LEN + 1);
			sku_[MAX_SKU_LEN + 1] = 0;
		}
	}

	// Setter for price_ attribute
	void Product::price(double p)
	{
		price_ = p;
	}

	// Setter for name_ attribute
	void Product::name(const char* n)
	{
		if (n)
		{
			int size(strlen(n) + 1);
			name_ = new char[size];
			strncpy(name_, n, size);
			name_[size] = 0;
		}
	}

	// Setter for taxed_ attribute
	void Product::taxed(bool t)
	{
		taxed_ = t;
	}

	// Setter for quantity_ attribute
	void Product::quantity(int q)
	{
		quantity_ = q;
	}

	// Setter for qtyNeeded_ attribute
	void Product::qtyNeeded(int qN)
	{
		qtyNeeded_ = qN;
	}

	// Getter for sku_ attribute
	const char* Product::sku()const
	{
		return sku_;
	}

	// Getter for price_ attribute
	double Product::price()const
	{
		return price_;
	}

	// Getter for name_ attribute
	const char* Product::name()const
	{
		return name_;
	}

	// Getter for taxed_ attribute
	bool Product::taxed()const
	{
		return taxed_;
	}

	// Getter for quantity_ attribute
	int Product::quantity()const
	{
		return quantity_;
	}

	// Getter for qtyNeeded_ attribute
	int Product::qtyNeeded()const
	{
		return qtyNeeded_;
	}

	// Returns the Cost returns the cost of the Product after tax
	// If the Product is not taxed the return value of cost() will be the same as price
	double Product::cost()const
	{
		double ret(0);
		if (taxed() == 1)     // 1 means taxed and 0 means not taxed
		{
			double tax(price_ * TAX);
			ret = tax + price();
		}
		else
		{
			ret = price();
		}
		return ret;
	}

	// return true if the Product is in a safe empty state
	bool Product::isEmpty()const
	{
		return (!name_ || !sku_);
	}

	// receives a constant character pointer and returns a Boolean
	// This operator will compare the received constant character pointer to the SKU of the 
	// Product, if they are the same, it will return true or else, it will return false
	bool Product::operator==(const char* s)
	{
		return (strcmp(sku(), s) == 0);
	}

	// receives an integer and returns an integer
	// This operator will add the received integer
	// value to the quantity of the Product, returning the sum
	int Product::operator+=(int q)
	{
		return quantity_ += q;
	}

	// receives an integer and returns an integer
	// This operator will reduce the quantity of the Product by the integer value 
	// returning the quantity after reduction
	int Product::operator-=(int q)
	{
		return quantity_ -= q;
	}

	// receives a double reference value as left operand and a constant Product 
	// reference as right operand and returns a double value;
	// This operator multiplies the cost of the Product by the quantity of the 
	// Product and then adds that value to the left operand and returns the result
	// Essentially this means this operator adds the total cost of the Product on 
	// hand to the left operand, which is a double reference, and then returns it
	double operator+=(double& price, const Product& P)
	{	
		double temp = price += (P.cost() * P.quantity());
		return temp;
	}

	// overloaded operators to work with ostream (cout) to print a Product to, and 
	// istream (cin) to read a Product from, the console; Makes use of the write() 
	// and read() methods of Streamable class that are implemented on ms4Tester
	std::ostream& operator<<(std::ostream& ostr, const Product& P){
		return P.write(ostr, true);
	}
	std::istream& operator>>(std::istream& istr, Product& P){
		return P.read(istr);
	}


	bool Product::operator<(const Product& p)
	{
		return strcmp(name(), p.name()) > 0;
	}
	bool Product::operator>(const Product& p)
	{
		return strcmp(name(), p.name()) > 0;
	} 
}

