#include <iostream>

class Int{
private:
  int mi;
public:
  //Int(){}
  
  Int(int i):mi(i){
    std::cout << "c" << std::endl;
  }
  Int(const Int& tmp){
    mi = tmp.mi;
  }
  
  ~Int(){}
};

class test{
  Int data;
public:
  test(Int d) : data(d){}
  test(const test& t){
    //data = t.data;
  }
  ~test(){}
  Int getvalue(){
    return data;
  }
  //重载方法
  Int getvalue() const {
    return data;
  }
};

int main(){
  //Int d1(10);
  //test t1(10);
  //const test t2(12);
  
  //Int a1 = t2.getvalue();
  //int& b1 = t2.getvalue();
  //const Int& c1 = t2.getvalue();
}
