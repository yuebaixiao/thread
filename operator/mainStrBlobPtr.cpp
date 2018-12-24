#include "StrBlob.h"
#include "StrBlobPtr.h"
#include <iostream>

using namespace std;
int main(){
  StrBlob s1{"11", "22"};
  StrBlobPtr p1 = s1.begin();
  StrBlobPtr tm = ++p1;
  cout << tm->size() << endl;
  p1--;
  tm = p1;
  cout << *tm << endl;
}
