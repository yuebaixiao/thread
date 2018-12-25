#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <functional>

class LineStr{
public:
  LineStr(std::istream& in = std::cin) : is(in){}
  std::string operator()(){
    std::string str;
    std::getline(is, str);
    return is ? str : std::string();
  }
private:
  std::istream& is;
};

class Isequ{
public:
  Isequ(int i = 0) : val(i){}
  bool operator()(int t){
    return val == t;
  }
private:
  int val;
};

class StableSort{
public:
  bool operator()(const std::string& a, const std::string& b){
    return a.size() < b.size();
  }
};

class SizeCmp{
public:
  SizeCmp(std::size_t s) : sz(s){}
  bool operator()(const std::string& str)const{
    return str.size() > sz;
  }
private:
  std::size_t sz;
};

int main(){
  /*
  LineStr ls;
  std::cout << ls() << std::endl;
  */
  /*
  std::vector<int> vi{23,3,5,6,78,3};
  Isequ iq(3);
  std::replace_if(vi.begin(), vi.end(), iq, 9);
  for(int i : vi)
    std::cout << i << " ";
  std::cout << std::endl;
  */
  /*
  std::vector<std::string> vs{"1234", "123", "a", "bc"};
  //stable_sort(vs.begin(), vs.end(), [](const std::string& a,
  //			       const std::string& b){
  //		return a.size() < b.size();
  //	      });
  //std::stable_sort(vs.begin(), vs.end(), StableSort());
  StableSort ss;
  std::stable_sort(vs.begin(), vs.end(), ss);
  std::size_t sz = 2;
  //auto b = std::find_if(vs.cbegin(), vs.cend(), [sz](const std::string& a){
  //    return a.size() > sz;
  //  });
  SizeCmp sc(3);
  auto b = std::find_if(vs.cbegin(), vs.cend(), sc);
  for_each(b, vs.cend(), [](const std::string& s){
      std::cout << s << " ";
    });
  std::cout << std::endl;
  for(auto s : vs)
    std::cout << s << " ";
  std::cout << std::endl;
  */
  using std::placeholders::_1;
  std::vector<int> iv {12,213,123123,434344,213232};
  int cnt = std::count_if(iv.cbegin(), iv.cend(),
			  std::bind(std::greater<int>(), _1, 1024));
  std::cout << cnt << std::endl;

  std::vector<std::string> sv{"pooh", "pooh", "11","pooh","22"};
  auto idx = std::find_if(sv.cbegin(), sv.cend(),
			  std::bind(std::not_equal_to<std::string>(),_1, "pooh"));
  std::cout << *idx << std::endl;

  std::vector<int> iv2 {12,3,12,4,21};
  std::transform(iv2.cbegin(), iv2.cend(), iv2.begin(),
		 std::bind(std::multiplies<int>(), _1, 2));
  for(auto i : iv2)
    std::cout << i << " ";
  std::cout << std::endl;
  
}
