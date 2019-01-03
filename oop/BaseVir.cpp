#include <iostream>

class Base{
public:
  virtual int fcn(){
    std::cout << "base fcn()" << std::endl;
  }
};

class D1 : public Base{
  
public:
  using Base::fcn;
  int fcn(int){//形参与Base的fcn不一致，所以隐藏了Base的fcn
    std::cout << "D1 fcn(int)" << std::endl;
  }
  virtual void f2(){
    std::cout << "D1 f2()" << std::endl;
  }
};

class D2 : public D1{
public:
  int fcn(int){//隐藏了D1::fcn(int)
    std::cout << "D2 fcn(int)" << std::endl;
  }
  int fcn(){//覆盖了Base的虚函数fcn
    std::cout << "D2 fcn()" << std::endl;
  }
  void f2(){//覆盖了D1的虚函数f2
    std::cout << "D2 f2()" << std::endl;
  }
};

int main(){
  Base b;
  D1 d1;
  D2 d2;

  d1.fcn();

  Base* bp1 = &b;
  Base* bp2 = &d1;
  Base* bp3 = &d2;

  bp1->fcn();//调用虚函数，将在运行时调用Base::fcn
  bp2->fcn();//调用虚函数，将在运行时调用Base::fcn
  bp3->fcn();//调用虚函数，将在运行时调用D2::fcn

  D1* d1p = &d1;
  D1* d2p = &d2;

  //bp2->f2();//‘class Base’ has no member named ‘f2’
  d1p->f2();//调用虚函数，将在运行时调用D1::f2
  d2p->f2();//调用虚函数，将在运行时调用D2::f2

  Base* p1 = &d2;
  D1*   p2 = &d2;
  D2*   p3 = &d2;
  //p1->fcn(12);//error
  p2->fcn(12);//静态调用，调用D1::fcn(int)
  p3->fcn(12);//静态调用，调用D2::fcn(int)
 
}
