#include <iostream>
#include <thread>
#include <unistd.h>

using namespace std;

class Int{
public:
  Int(int i = 0) : data(i){}
  int data;
};
class bad{
public:
  bad(Int* i) : data(i){
  cout << "addr2:" << data << endl;
  }
  void operator()(){
    for(unsigned j = 0; j < 10000000000; ++j){
      something(data);
    }
  }

  void something(Int* i){
    i->data = 100;
    cout << i->data << endl;
  };
  Int* data;
};

void func(){
  Int* local = new Int(10);
  cout << "addr1:" << local << endl;
  bad b(local);
  //thread t(b);
  //cout << "before join " << *local << endl;
  delete local;
  local = nullptr;
  //*local = 111;
  cout << "local addr: " << local << endl;
  cout << "b.data: " << b.data << endl;
  cout << "end delete" << endl;
  //t.detach();
  //t.join();

  //cout << "after join " << *local << endl;
  cout << "func end" << endl;
}
int main(){
  func();
  //sleep(10);
  cout << "end" << endl;
}
