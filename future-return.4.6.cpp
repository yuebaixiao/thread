#include <future>
#include <iostream>
#include <unistd.h>

int return_from_thread(int val){
  std::cout << val << std::endl;
  sleep(1);
  return val;
}
void do_something(){
  std::cout << "在等滴滴来车" << std::endl;
}

int main(){
  std::future<int> ret = std::async(return_from_thread, 10);
  do_something();
  std::cout << "车来了，车牌号：" << ret.get() << std::endl;
  std::cout << "end" << std::endl;
}
