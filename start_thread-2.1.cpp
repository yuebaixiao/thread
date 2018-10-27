#include <iostream>
#include <thread>

using namespace std;

class background{
public:
  background(int i = 0):data(i){}
  void operator()()const{
    do_one();
    do_two();
  }
private:
  void do_one()const{cout << "do_one:" << data << endl;}
  void do_two()const{cout << "do_two:" << data <<endl;}
  int data;
};

int main(){
  background task;
  thread t(task);
  t.join();
  thread t1((background(1)));
  //t1.join();
  t1.detach();
  thread t2{background(2)};
  t2.join();
  cout << "main thread end" << endl;
}
