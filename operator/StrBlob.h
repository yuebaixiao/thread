#include <memory>
#include <string>
#include <vector>

class StrBlob{
  friend bool operator==(const StrBlob&, const StrBlob&);
  friend bool operator!=(const StrBlob&, const StrBlob&);
 public:
  typedef std::vector<std::string>::size_type size_type;
  StrBlob();
  StrBlob(std::initializer_list<std::string>);
  size_type size() const{return data->size();}
  bool empty()const {return data->empty();}
  void push_back(const std::string& t){data->push_back(t);}
  void pop_back();
  std::string& front();
  std::string& back();

  std::string& operator[](size_type);
  const std::string& operator[](size_type)const;
  
 private:
  std::shared_ptr<std::vector<std::string>> data;
  void check(size_type, const std::string&) const;
};
bool operator==(const StrBlob&, const StrBlob&);
bool operator!=(const StrBlob&, const StrBlob&);
