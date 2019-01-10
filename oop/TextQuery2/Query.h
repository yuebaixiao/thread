#ifndef __QUERY_H__
#define __QUERY_H__

#include <string>
//#include <memory>
#include <iostream>
#include "TextQuery.h"

class QueryResult;
class Query;

class Query_base{
  friend class Query;
 protected:
  using line_no = TextQuery::line_no;
  virtual ~Query_base() = default;
 private:
  virtual QueryResult eval(const TextQuery&) const = 0;
  virtual std::string rep() const = 0;

  virtual Query_base* clone() const = 0;
};

class Query{
  friend Query operator~(const Query&);//需要访问私有的构造函数
  friend Query operator|(const Query&, const Query&);//需要访问私有的构造函数
  friend Query operator&(const Query&, const Query&);//需要访问私有的构造函数
 public:
  Query(const std::string&);//构建一个新的WordQuery
  ~Query(){
    std::cout << "Free" << std::endl;
    delete q;
  }

  Query(const Query& tmp){
    if(&tmp != this){
      std::cout << "copy Query" << std::endl;
      q = tmp.q->clone();
    }
  }

  Query& operator=(const Query& tmp){
    std::cout << "= Query" << std::endl;
  }

  // 接口函数：调用对应的Query_base操作
  QueryResult eval(const TextQuery& t) const{
    return q->eval(t);
  }
  std::string rep()const{
    return q->rep();
  }

 private:
  /*
  Query(std::shared_ptr<Query_base> query)
    :q(query){
    std::cout << "Query pri:" << std::endl;
  }
  */

  Query(Query_base* qb)
    :q(qb){}
  
  Query_base* q;
  
};

class WordQuery : public Query_base{
  friend class Query;//Query 使用WordQuery的私有构造函数
  WordQuery(const std::string& s)
    : query_word(s){
    std::cout << "WordQuery:" << s << std::endl;
  }
  QueryResult eval(const TextQuery& t)const{
    return t.query(query_word);
  }
  std::string rep()const{
    return query_word;
  }

  virtual WordQuery* clone() const {
    return new WordQuery(*this);
  }
  std::string query_word;
};

class NotQuery : public Query_base{
  friend Query operator~(const Query&);
  NotQuery(const Query& q)
    :query(q){//调用Query的拷贝构造函数
    std::cout << "NotQuery" << std::endl;
  }
  std::string rep() const {
    return "~(" + query.rep() + ")";
  }
  
  virtual NotQuery* clone() const {
    return new NotQuery(*this);
  }
  
  QueryResult eval(const TextQuery&)const;
  Query query;
};

inline Query operator~(const Query& op){
  //return std::shared_ptr<Query_base>(new NotQuery(op));
  Query_base* tmp = new NotQuery(op);
  return Query(tmp);
}


class BinaryQuery : public Query_base{
 protected:
  BinaryQuery(const Query& l, const Query& r,
	      std::string s)
    : lhs(l), rhs(r), opSym(s){
    std::cout << "BinaryQuery" << std::endl;
  }
  std::string rep() const {
    return "(" + lhs.rep() + " "
      + opSym + " "
      + rhs.rep() + ")";
  }
  Query lhs, rhs;
  std::string opSym;
};

class AndQuery : public BinaryQuery{
  friend Query operator&(const Query&, const Query&);
  AndQuery(const Query& l, const Query& r)
    : BinaryQuery(l, r, "&"){
    std::cout << "AndQuery" << std::endl;
  }
  QueryResult eval(const TextQuery&) const;
  
  virtual AndQuery* clone() const {
    return new AndQuery(*this);
  }
};

inline Query operator&(const Query& lhs, const Query& rhs){
  return new AndQuery(lhs, rhs);
}

class OrQuery : public BinaryQuery{
  friend Query operator|(const Query&, const Query&);
  OrQuery(const Query& l, const Query& r)
    : BinaryQuery(l, r, "|"){
    std::cout << "OrQuery" << std::endl;
  }
  
  virtual OrQuery* clone() const {
    return new OrQuery(*this);
  }
  QueryResult eval(const TextQuery&) const;
};

inline Query operator|(const Query& lhs, const Query& rhs){
  return new OrQuery(lhs, rhs);
}

#endif
