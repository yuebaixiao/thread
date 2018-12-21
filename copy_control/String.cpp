#include "String.h"

String::String(const char* p){
  char* tmp = (char*)p;
  while(*tmp++ != '\0'){
  }
  auto pa = alloc_n_copy(p, tmp);
  elements = pa.first;
  first_free = cap = pa.second;
}

std::pair<char*, char*> String::alloc_n_copy
(const char* b, const char* e){
  auto data = alloc.allocate(e - b);
  return {data, std::uninitialized_copy(b, e, data)};
}

std::ostream& operator<<(std::ostream& os, const String& str){
  for(char* tmp = str.elements; tmp != str.first_free;++tmp){
    os << *tmp;
  }
  return os;
}

bool operator==(const String& lhs, const String& rhs){
  if(lhs.size() == rhs.size()){
    char* t1 = lhs.elements;
    char* t2 = rhs.elements;
    while(*t1 == *t2 && *t1 != '\0'){
      t1++;
      t2++;
    }
    if(*t1 == '\0'){
      return true;
    }
    else{
      return false;
    }
  }
  else{
    return false;
  }
}
bool operator<(const String& lhs, const String& rhs){
  if(lhs.size() == rhs.size()){
    char* t1 = lhs.elements;
    char* t2 = rhs.elements;
    while(*t1 == *t2 && *t1 != '\0'){
      t1++;
      t2++;
    }
    if(*t1 == '\0'){
      return false;//==
    }
    else if(*t1 < *t2){
      return true;
    }
    else{
      return false;
    }
  }
  else if(lhs.size() < rhs.size()){
    return true;
  }
  else{
    return false;
  }
}
int main(){
  String s1("bbc");
  String s2("abce");
  if(s1 < s2){
    std::cout << "<" << std::endl;
  }
  /*
  String s1("qq");
  String s2("qq");
  if(s1 == s2){
    std::cout << "true" << std::endl;
  }
  else{
    std::cout << "false" << std::endl;
  }
  std::cout << s1 << std::endl;
  */
}
