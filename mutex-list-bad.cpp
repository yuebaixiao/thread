#include <list>
#include <iostream>
#include <mutex>
#include <algorithm>
#include <thread>
#include <unistd.h>

using namespace std;

//是线程安全的
class data_protect{
public:
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
  //参数接受一个外来的函数，并把双向链表传递给了外来的函数
  template<typename Function>
  void do_data(Function func){
    lock_guard<mutex> g(m);
    func(alist);
  }
};

list<int>* unprotect_list;
//外来的函数接收到了双向链表的引用，并把这个双向链表暴露给外面的非保护的双向链表的指针
void bad_func(list<int>& alist){
  unprotect_list = &alist;
}

void gl(data_protect& dp){
  dp.do_data(bad_func);
  //这个插入操作没有加锁，所以不是线程安全的
  unprotect_list->push_back(99);
}
int main(){
  data_protect dp;
  gl(dp);
  //alist被改变了
  for(auto& s : dp.alist){
    cout << s << endl;
  }
}
