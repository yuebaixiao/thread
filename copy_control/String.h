#include <memory>

class String{
 public:
  String(const char*);
 private:
  std::pair<char*, char*> alloc_n_copy
  (const char* b, const char* e);
  static std::allocator<char> alloc;
  std::string* elements;
  std::string* first_free;
  std::string* cap;
};

std::allocator<char> String::alloc;
