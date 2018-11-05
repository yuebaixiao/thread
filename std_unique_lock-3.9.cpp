#include <list>
#include <iostream>
#include <mutex>
#include <algorithm>
#include <thread>
#include <unistd.h>

using namespace std;
class data_protect;
void swap(data_protect& , data_protect& );
//是线程安全的
class data_protect{
  friend void swap(data_protect& , data_protect& );
private:
  list<int> alist{1,2};
  mutex m;
public:  
  void add_list(int val){
    //操作双向链表时，加锁了
    lock_guard<mutex> g(m);
    alist.push_back(val);
  }
  bool contains(int val){
    //操作双向链表时，加锁了
    lock_guard<mutex> g(m);
    return find(alist.begin(), alist.end(), val) != alist.end();
  }
};

void swap(data_protect& d1, data_protect& d2){
  //if(d1 == d2) return;

  //造成死锁
  //d1.add_list(11);
  unique_lock<mutex> lock_a(d1.m, std::defer_lock);
  unique_lock<mutex> lock_b(d2.m, std::defer_lock);
  std::lock(lock_a, lock_b);
  swap(d1.alist, d2.alist);

  //有unlock成员函数,并可以手动调用unlock函数
  //如果没有持有锁，就调用unlock成员函数就会导致程序崩溃。所以要检查是否拥有锁。
  if(lock_a.owns_lock() && lock_b.owns_lock()){
    lock_a.unlock();
    lock_b.unlock();
  }
}
int main(){
  data_protect d1, d2;
  swap(d1, d2);
  d2.add_list(11);
}
