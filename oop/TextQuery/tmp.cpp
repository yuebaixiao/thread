#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <memory>

using namespace std;


class QueryResult{
  friend ostream& print(ostream&, const QueryResult&);
public:
  using line_no = vector<string>::size_type;
  QueryResult(string s, shared_ptr<set<line_no>> p,
              shared_ptr<vector<string>> f):
    sought(s), lines(p), file(f){}
private:
  string sought;//查询的单词                                                    
  shared_ptr<set<line_no>> lines;//出现的行号                                   
  shared_ptr<vector<string>> file;
};
//QueryResult的友元函数                                                         
ostream& print(ostream& os, const QueryResult& qr){
  os << qr.sought << " 出现了：" << qr.lines->size() << "次" << endl;
  for(auto num : *qr.lines){
    os << "\t(行号 " << num + 1 << ")"
       << *(qr.file->cbegin() + num) << endl;
  }
  return os;
}
class TextQuery{
public:
  using line_no = vector<string>::size_type;
  TextQuery(ifstream& is) : file(new vector<string>){
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
  QueryResult query(const string &sought) const{
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
private:
  shared_ptr<vector<string>> file;
  map<string, shared_ptr<set<line_no>>> wm;
};
int main(){
  ifstream infile("/home/ys/cpp/thread/oop/TextQuery/search_text");
  TextQuery tq(infile);
  while(true){
    cout << "输入要查找的单词: q 退出";
    string s;
    if(!(cin >> s) || s == "q")break;
    print(cout, tq.query(s)) << endl;;
  }
}
