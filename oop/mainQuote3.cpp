#include "Quote3.h"
#include "Basket.h"
#include <vector>
#include <iostream>

double print_total(std::ostream& os,
		   const Quote& item, size_t n){
  double ret = item.net_price(n);
  os << "ISBN: " << item.isbn()
     << " # sold: " << n << " total due: " << ret << std::endl;
  return ret;

}

int main(){
  Basket bsk;
  bsk.add_item(std::make_shared<Quote>("01", 100));
  bsk.add_item(std::make_shared<Bulk_quote>("01", 100, 2, 0.1));
  bsk.add_item(std::make_shared<Bulk_quote>("01", 100, 2, 0.1));
  bsk.total_receipt(std::cout);
}
