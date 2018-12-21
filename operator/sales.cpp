#include "sales.hpp"

Sales_data::Sales_data(std::istream& is) : Sales_data(){
  is >> *this;
}

std::istream& operator>>(std::istream& is, Sales_data& item){
  double price = 0.0;
  is >> item.bookNo >> item.units_sold >> price;
  if(is){
    item.revenue = item.units_sold * price;
  }
  else{
    //item = Sales_data();
  }
  return is;
}

std::ostream& operator<<(std::ostream& os, const Sales_data& item){
  os << item.bookNo << ":" << item.units_sold << " " <<
    item.revenue << " " << item.avg_price();
  return os;
}

Sales_data operator+(const Sales_data& s1, const Sales_data& s2){
  Sales_data da = s1;
  da += s2;
  return da;
}

Sales_data& Sales_data::operator+=(const Sales_data& rhs){
  units_sold += rhs.units_sold;
  revenue += rhs.revenue;
  return *this;
}
Sales_data& Sales_data::operator=(const std::string& isbn){
  bookNo = isbn;
  return *this;
}
int main(){
  Sales_data s1;
  s1 = std::string("aa");
  std::cout << s1 << std::endl;
  /*
  Sales_data s1(std::cin);
  std::string bn("aa");
  Sales_data s2(bn, 10, 5.2);
  Sales_data s3 = s1 + s2;
  std::cout << s3 << std::endl;
  */

  
}
