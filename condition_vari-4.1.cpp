#include <iostream>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <thread>
#include <unistd.h>

std::mutex mut;
std::queue<int> data_queue;
std::condition_variable data_cond;

void data_preparation_thread(){
  while(true){
    int data = 10;
    std::lock_guard<std::mutex> lk(mut);
    data_queue.push(data);
    data_cond.notify_one();
    //std::this_thread::sleep_for(1000);
    sleep(1);
  }
}

void data_process_thread(){
  while(true){
    std::unique_lock<std::mutex> lk(mut);
    data_cond.wait(lk, []{return !data_queue.empty();});
    int data = data_queue.front();
    std::cout << data << std::endl;
    data_queue.pop();
    lk.unlock();
    //假设处理数据data的函数process要花费大量时间，所以提前解锁
    //process(data);
  }
}
int main(){
  std::thread t1(data_preparation_thread);
  std::thread t2(data_process_thread);
  t1.join();
  t2.join();
}
