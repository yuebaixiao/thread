#include <mutex>
#include <thread>
#include <iostream>

class X{
  int connect_detail;
  std::once_flag connect_init_flag;
  void open_connection(){
    std::cout << "open:" << connect_detail << std::endl;
    //open();
  }

public:
  X(int detail):connect_detail(detail){}
  void send_data(){
    std::call_once(connect_init_flag, &X::open_connection, this);
    //send();
  }
  void receive_data(){
    std::call_once(connect_init_flag, &X::open_connection, this);
    //receive();
  }
};

int main(){
  X x(10);
  x.send_data();
  x.receive_data();
}
