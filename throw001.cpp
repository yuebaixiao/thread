#include <iostream>
#include <string>

class A{
  int data;
public:
  A(int d = 10) : data(d){}
  int _data() const {return data;}
};
double div1(double a, double b){
  if(b == 0){
    //throw std::string("error");//进入string的catch
    //throw "error";//进入const char*的catch
    //throw 1;//进入int的catch
    throw A(101);
    
  }
  return a / b;
}

int main(){
  try{
    div1(1, 0);
  }
  catch(A a){
    std::cout << a._data() << std::endl;
  }
  catch(int a){
    std::cout << a << std::endl;
  }
  catch(const char* s){
    std::cout << "char*" << std::endl;
    std::cout << s << std::endl;
  }
  catch(std::string s){
    std::cout << "string" << std::endl;
    std::cout << s << std::endl;
  }
  catch(...){
    using namespace std;
    cout << "...." << endl;
    
  }
}
