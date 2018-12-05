#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class hasptr{
public:
  friend void show(const std::vector<hasptr>& v);
  friend void swap(hasptr&, hasptr&);
  //默认构造函数
  hasptr():ptr(new std::string), i(0){
    //std::cout << "Cr0" << std::endl;
  }
  //自定义构造函数
  hasptr(const std::string& s, int _i) :
    ptr(new std::string(s)), i(_i){
    //std::cout << "Cr1" << std::endl;
  }
  //拷贝构造函数
  hasptr(const hasptr& rhs) :
    ptr(new std::string(*rhs.ptr)), i(rhs.i){
    //std::cout << "Co" << std::endl;
  }
  //赋值运算符
  hasptr& operator=(const hasptr& rhs){
    //std::cout << "As" << std::endl;
    auto* newp = new std::string(*rhs.ptr);
    delete ptr;
    ptr = newp;
    i = rhs.i;
  }
  //西沟函数
  ~hasptr(){
    //std::cout << "F" << std::endl;
    delete ptr;
  }

  bool operator<(const hasptr& rhs){
    //std:: cout << "<" << std::endl;
    return i < rhs.i;
  }
private:
  std::string* ptr;
  int i;
};

void show(const std::vector<hasptr>& v){
  for(auto a : v){
    std::cout << a.i << ",";
  }
  std::cout << std::endl;
}

inline
void swap(hasptr& lhs, hasptr& rhs){
  std::cout << "swap" << std::endl;
  using std::swap;
  swap(lhs.ptr, rhs.ptr);
  swap(lhs.i, rhs.i);
}
int main(){

  hasptr h1(std::string("a"), 1);
  hasptr h2(std::string("b"), 2);
  hasptr h3(std::string("c"), 3);

  //swap(h1, h3);
  
  std::vector<hasptr> v{h3, h1, h2};
  show(v);
  std::sort(v.begin(), v.end());
  show(v);

  std::vector<hasptr> v1;
  for(int i = 110; i > 0; --i){
    hasptr h(std::string("for"), i);
    //v1.push_back(hasptr(std::string("for"), i));
    v1.push_back(h);
  }
  show(v1);
  std::sort(v1.begin(), v1.end());
  show(v1);
  return 0;
}
