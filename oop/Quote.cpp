#include "Quote.h"

Bulk_quote::Bulk_quote(const std::string& book, double p,
		       std::size_t qty, double disc):
  Quote(book, p), min_qty(qty), discount(disc){}

double Bulk_quote::net_price(std::size_t cnt)const {
  if(cnt >= min_qty){
    return cnt * (1 - discount) * price;
  }
  else{
    return cnt * price;
  }
}

void Bulk_quote::debug()const{
  std::cout << min_qty << " " << discount << " " << price << std::endl;
}
Min_quote::Min_quote(const std::string& book, double p,
		       std::size_t qty, double disc):
  Quote(book, p), max_qty(qty), discount(disc){}

double Min_quote::net_price(std::size_t cnt)const {
  if(cnt < max_qty){
    return cnt * (1 - discount) * price;
  }
  else{
    return cnt * price;
  }
}

void Min_quote::debug()const{
  std::cout << max_qty << " " << discount << " " << price << std::endl;
}
