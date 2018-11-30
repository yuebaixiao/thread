#include <iostream>

class test{
  int data;
public:
  test(int d = 0) : data(d){}
  ~test(){}
  int getvalue(){
    return data;
  }
  int getvalue() const {
    return data;
  }
  void setvalue const (int d){
    data = d;
  }
};

int main(){
  test t1(19);
  const test t2(12);

  t1.setvalue(11);
  
  int a1 = t1.getvalue();
  const int& b1 = t1.getvalue();
}
