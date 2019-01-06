#ifndef __WORDQUERY_H__
#define __WORDQUERY_H__

#include "TextQuery.h"

class WordQuery : public Query_base{
  friend class Query;//Query 使用WordQuery的私有构造函数
  WordQuery(const std::string& s)
    : query_word(s){}
  QueryResult eval(const TextQuery& t)const{
    return t.query(query_word);
  }
  std::string rep()const{
    return query_word;
  }

  std::string query_word;
};

#endif
