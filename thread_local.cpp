#include <iostream>
#include <thread>

struct S
{
    S() {
      printf("S() called i=%d\n", i);
    }
    int i = 0;
};

//thread_local S gs;
S gs;

void foo()
{
  gs.i += 1;
  printf("foo  %p, %d\n", &gs, gs.i);
}

void bar()
{   
  gs.i += 2;
  printf("bar  %p, %d\n", &gs, gs.i);
}

int main()
{
  std::thread a(foo), b(bar);
  a.join();
  b.join();
}
