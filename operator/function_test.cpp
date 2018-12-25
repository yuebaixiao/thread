#include <functional>
#include <map>
#include <iostream>

int add(int a, int b){
  return a+ b;
}
auto mod = [](int a, int b){return a % b;};
struct divide{
  int operator()(int a, int b){
    return a / b;
  }
};

int main(){
  /*
  std::map<std::string, int(*)(int, int)> mp;
  mp.insert({"+", add});
  mp.insert({"%", mod});
  divide dv;
  mp.insert({"/", divide()});//bian yi bu guo
  
  std::function<int(int, int)> f1 = add;
  std::function<int(int, int)> f2 = mod;
  std::function<int(int, int)> f3 = divide();
  std::cout << f1(1,2) << std::endl;
  std::cout << f2(4,3) << std::endl;
  std::cout << f3(6,2) << std::endl;
  */
  
  std::map<std::string, std::function<int(int, int)>> mp;
  mp.insert({"+", add});
  mp.insert({"-", std::minus<int>()});
  mp.insert({"*", [](int a, int b){return a * b;}});
  mp.insert({"%", mod});
  mp.insert({"/", divide()});

  std::cout << mp["+"](1, 2) << std::endl;
  std::cout << mp["-"](3, 2) << std::endl;
  std::cout << mp["*"](2, 2) << std::endl;
  std::cout << mp["/"](100, 2) << std::endl;
  std::cout << mp["%"](31, 15) << std::endl;
}
