#include <iostream>

class Quote{
 public:
  Quote() = default;
  Quote(const std::string& book, double pri)
    :bookNo(book), price(pri){}
  std::string isbn() const{return bookNo;}
  virtual double net_price(std::size_t n)const{
    return n * price
  }
  virtual ~Quote() = default;
 private:
  std::string bookNo;
 protected:
  double price = 0.0;
};

class Bulk_quote : public Quote{
 public:
  Bulk_quote() = default;
  Bulk_quote(const std::string&, double, std::size_t,
	     double);
  double net_price(std::size_t n)const override;
 private:
  std::size_t min_qty = 0;//适用于折扣的最低购买数量
  double discount = 0.0;//折扣额
};

double print_total(ostream& os,
		   const Quote& item, size_t n){
  double ret = item.net_price();
  os << "ISBN: " << item.isbn()
     << " # sold: " << n << " total due: " << ret << std::endl;
  return ret;
}
