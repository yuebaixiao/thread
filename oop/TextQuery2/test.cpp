#include <iostream>

class D{
public:
  D(int i) : d(i){}
  ~D(){
    std::cout << "D F" << std::endl;
  }
private:
  int d;
};

class E{
public:
  E(int i=0) : dp(new D(11)){}
  /*
  E(const E& e){
    if(&e != this){
      dp = e.dp;
    }
  }
  */
  ~E(){
    delete dp;
    //delete dp;
    std::cout << "E F" << std::endl;    
  }
  //private:
  D* dp;
};

int main(){
  E ep(10);
  E ep2(ep);
  //delete dp;
  return 0;
}
