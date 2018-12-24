#ifndef __STRBLOBPTR_H__
#define __STRBLOBPTR_H__

#include <memory>
#include <string>
#include <vector>
#include "StrBlob.h"

class StrBlob;
class StrBlobPtr{
 public:
  StrBlobPtr() : curr(0){}
  StrBlobPtr(StrBlob& a, size_t sz = 0):wptr(a.data), curr(sz){}

  //方法get和重载*的效果是一样的
  std::string get(){
    auto ptr = check(curr, "get string value");
    return (*ptr)[curr];
  }
  
  //方法get和重载*的效果是一样的
  std::string& operator*(){
    auto p = check(curr, "get string value");
    return (*p)[curr];
  }
  std::string* operator->(){
    return & this->operator*();
  }
  
  StrBlobPtr& operator++();
  StrBlobPtr& operator--();
  StrBlobPtr operator++(int);
  StrBlobPtr operator--(int);

 private:
  std::shared_ptr<std::vector<std::string>>
    check(std::size_t, const std::string&) const;
  
  std::weak_ptr<std::vector<std::string>> wptr;
  std::size_t curr;
};

#endif
