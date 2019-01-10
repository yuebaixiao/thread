#include "TextQuery.h"

using namespace std;

TextQuery::TextQuery(ifstream& is) : file(new vector<string>){
  string text;
  while(getline(is, text)){//读文件的每一行                                   
    file->push_back(text);
    int n = file->size() - 1;//当前行号                                       
    istringstream line(text);//将行文本分解为单词                             
    string word;
    while(line >> word){
      //非常重要，必须用引用，要不然就会拷贝一个新的set给lines，不是原来的    
      auto &lines = wm[word];//lines是shared_ptr                              
      if(!lines)
	lines.reset(new set<line_no>);
      lines->insert(n);
    }
  }
}

QueryResult TextQuery::query(const string &sought) const{
  //如果没有找到sought，返回指向此set的一个智能指针                           
  static shared_ptr<set<line_no>> nodata(new set<line_no>);
  auto ret = wm.find(sought);
  if(ret == wm.end()){
    return QueryResult(sought, nodata, file);//没有找到                       
  }
  else{
    return QueryResult(sought, ret->second, file);
  }
}

