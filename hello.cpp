#include <iostream>
#include <thread>

using namespace std;
void hello(){
  //cout << "hello\n";
  cout << "hello" << endl;
}

class back_task{
public:
  void operator()() const{
    fun1();
    fun2();
  }
private:
  void fun1()const{cout << "fun1()" << endl;}
  void fun2()const{cout << "fun2()" << endl;}
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
  int data = 0;
  func fun(data);
  thread t(fun);
  for(int i = 11111; i !=0; --i){
    cout << "[!!!!!!!!!!" << i << "]" << endl;
  }
  //t.join();
  t.detach();
  cout << "complete!!!!" << endl;
}
/*
int main(){
  thread t(hello);
  t.join();

  const back_task task;
  thread t1(task);
  t1.join();
  
}
*/
