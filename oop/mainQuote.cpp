#include "Quote.h"

double print_total(std::ostream& os,
		   const Quote& item, size_t n);
int main(){
  Quote q("01",100.5);
  double d = print_total(std::cout, q, 1);

  Bulk_quote bq("01", 100.5, 5, 1);
}
