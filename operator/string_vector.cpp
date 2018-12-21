#include <iostream>
#include <memory>
#include <string>

class string_vector{
  friend bool operator==(const string_vector&, const string_vector&);
  friend bool operator!=(const string_vector&, const string_vector&);
public:
  string_vector():
    elements(nullptr), first_free(nullptr), cap(nullptr){}
  string_vector(const string_vector&);
  string_vector& operator=(const string_vector&);
  string_vector(std::initializer_list<std::string>);
  ~string_vector();
  void push_back(const std::string&);

  string_vector& operator=(std::initializer_list<std::string>);
  
  size_t size() const {
    return first_free - elements;
  };
  
  size_t capacity() const {
    return cap - elements;
  }

  void resize(size_t, std::string&);
  void resize(size_t);

  void reserve(size_t);
  
  std::string* begin() const{return elements;}
  std::string* end() const{return first_free;}
private:
  static std::allocator<std::string> alloc;
  //static const int a = 10;
  void chk_n_alloc(){
    if(size() == capacity())
      reallocate();
  }
  std::pair<std::string*, std::string*> alloc_n_copy
  (const std::string* b, const std::string* e);
  void free();
  void reallocate();
  void reallocate(size_t);
  std::string* elements;//指向第一个元素的指针
  std::string* first_free;//指向最后一个元素的下一个位置的指针
  std::string* cap;//指向vector空间最后一个位置的下一个位置的指针
};

//必须在类的外面再定义一次，否则后面使用alloc的地方，编译不过
std::allocator<std::string> string_vector::alloc;

std::pair<std::string*, std::string*> string_vector::alloc_n_copy
(const std::string* b, const std::string* e){
  auto data = alloc.allocate(e - b);
  return {data, std::uninitialized_copy(b, e, data)};
}

void string_vector::push_back(const std::string& s){
  chk_n_alloc();
  alloc.construct(first_free++, s);
}

void string_vector::free(){
  if(elements){
    for(auto p = first_free; p != elements;)
      alloc.destroy(--p);
    alloc.deallocate(elements, cap - elements);
  }
}

string_vector::string_vector(const string_vector& s){
  auto newdata = alloc_n_copy(s.begin(), s.end());
  elements = newdata.first;
  first_free = cap = newdata.second;
}
string_vector::string_vector(std::initializer_list<std::string> sl){
  auto newdata = alloc_n_copy(sl.begin(), sl.end());
  elements = newdata.first;
  first_free = cap = newdata.second;
}
string_vector::~string_vector(){
  free();
}

string_vector& string_vector::operator=(const string_vector& rhs){
  auto newdata = alloc_n_copy(rhs.begin(), rhs.end());
  free();
  elements = newdata.first;
  first_free = cap = newdata.second;
  return *this;
}

void string_vector::reallocate(){
  auto newcap = size() ? size() * 2 : 1;
  auto newdata = alloc.allocate(newcap);
  auto dest = newdata;
  auto elem = elements;
  for(size_t i = 0; i != size(); ++i){
    alloc.construct(dest++, std::move(*elem++));
  }
  free();
  elements = newdata;
  first_free = dest;
  cap = elements + newcap;
}

void string_vector::reallocate(size_t sz){
  auto newcap = sz * 2;
  auto newdata = alloc.allocate(newcap);
  auto dest = newdata;
  auto elem = elements;
  for(size_t i = 0; i != size(); ++i){
    alloc.construct(dest++, std::move(*elem++));
  }
  free();
  elements = newdata;
  first_free = dest;
  cap = elements + newcap;
}
void string_vector::reserve(size_t sz){
  if(sz > capacity()){
    reallocate(sz);
  }
}

void string_vector::resize(size_t sz){
  size_t cap = capacity();
  if(sz > cap){
    reallocate(sz);
    for(size_t i = size();i != sz; ++i){
      //调用string的默认构造方法
      alloc.construct(first_free++);
    }
  }
  else if(sz < size()){
    for(size_t i = sz;i != size(); ++i){
      //调用string的西沟函数
      alloc.destroy(--first_free);
    }
  }
}

void string_vector::resize(size_t sz, std::string& s){
  size_t cap = capacity();
  if(sz > cap){
    reallocate(sz);
    for(size_t i = size();i != sz; ++i){
      //调用string的非默认构造方法
      alloc.construct(first_free++, s);
    }
  }
  else if(sz < size()){
    for(size_t i = sz;i != size(); ++i){
      //调用string的西沟函数
      alloc.destroy(--first_free);
    }
  }
}

bool operator==(const string_vector& lhs, const string_vector& rhs){
  if(lhs.size() == rhs.size()){
    auto *p1 = lhs.elements;
    auto *p2 = rhs.elements;
    while(p1 != lhs.first_free){
      if(*p1++ != *p2++){
	return false;
      }
    }
    return true;
  }else{
    return false;
  }
}
bool operator!=(const string_vector& lhs, const string_vector& rhs){
  return !operator==(lhs, rhs);
}

string_vector& string_vector::operator=(std::initializer_list<std::string> il){
  auto newdata = alloc_n_copy(il.begin(), il.end());
  free();
  elements = newdata.first;
  first_free = cap = newdata.second;
  return *this;
}

int main(){
  string_vector s1{"111"};
  std::cout << s1.size() << std::endl;
  s1 = {"222","233"};
  std::cout << s1.size() << std::endl;
  /*
  string_vector sv1{"112"};
  string_vector sv2{"11"};
  if(sv1 != sv2){
    std::cout << "!=" << std::endl;
  }
  else{
    std::cout << "==" << std::endl;
  }
  */
}
