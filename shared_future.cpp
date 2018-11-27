#include <iostream>       // std::cout
#include <future>         // std::async, std::future, std::shared_future
#include <assert.h>

int do_get_value() { return 10; }
void th1(std::shared_future<int> sf){
  std::cout << sf.get() << std::endl;
}
void th2(std::shared_future<int> sf){
  std::cout << sf.get() << std::endl;
}
int main(){
  std::future<int> fut = std::async(do_get_value);
  //std::shared_future<int> sf2(std::move(fut));
  //std::shared_future<int> sf2 = fut.share();
  //std::thread t1(th1, sf2);
  //std::thread t2(th1, sf2);

  //t1.join();
  //t2.join();
  std::promise<int> pro;
  std::shared_future<int> sf1(pro.get_future());
  std::thread t1(th1, sf1);
  std::thread t2(th1, sf1);
  pro.set_value(110);
  t1.join();
  t2.join();
}
/*
int do_get_value() { return 10; }

int main ()
{
    std::future<int> fut = std::async(do_get_value);
    assert(fut.valid());
    //std::shared_future<int> shared_fut = fut.share();
    std::shared_future<int> shared_fut(std::move(fut));
    assert(!fut.valid());
    std::shared_future<int> shared_fut1 = shared_fut;
    // 共享的 future 对象可以被多次访问.
    std::cout << "value: " << shared_fut.get() << '\n';
    std::cout << "its double: " << shared_fut1.get()*2 << '\n';

    return 0;
}
*/
