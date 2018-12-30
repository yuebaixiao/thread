#include "Quote2.h"


double print_total(std::ostream& os,
		   const Quote& item, size_t n){
  double ret = item.net_price(n);
  os << "ISBN: " << item.isbn()
     << " # sold: " << n << " total due: " << ret << std::endl;
  return ret;

}

int main(){
  Bulk_quote bq("01", 100.1, 10, 0.2);
  Min_quote mq("01", 200.2, 10, 0.1);
  
  Disc_quote& dq = bq;
  print_total(std::cout, dq, 9);
  dq = mq;
  print_total(std::cout, dq, 9);
  
}
