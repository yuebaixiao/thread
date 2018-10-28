#include <iostream>
#include <thread>
#include <string>
#include <unistd.h>

using namespace std;

void f(int i, string* s){
  while(1){
    cout << i << ", " << *s << endl;
  }
}
/*
int main(){
  //char* s = "abcd";
  string* s = new string("abcd");

  thread t(f, 3, s);
  delete s;
  t.detach();
  //pthread_exit(NULL);
  sleep(5);
}
*/
void f1(int& i){
  
  while(1){
    cout << i++ << endl;
    if(i > 13) break;
  }
}

int main(){
  //int* ip = new int(100);
  //delete ip;
  int ip = 1;

  thread t(f1, ref(ip));
  t.detach();
  //sleep(2);
  cout << "afger:" << ip << endl;
  //pthread_exit(NULL);

  //sleep(11);
}
