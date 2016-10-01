// Final Project Milestone 4 
// Product Tester program
// File	Product.h
// Version 1.0
// Date	2016-3-17
// Author	Fardad Soleimanloo
// Student Julian Philip Hernandez; 036054120; jphernandez2
#ifndef SICT_PRODUCT_H__
#define SICT_PRODUCT_H__
#include "Streamable.h"
#include "general.h"
namespace sict
{
	class Product: public Streamable
	{
		char sku_[MAX_SKU_LEN + 1];  // This character array holds the SKU (barcode) of the items as a string.
		char* name_;                 // This character pointer points to a dynamic string that holds the name of the Product
		double price_;               // Holds the Price of the Product
		bool taxed_;                 // This variable will be true if this Product is taxed
		int quantity_;               // Holds the on hand (current) quantity of the Product.
		int qtyNeeded_;              // Holds the needed quantity of the Product.
		void copy(const Product& P); // private copy method for copy constructor and op=
	public:
		Product();
		Product(const char* s, const char* n, double p = 0, int qN = 0, bool t = true);

		Product(const Product& P);
		Product& operator=(const Product& P);
		virtual ~Product();

		void sku(const char* s);
		void price(double p);
		void name(const char* n);
		void taxed(bool t);
		void quantity(int q);
		void qtyNeeded(int qN);

		const char* sku()const;
		double price()const;
		const char* name()const;
		bool taxed()const;
		int quantity()const;
		int qtyNeeded()const;
		double cost()const;
		bool isEmpty()const;

		bool operator==(const char* s);
		int operator+=(int q);
		int operator-=(int q);
		bool Product::operator<(const Product& p);
		bool Product::operator>(const Product& p);
	};

	double operator+=(double& price, const Product& P);
	std::ostream& operator<<(std::ostream& ostr, const Product& P);
	std::istream& operator>>(std::istream& istr, Product& P);
}

#endif // !


