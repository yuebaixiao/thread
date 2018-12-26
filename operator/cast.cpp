#include <iostream>

/*---------test1------------- */
class Int{
public:
  Int(int i = 0) : val(i){}
  explicit operator int()const{return val;}
private:
  int val;
};
/*---------test1------------- */

/*---------test2------------- */
struct A;
struct B{
  operator A()const;
  int val;
};

struct A{
  A(int i = 0) : val(i){}
  A(const B& b){
    std::cout << "A copy" << std::endl;
    val = b.val;
  }
private:
  int val;
};

B::operator A()const{
  std::cout << "B cast" << std::endl;
  return A(10);
}
  A f(const A&){}
/*---------test2------------- */
int main(){
/*---------test1------------- */
  Int i1;
  i1 = 10;
  int s = (int)i1 + 11;
  std::cout << s << std::endl;

  const Int i2(11);
  int s1 = (int)i2;
/*---------test1------------- */

/*---------test2------------- */
  B b1;
  A a1 = f(b1.operator A());
/*---------test2------------- */
}
