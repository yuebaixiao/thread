#include <deque>
#include <mutex>
#include <future>
#include <thread>
#include <iostream>
#include <unistd.h>
//#include <utility>

std::mutex mut;
std::deque<std::packaged_task<std::string(int)>> tasks;

void manage_tasks(){
  while(true){
    sleep(2);
    //std::cout << "please wait for a moument" << std::endl;
    std::packaged_task<std::string(int)> task;
    {
      std::lock_guard<std::mutex> lg(mut);
      if(tasks.empty()) continue;
      std::cout << "----------------------not empty---------------" << std::endl;
      task = std::move(tasks.front());
      tasks.pop_front();
    }
    task(1);
    //std::string s = task(10);
  }
}

template<typename Call>
std::future<std::string> add_task(Call ca){
  std::cout << "----------------------add_task---------------" << std::endl;  
  std::packaged_task<std::string(int)> task(ca);
  std::future<std::string> ret = task.get_future();
  std::lock_guard<std::mutex> lg(mut);
  tasks.push_back(std::move(task));
  return ret;
}

std::string jiaoche(int i = 0){
  std::cout << "-------------jiaoche---------------" << std::endl;
  if(i == 1){
    return "aaa";
  }else{
    return "bbb";
  }
}
int main(){

  std::thread background_thread(manage_tasks);
  background_thread.detach();


  std::future<std::string> fut1 = add_task(jiaoche);
  //std::string s1 = fut1.get();
  //std::cout << s1 << std::endl;
  
  std::future<std::string> fut2 = add_task(jiaoche);
  //std::string s2 = fut2.get();
  //std::cout << s2 << std::endl;

  pthread_exit(NULL);

}
