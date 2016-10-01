

#ifndef SICT_AMAPRODUCT_H__
#define SICT_AMAPRODUCT_H__
#include "Product.h"
#include "ErrorMessage.h"
namespace sict
{
  class AmaProduct : public Product
  {
  private:
	  char fileTag_;  // Holds a single character to tag the records as Perishable or non-Perishable product in a file.
	  char unit_[11]; // Unit of Measurement (i.e. Kg, Liters, …)
  protected:
	  ErrorMessage err_;
  public:
	  AmaProduct(const char filetag = 'N');
	  const char* unit()const;
	  void unit(const char* value);
	  std::fstream& store(std::fstream& file, bool addNewLine = true)const;
	  std::fstream& load(std::fstream& file);
	  std::ostream& write(std::ostream& os, bool linear)const;
	  std::istream& read(std::istream& is);
  };

}
#endif


