#ifndef __QUERY_H__
#define __QUERY_H__

#include <string>
#include <memory>
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
};

class Query{
  friend Query operator~(const Query&);//需要访问私有的构造函数
  friend Query operator|(const Query&, const Query&);//需要访问私有的构造函数
  friend Query operator&(const Query&, const Query&);//需要访问私有的构造函数
 public:
  Query(const std::string&);//构建一个新的WordQuery
  // 接口函数：调用对应的Query_base操作
  QueryResult eval(const TextQuery& t) const{
    return q->eval(t);
  }
  std::string rep()const{
    return q->rep();
  }

 private:
  Query(std::shared_ptr<Query_base> query)
    :q(query){
    std::cout << "Query pri:" << std::endl;
  }
  std::shared_ptr<Query_base> q;
  
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

  std::string query_word;
};

class NotQuery : public Query_base{
  friend Query operator~(const Query&);
  NotQuery(const Query& q)
    :query(q){
    std::cout << "NotQuery" << std::endl;
  }
  std::string rep() const {
    return "~(" + query.rep() + ")";
  }
  QueryResult eval(const TextQuery&)const;
  Query query;
};

inline Query operator~(const Query& op){
  //return std::shared_ptr<Query_base>(new NotQuery(op));
  std::shared_ptr<Query_base> tmp(new NotQuery(op));
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
};

inline Query operator&(const Query& lhs, const Query& rhs){
  return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}

class OrQuery : public BinaryQuery{
  friend Query operator|(const Query&, const Query&);
  OrQuery(const Query& l, const Query& r)
    : BinaryQuery(l, r, "|"){
    std::cout << "OrQuery" << std::endl;
  }
  QueryResult eval(const TextQuery&) const;
};

inline Query operator|(const Query& lhs, const Query& rhs){
  return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}

#endif
