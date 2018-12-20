#include "String.h"

String::String(const char* p){

}

std::pair<char*, char*> String::alloc_n_copy
(const char* b, const char* e){
  auto data = alloc.allocate(e - b);
  return {data, std::uninitialized_copy(b, e, data)};
}

int main(){}
