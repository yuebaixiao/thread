#include <iostream>

using namespace std;


class Base{
public:
  virtual void show() const{
    cout << "base show" << endl;
  }
  void print(){
    cout << "base print" << endl;
  }
};

class D : public Base{
public:
  void print()const{
    cout << "D print" << endl;
  }
};
void fun(Base *pb){
  D *pd = dynamic_cast<D*>(pb);
  if(pd != nullptr){
    cout << "not null" << endl;
  }else{
    cout << "null" << endl;
  }
}
int main(){
  Base b;
  D d;
  fun(&b);
}
/*
int main(){
  int a = 10;
  int const  * p = &a;
  const int b = 11;
  p = &b;

}
*/

/* static_cast
int main(){
  int i = 122;
  float f;
  double d;

  f = i;

  float ff = 12.23f;
  double dd = 112.123;
  int v = dd
  //cout << v << endl;

  void* vo = &ff;
  int* p = (int*)(&ff);
  cout << *p << endl;
}
*/
