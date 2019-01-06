#ifndef __ANDQUERY_H__
#define __ANDQUERY_H__

#include "BinaryQuery.h"

class AndQuery : public BinaryQuery{
  friend Query operator&(const Query&, const Query&);
  AndQuery(const Query& l, const Query& r)
    : BinaryQuery(l, r, "&"){}
  QueryResult eval(const TextQuery&) const;
};

inline Query operator&(const Query& lhs, const Query& rhs){
  return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}

#endif
