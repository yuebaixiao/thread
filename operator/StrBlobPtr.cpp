#include "StrBlobPtr.h"

std::shared_ptr<std::vector<std::string>>
StrBlobPtr::check(std::size_t i, const std::string& msg) const{
  auto ptr = wptr.lock();
  if(!ptr){
    throw std::runtime_error("unbound StrBlobPtr");
  }
  if(i >= ptr->size()){
    throw std::out_of_range(msg);
  }
  return ptr;
}

//qianzhi
StrBlobPtr& StrBlobPtr::operator++(){
  check(curr, "will past end");
  ++curr;
  return *this;
}
//qianzhi
StrBlobPtr& StrBlobPtr::operator--(){
  --curr;
  check(curr, "will past begin");
  return *this;
}
//houzhi
StrBlobPtr StrBlobPtr::operator++(int){
  auto tmp = *this;
  ++*this;
  return tmp;
}
//houzhi
StrBlobPtr StrBlobPtr::operator--(int){
  auto tmp = *this;
  --*this;
  return tmp;
}
