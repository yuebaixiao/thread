#ifndef __ORQUERY_H__
#define __ORQUERY_H__

#include "BinaryQuery.h"

class OrQuery : public BinaryQuery{
  friend Query operator|(const Query&, const Query&);
  OrQuery(const Query& l, const Query& r)
    : BinaryQuery(l, r, "|"){}
  QueryResult eval(const TextQuery&) const;
};

inline Query operator|(const Query& lhs, const Query& rhs){
  return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}

#endif
