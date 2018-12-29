#include "Quote.h"


double print_total(std::ostream& os,
		   const Quote& item, size_t n){
  double ret = item.net_price(n);
  os << "ISBN: " << item.isbn()
     << " # sold: " << n << " total due: " << ret << std::endl;
  return ret;

}


double print_total(std::ostream& os,
		   const std::shared_ptr<Quote> item, size_t n){
  double ret = item->net_price(n);
  os << "ISBN: " << item->isbn()
     << " # sold: " << n << " total due: " << ret << std::endl;
  return ret;

}

int main(){
  Quote q("01",100);
  print_total(std::cout, q, 1);

  Bulk_quote bq("01", 100, 5, 0.1);
  print_total(std::cout, bq, 10);

  Min_quote mq("01", 100, 15, 0.1);
  print_total(std::cout, mq, 4);

  std::shared_ptr<Quote> sbq =
    std::make_shared<Bulk_quote>("02", 100, 5, 0.2);
  print_total(std::cout, sbq, 10);

  /*
  Quote& q1 = mq;
  q1.debug();
  q1 = bq;
  q1.debug();
  q1 = q;
  q1.debug();
 
  
  Quote* q2 = &mq;
  q2->debug();
  q2 = &bq;
  q2->debug();
  q2 = &q;
  q2->debug();
  */

  /*-----------test1-----------*/
  //Quote& q1 = q;
  //q1.debug();
  //q1 = bq;
  //q1.debug();
  //q1 = mq;
  //q1.debug();
  /*-----------test1-----------*/
  
  /*-----------test2-----------*/
  //Quote& q1 = mq;
  //q1.debug();
  //q1 = bq;
  //q1.debug();
  //q1 = q;
  //q1.debug();
  /*-----------test2-----------*/
    
  /*-----------test3-----------*/
  //Quote* q2 = &q;
  //q2->debug();
  //q2 = &bq;
  //q2->debug();
  //q2 = &mq;
  //q2->debug();
  /*-----------test3-----------*/
    
  /*-----------test4-----------*/
  Quote* q2 = &mq;
  q2->debug();
  q2 = &bq;
  q2->debug();
  q2 = &q;
  q2->debug();
  /*-----------test4-----------*/
}
