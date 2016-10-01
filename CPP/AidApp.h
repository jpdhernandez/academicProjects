// Final Project Milestone 6
// File	AidApp.h
// Date	2016-Apr-16
// Author	Fardad Soleimanloo
// Student Julian Philip Hernandez; 036054120; jphernandez2

#ifndef SICT_AIDAPP_H__
#define SICT_AIDAPP_H__
#include "AmaPerishable.h"
#include <fstream>
#include <iostream>
namespace sict
{
	class AidApp
	{
	private:
		char filename_[256]; // holds the name of the text file to store the products' information.
		Product* product_[MAX_NO_RECS]; //An array of Product pointers, MAX_NO_RECS long. (i.e. Each element of this array is a product pointer)
		std::fstream datafile_; //A fstream instance to create and access a file.
		int noOfProducts_; // Number of Products (Non-perishable or Perishable) pointed by product_ array elements.
		
		AidApp(const AidApp& src) = delete;   // prevents copying to similar obj
		AidApp& operator=(const AidApp& src) = delete; // prevents assignment to similar obj

		void pause()const;
		int menu();
		void loadRecs();
		void saveRecs();
		void listProducts()const;
		int SearchProducts(const char* sku)const;
		void addQty(const char* sku);
		void addProduct(bool isPerishable);
		void updateQty(const char* sku);
	public:
		AidApp(const char* filename);
		int run();
		void DeleteProduct(const char* sku);
	};
}
#endif
