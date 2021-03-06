#ifndef __QUOTE2_H__
#define __QUOTE2_H__

#include <iostream>
#include <memory>

class Quote{
 public:
  Quote() = default;
  Quote(const std::string& book, double pri)
    :bookNo(book), price(pri){}
  std::string isbn() const{return bookNo;}
  virtual double net_price(std::size_t n)const{
    return n * price;
  }
  virtual void debug()const{
    std::cout << bookNo << " " << price << std::endl;
  }
  virtual ~Quote() = default;
 private:
  std::string bookNo;
 protected:
  double price = 0.0;
};

class Disc_quote : public Quote{
 public:
  Disc_quote() = default;
  Disc_quote(const std::string& book, double price,
	     std::size_t qyn, double disc):Quote(book, price),
    quantity(qyn), discount(disc){}
  
  double net_price(std::size_t) const override = 0;
 protected:
  std::size_t quantity = 0;//折扣适用的数量
  double discount = 0.0;   //折扣率
};

class Bulk_quote : public Disc_quote{
 public:
  
  Bulk_quote() = default;
  
  Bulk_quote(const std::string& book, double price,
  std::size_t qyn, double disc)
  :Disc_quote(book, price, qyn, disc){}
  
  double net_price(std::size_t) const override;
};

class Min_quote : public Disc_quote{
 public:
  
  Min_quote() = default;
  Min_quote(const std::string& book, double price,
  	   std::size_t qyn, double disc)
   :Disc_quote(book, price, qyn, disc){}
  
  double net_price(std::size_t) const override;
};

#endif
