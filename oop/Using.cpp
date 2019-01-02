#include <cstddef>//std::size_t

class Base{
public:
  std::size_t size() const {
    return n;
  }
  void f() const {
    
  }
protected:
  std::size_t n = 0;
  int j = 0;
};

class D : private Base{
public:
  using Base::size;
protected:
  using Base::n;
};

class DD : public D{
  void g(){
    std::size_t t = n;
    //int tj = j;//error
  }
};

int main(){
  D d;
  d.size();
  //d.f();//error
  
}


