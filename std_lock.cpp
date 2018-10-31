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
  std::lock(d1.m, d2.m);
  //造成死锁
  //d1.add_list(11);
  lock_guard<mutex> lock_a(d1.m, std::adopt_lock);
  lock_guard<mutex> lock_b(d2.m, std::adopt_lock);
  swap(d1.alist, d2.alist);
}
int main(){
  data_protect d1, d2;
  swap(d1, d2);
  d1.add_list(11);
}
