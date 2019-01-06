#ifndef __NOTQUERY_H__
#define __NOTQUERY_H__

#include "Query.h"//query.rep()

class QueryResult;
class TextQuery;

class NotQuery : public Query_base{
  friend Query operator~(const Query&);
  NotQuery(const Query& q)
    :query(q){}
  std::string rep() const {
    return "~(" + query.rep() + ")";
  }
  QueryResult eval(const TextQuery&)const;
  Query query;
};

inline Query operator~(const Query& op){
  std::shared_ptr<Query_base> tmp(new NotQuery(op));
  return Query(tmp);
}
#endif
