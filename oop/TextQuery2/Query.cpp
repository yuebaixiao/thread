#include "Query.h"
#include <algorithm>
#include <memory>

/*
std::ostream& operator<<(std::ostream& os, const Query& q){
  //Query::rep通过它的Query_base指针对rep()进行虚调用
  return os << q.rep();
}
*/
Query::Query(const std::string& s) : q(new WordQuery(s)){
    std::cout << "Query pub" << std::endl;
}

QueryResult NotQuery::eval(const TextQuery& text)const{
  //通过Query运算对象对eval进行虚调用
  auto result = query.eval(text);
  //开始时结果set为空
  auto ret_lines = std::make_shared<std::set<line_no>>();
  auto beg = result.begin();
  auto end = result.end();
  //对于输入文件的每一行，如果该行不在result当中，则将其添加到ret_lines
  auto sz = result.get_file()->size();
  for(size_t n = 0; n != sz; ++n){
    //如果还没有处理完result的所以行
    //检查当前行是否存在
    if(beg == end || *beg != n){
      ret_lines->insert(n);
    }
    else if(beg != end){
      ++beg;//继续获取reslut的下一行
    }
  }

  return QueryResult(rep(), ret_lines, result.get_file());
}

QueryResult AndQuery::eval(const TextQuery& text)const{
  //通过Query成员lhs,rhs进行虚调用
  //调用eval返回每个对象的QueryResult
  auto right = rhs.eval(text);
  auto left  = lhs.eval(text);
  //保存left和right交集的set
  auto ret_lines =
    std::make_shared<std::set<line_no>>();
  //将两个范围的交集写入一个目的迭代其中。
  std::set_intersection(left.begin(), left.end(),
			right.begin(), right.end(),
			inserter(*ret_lines, ret_lines->begin()));
  return QueryResult(rep(), ret_lines, left.get_file());
}

QueryResult OrQuery::eval(const TextQuery& text)const{
  //通过Query成员lhs,rhs进行虚调用
  //调用eval返回每个对象的QueryResult
  auto right = rhs.eval(text);
  auto left  = lhs.eval(text);
  //将左侧运算对象的行号拷贝到结果set中
  auto ret_lines =
    std::make_shared<std::set<line_no>>(left.begin(), left.end());
  //插入右侧运算对象所得的行号
  ret_lines->insert(right.begin(), right.end());
  //返回一个新的QueryResult，它表示lhs和rhs的并集
  return QueryResult(rep(), ret_lines, right.get_file());
}
