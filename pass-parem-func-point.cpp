#include <iostream>
#include <thread>
#include <string>
#include <unistd.h>

using namespace std;

class Test{
public:
  void func(int& i){
    cout << i << endl;
  }
};
int main(){
  Test da;
  int i = 10;
  thread t(&Test::func, &da, ref(i));
  t.detach();
  pthread_exit(NULL);
}
