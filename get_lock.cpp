#include <mutex>

std::unique_lock<std::mutex> getlock(){
  std::mutex sm;
  std::unique_lock<std::mutex> lk(sm);
  //prepare_data();
  return lk;//因为lk是右值，所以自动调用了std::move函数，把锁的所有权转移了出去。
}

void process_data(){
  std::unique_lock<std::mutex> lk(getlock());
  //do_something();
}

int main(){
  process_data();
}
