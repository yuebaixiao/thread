#ifndef __QUERYRESULT_H__
#define __QUERYRESULT_H__

#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <memory>

class QueryResult{
  friend std::ostream& print(std::ostream&, const QueryResult&);
public:
  using line_no = std::vector<std::string>::size_type;
  QueryResult(std::string s, std::shared_ptr<std::set<line_no>> p,
              std::shared_ptr<std::vector<std::string>> f):
    sought(s), lines(p), file(f){}
private:
  std::string sought;//查询的单词                                                    
  std::shared_ptr<std::set<line_no>> lines;//出现的行号                                   
  std::shared_ptr<std::vector<std::string>> file;
};
//QueryResult类的友元声明
std::ostream& print(std::ostream&, const QueryResult&);

#endif
