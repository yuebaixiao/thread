#ifndef __QUOTE4_H__
#define __QUOTE4_H__

#include <iostream>

class Quote{
 public:
  Quote() = default;
  Quote(const std::string& book, double pri)
    :bookNo(book), price(pri){}
  std::string isbn() const{return bookNo;}

  
  //调用此方法的对象是左值的时候
  virtual Quote* clone() const & {
    //调用合成的拷贝构造函数
    return new Quote(*this);
  }

  ///调用此方法的对象是右值的时候
  virtual Quote* clone() && {
    //调用合成的移动构造函数
    return new Quote(std::move(*this));
  }



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


  //调用此方法的对象是左值的时候
  Bulk_quote* clone() const & {
    //调用合成的拷贝构造函数
    return new Bulk_quote(*this);
  }

  ///调用此方法的对象是右值的时候
  Bulk_quote* clone() && {
    //调用合成的移动构造函数
    return new Bulk_quote(std::move(*this));
  }

  
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
