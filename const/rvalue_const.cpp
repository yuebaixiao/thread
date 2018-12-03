#include <iostream>
using namespace std;

class Test{
public:
  Test(int d = 0):data(d){
    cout << "C:" << d << " " << this << endl;
  }
  
  Test( Test &t){
    cout << "Copy:" << t.data << " " << this << endl;
    data = t.data;
  }
  ~Test(){
    cout << "F:" << this->data << "->" << this << endl;
  }
  int getData()const{
    return data;
  }
  void setData(int d){
    data = d;
  }
private:
  int data;
};


Test fun(Test &x){
  int value = x.getData();
  Test tmp(value);
  return tmp;

}

int main(){
  Test t1(100); 
  //编译器优化了，当把fun(t1)的返回值拷贝给t2时，应该调用拷贝构造函数，但是编译器优化了，就没有调用这次多余的拷贝构造函数，直接把让t2所占用的内存就是右值(fun(t1))所开辟的内存.
  const Test& t2 = fun(t1);
  //Test t3 = fun(t1);
  //t2.setData(11);
  //std::cout << t2.getData() << std::endl;

  //Test t2(fun(t1));

  return 0;
}
