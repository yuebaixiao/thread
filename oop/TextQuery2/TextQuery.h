#ifndef __TEXTQUERY_H__
#define __TEXTQUERY_H__

#include "QueryResult.h"
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <vector>
#include <string>
#include <memory>

using namespace std;
class TextQuery{
 public:
  using line_no = std::vector<std::string>::size_type;

  TextQuery(ifstream& is);  
  QueryResult query(const std::string &sought) const;
 private:
  std::shared_ptr<std::vector<std::string>> file;
  std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};

#endif
