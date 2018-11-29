#include <iostream>
#include <chrono>
#include <mutex>
#include <condition_variable>

std::mutex mut;
std::condition_variable cond;

void thread1(){
  auto const dead = std::chrono::steady_clock::now() +
    std::chrono::milliseconds(500);
  std::unique_lock<std::mutex> loc(mut);
  while(true){
    if(cond.wait_until(loc,dead) == std::cv_status::timeout)
      break;
  }
}
int main(){
}
