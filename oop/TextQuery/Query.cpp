#include "Query.h"

std::ostream& operator<<(std::ostream& os, const Query& q){
  //Query::rep通过它的Query_base指针对rep()进行虚调用
  return os << q.rep();
}

Query::Query(const std::string& s) : q(new WordQuery(s)){
    std::cout << "Query pub" << std::endl;
}

QueryResult NotQuery::eval(const TextQuery&)const{

}

QueryResult AndQuery::eval(const TextQuery&)const{

}

QueryResult OrQuery::eval(const TextQuery&)const{

}
