// Final Project Milestone 6
// File	AidApp.cpp
// Date	2016-Apr-16
// Author	Fardad Soleimanloo
// Student Julian Philip Hernandez; 036054120; jphernandez2
#include "AidApp.h"
#include "Product.h"
#include "AmaPerishable.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "Sort.h"
using namespace std;
namespace sict
{
	AidApp::AidApp(const char* filename)
	{
		strncpy(filename_, filename, 256);
		filename_[256] = 0;
		for (int i = 0; i < MAX_NO_RECS; i++)
		{
			product_[i] = nullptr;
		}
		noOfProducts_ = 0;
		loadRecs();
	}

	void AidApp::pause()const
	{
		cout << "Press Enter to continue..." << endl;
		while (cin.get() != '\n');
	}

	int AidApp::menu()
	{
		cout << "Disaster Aid Supply Management Program" << endl;
		cout << "1- List products" << endl;
		cout << "2- Display product" << endl;
		cout << "3- Add non-perishable product" << endl;
		cout << "4- Add perishable product" << endl;
		cout << "5- Add to quantity of purchased products" << endl;
		cout << "6- Update product quantity" << endl;
		cout << "7- Delete product" << endl;
		cout << "8- Sort Products" << endl;
		cout << "0- Exit program" << endl;
		cout << "> ";
		int selection;
		cin >> selection;
		cin.ignore(1000, '\n');
		return (selection < 0 || selection > 8) ? -1 : selection;
		cout << endl;
	}

	void AidApp::loadRecs()
	{
		int readIndex(0);
		datafile_.open(filename_, ios::in);
		if (datafile_.fail())
		{
			datafile_.clear();
			datafile_.close();
			datafile_.open(filename_, ios::out);
			datafile_.close();
		}
		else
		{
			char ch;
			while (!datafile_.fail())
			{
				delete product_[readIndex];
				product_[readIndex] = nullptr;
				ch = datafile_.get();
				if (ch == 'P')
				{
					product_[readIndex] = new AmaPerishable;
				}
				else if (ch == 'N')
				{
					product_[readIndex] = new AmaProduct;
				}
				if (ch == 'P' || ch == 'N')
				{
					datafile_.ignore();
					product_[readIndex]->load(datafile_);
					readIndex++;
				}
			}
			noOfProducts_ = readIndex;
		}
		datafile_.close();
	}

	void AidApp::saveRecs()
	{
		datafile_.open(filename_, ios::out);
		for (int i = 0; i < (noOfProducts_) && datafile_.is_open(); i++)
		{
			product_[i]->store(datafile_);
		}
		datafile_.close();
	}
	void AidApp::listProducts()const
	{
		cout << endl;
		cout << " Row | SKU    | Product Name       | Cost  | QTY| Unit     |Need| Expiry   " << endl;
		cout << "-----|--------|--------------------|-------|----|----------|----|----------" << endl;

		double totalcost(0);
		for (int i = 0; i < noOfProducts_; i++)
		{
			cout << setfill(' ') << right << setw(4) << i + 1 << " | " << *product_[i] << endl;
			if (i == 9)	pause();
			totalcost += *product_[i];
		}

		cout << "---------------------------------------------------------------------------" << endl;
		cout << "Total cost of support: $" << fixed << setprecision(2) << totalcost << endl << endl;
	}

	int AidApp::SearchProducts(const char* sku)const
	{
		int ret(0);
		for (int i = 0; i < noOfProducts_ - 1; i++)
		{
			if (*product_[i] == sku)  
			{
				ret = i;
				break;
			}
			else
			{
				ret = -1;
			}
		}
		return ret;
	}

	void AidApp::DeleteProduct(const char* sku)
	{
		datafile_.open(filename_, ios::out);
		int i;
		for (int i = 0; i < noOfProducts_ - 1; i++)
		{
			if (*product_[i] == sku)
			{
				delete[] product_[i];
				noOfProducts_--;
			}
			else
			{
				product_[i]->store(datafile_);
				cout << "Not found!" << endl;
			}
		}

	}

	void AidApp::addQty(const char* sku)
	{
		int indexSku(SearchProducts(sku));
		int quantity(0);
		if (indexSku == -1)
		{
			cout << "Not found!" << endl;
		}
		else
		{
			product_[indexSku]->write(cout, false);
			cout << endl << '\n' << "Please enter the number of purchased items: ";
			cin >> quantity;
			cin.ignore(1000, '\n'); // flush keyboard
			if (cin.fail())
			{
				cout << "Invalid quanitity value!" << endl;
			}
			else
			{
				int requiredQty = product_[indexSku]->qtyNeeded() - product_[indexSku]->quantity();
				if (quantity <= requiredQty)
				{
					product_[indexSku]->operator+=(quantity);
				}
				else
				{
					int surplus(abs(quantity - requiredQty)); // the amount of items that need to be returned
					product_[indexSku]->operator+=(abs(quantity - surplus)); // adds to inventory only the required amount after subracting surplus
					cout << "Too many items; only " << requiredQty << " is needed, please return the extra "
						<< surplus << " items." << endl;
				}
			}
		}
	}

	void  AidApp::updateQty(const char* sku)
	{
		int indexSku(SearchProducts(sku));
		int quantity(0);
		if (indexSku == -1)
		{
			cout << "Not found!" << endl;
		}
		else
		{
			product_[indexSku]->write(cout, false);
			cout << endl << '\n' << "Please enter the new item quantity: ";
			cin >> quantity;
			cin.ignore(1000, '\n'); // flush keyboard
			int requiredQty = product_[indexSku]->qtyNeeded();
			if (cin.fail())
			{
				cout << "Invalid Quanitity value!" << endl;
			}
			else if (quantity > requiredQty || quantity < 0)
			{
				cout << "Invalid Quanity value, please enter a value between 0 and " << requiredQty << endl;
			}
			else if (quantity <= requiredQty)
			{
				product_[indexSku]->quantity(quantity);
				cout << "Item quantity set to " << quantity << endl;
			}
		}
	}

	void AidApp::addProduct(bool isPerishable)
	{
		if (isPerishable)
		{
			product_[noOfProducts_] = new AmaPerishable; // adds a new Product to end of array
			product_[noOfProducts_]->read(cin); // gets values from user
			saveRecs();
			if (product_[noOfProducts_]) cout << endl << "Product added" << endl << endl;
		}
		else
		{
			product_[noOfProducts_] = new AmaProduct; // adds a new Product to end of array
			product_[noOfProducts_]->read(cin); // gets values from user
			saveRecs();
		}
		if (cin.fail())
		{
			product_[noOfProducts_]->write(cout, false);
		}
		else
		{
			noOfProducts_++;
		}
		cout << endl << "Product added" << endl << endl;
	}

	int AidApp::run()
	{
		int selection;
		do
		{
			selection = menu();
			switch (selection)
			{
				case 1:
				{
					listProducts();
					pause();
				}
				break;
				case 2:
				{
					cout << endl << "Please enter the SKU: "; // prompts user for desired product
					char sku[MAX_SKU_LEN + 1];
					cin >> sku;
					cin.ignore(1000, '\n');
					cout << endl;
					int index = SearchProducts(sku); // retrives index from array
					index != -1 ? product_[index]->write(cout, false) << endl << endl : cout << "Not Found!" << endl;
					pause();
				}
				break;
				case 3:
				{
					cout << endl;
					addProduct(false);
					loadRecs();
				}
				break;
				case 4:
				{
					cout << endl;
					addProduct(true);
					loadRecs();
				} 
				break;
				case 5:
				{
					cout << endl << "Please enter the SKU: ";
					char skuTemp[MAX_SKU_LEN + 1];
					cin >> skuTemp;
					cin.ignore(1000, '\n');
					cout << endl;
					addQty(skuTemp);
					cout << endl << "Updated!" << endl << endl;
				}
				break;
				case 6:
				{
					cout << endl << "Please enter the SKU: ";
					char skuTemp[MAX_SKU_LEN + 1];
					cin >> skuTemp;
					cin.ignore(1000, '\n');
					cout << endl;
					updateQty(skuTemp);
					cout << endl << "Changed quantity!" << endl << endl;
				}
				break;
				case 7:
				{
					cout << endl << "Please enter the SKU: ";
					char skuTemp[MAX_SKU_LEN + 1];
					cin >> skuTemp;
					cin.ignore(1000, '\n');
					DeleteProduct(skuTemp);
					cout << endl << "Deleted!" << endl << endl;
				}
				break;
				case 8:
				{
					sort(product_, noOfProducts_);
					saveRecs();
					cout << endl << "Sorted!" << endl << endl;
				}
				break;
				case 0:
					cout << endl << "Goodbye!!" << endl;
				break;
				default:
				{
					cout << "===Invalid Selection, try again.===" << endl;
					pause();
				}
			}
		} while (selection != 0);
		return selection;
	}

}