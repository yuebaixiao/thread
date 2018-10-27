#include <iostream>
#include <thread>
#include <unistd.h>

using namespace std;

class bad{
public:
  bad(int* i) : data(i){
  cout << "addr2:" << data << endl;
  }
  void operator()(){
    for(unsigned j = 0; j < 100000000000000000; ++j){
      something(data);
    }
  }
private:
  void something(int* i){
    //*i = 100;
    cout << *i << endl;
  };
  int* data;
};

void func(){
  int* local = new int(1001);
  cout << "addr1:" << local << endl;
  bad b(local);
  thread t(b);
  //cout << "before join " << *local << endl;
  //delete local;
  cout << "end delete" << endl;
  t.detach();
  //t.join();

  cout << "after join " << *local << endl;
  cout << "func end" << endl;
}
int main(){
  func();
  sleep(10);
  cout << "end" << endl;
}
