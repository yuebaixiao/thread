#include <iostream>
#include <thread>
#include <string>
#include <unistd.h>

using namespace std;

void f(int i, char* s){
  while(1){
    cout << i << ", " << s << endl;
  }
}

int main(){
  char* s = "abcd";
  thread t(f, 3, s);
  t.detach();
  pthread_exit(NULL);
  //sleep(1);
}
