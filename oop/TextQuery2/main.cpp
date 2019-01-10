#include "Query.h"

//QueryResult的友元函数                                                         
ostream& print(ostream& os, const QueryResult& qr){
  os << qr.sought << " 出现了：" << qr.lines->size() << "次" << endl;
  for(auto num : *qr.lines){
    os << "\t(行号 " << num + 1 << ")"
       << *(qr.file->cbegin() + num) << endl;
  }
  return os;
}

int main(){
  ifstream infile("/home/ys/cpp/thread/oop/TextQuery/search_text");
  TextQuery tq(infile);
  Query q = Query("fiery") & Query("bird") | Query("wind");//OK
  //Query q = Query("fiery") | Query("bird");//OK
  //Query q("Daddy");//OK
  //Query q = ~Query("Alice");//OK
  print(std::cout, q.eval(tq)) << std::endl;
}
