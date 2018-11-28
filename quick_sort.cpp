#include <iostream>
#include <list>
#include <algorithm>

template<typename T>
std::list<T> sort1(std::list<T> input){
  if(input.empty()){
    return input;
  }
  std::list<T> r;
  r.splice(r.begin(), input, input.begin());
  
  T const& first = *r.begin();
  auto div = std::partition(input.begin(), input.end(),
			    [&](T const& t){return t < first;});

  std::list<T> l;
  l.splice(l.end(), input, input.begin(), div);

  //auto nl(sort1(std::move(l)));
  //auto nh(sort1(std::move(input)));
  auto nl = sort1(std::move(l));
  auto nh = sort1(std::move(input));

  r.splice(r.end(), nh);
  r.splice(r.begin(), nl);
  
  return r;
}
int main(){
  std::list<int> input{4,5,6,1,7,9,2,0,8,3};
  std::list<int> r = sort1(input);

  for(auto const m : input){
    std::cout << m << ",";
  }
  std::cout << std::endl;
  
  for(auto const m : r){
    std::cout << m << ",";
  }
  std::cout << std::endl;
}
