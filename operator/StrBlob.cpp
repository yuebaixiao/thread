#include "StrBlob.h"
#include <iostream>

StrBlob::StrBlob() : data(std::make_shared<std::vector<std::string>>()){}
StrBlob::StrBlob(std::initializer_list<std::string> il) :
  data(std::make_shared<std::vector<std::string>>(il)){}

void StrBlob::check(size_type i, const std::string& msg)const{
  if(i >= data->size()){
    throw std::out_of_range(msg);
  }
}

std::string& StrBlob::front(){
  check(0, "front");
  return data->front();
}

std::string& StrBlob::back(){
  check(0, "back");
  return data->back();
}

void StrBlob::pop_back(){
  check(0, "pop_back");
  data->pop_back();
}
bool operator==(const StrBlob& lhs, const StrBlob& rhs){
  /*
  if(lhs.data->size() >=0 && lhs.data->size() == rhs.data->size()){
    for(int i = 0; i < lhs.data->size(); ++i){
      if((*lhs.data)[i] != (*rhs.data)[i]){
	return false;
      }
    }
    return true;
  }
  else{
    return false;
  }
  */
  return *lhs.data == *rhs.data;
  
}
bool operator!=(const StrBlob& lhs, const StrBlob& rhs){
  return !operator==(lhs, rhs);
}

std::string& StrBlob::operator[](size_type idx){
  return (*data)[idx];
}
const std::string& StrBlob::operator[](size_type idx)const{
  return (*data)[idx];
}

/*
int main(){
  StrBlob b1 = {"11","22","33"};
  std::cout << b1[1] << std::endl;
  b1[1] = std::string("aa");
  std::cout << b1[1] << std::endl;
  const std::string& str = b1[1];
  const StrBlob b2 = {"11","22","33"};
  std::cout << b2[1] << std::endl;
  
  StrBlob b1 = {"aa","bb"};
  StrBlob b2 = {"aa","bb"};
  StrBlob b3 = {"aa","bb","dd"};
  using namespace std;
  if(b1 == b2){
    cout << "true" << endl;
  }
  if(b1 != b3){
    cout << "false" << endl;
  }
  
}
*/
