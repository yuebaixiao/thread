#include <iostream>
#include <thread>

using namespace std;

class my_thread{
public:
  explicit my_thread(thread& t_):t(t_){}
  ~my_thread(){
    if(t.joinable()){
      t.join();
    }
  }
  my_thread(my_thread const&) = delete;
  my_thread& operator=(const my_thread&) = delete;
private:
  thread& t;
};

class func{
public:
  int& data;
  func(int& d):data(d){}
  void operator()(){
    cout << "thread started@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
    for(unsigned j = 0; j < 100; ++j){
      cout << j << endl;
    }
  }
};

int main(){
  int state = 0;
  func f(state);
  thread t(f);
  t.join();
  t.join();
  my_thread mt(t);

  //do_something_in_current_thread();
}
