#include "Quote3.h"
#include <vector>


double print_total(std::ostream& os,
		   const Quote& item, size_t n){
  double ret = item.net_price(n);
  os << "ISBN: " << item.isbn()
     << " # sold: " << n << " total due: " << ret << std::endl;
  return ret;

}

int main(){

  std::vector<Quote> qv;
  for(unsigned i = 0; i != 10; ++i){
    qv.push_back(Bulk_quote("01", 100, 10, 0.1));
  }
  double total = 0;
  for(const auto s : qv){
    total += s.net_price(20);
  }
  std::cout << total << std::endl;

  std::cout << "-------------------------" << std::endl;

  std::vector<std::shared_ptr<Quote>> sv;
  for(unsigned i = 0; i != 10; ++i){
    sv.push_back(std::make_shared<Bulk_quote>("01", 100, 10, 0.1));
  }
  double total1 = 0;
  for(const auto s : sv){
    total1 += s->net_price(20);
  }
  std::cout << total1 << std::endl;
  
}
