#include <memory>
#include <iostream>

class String{
  friend std::ostream& operator<<(std::ostream&, const String&);
  friend bool operator==(const String&, const String&);
  friend bool operator!=(const String&, const String&);
 public:
  String(const char*);
  size_t size() const{
    return first_free - elements;
  }
 private:
  std::pair<char*, char*> alloc_n_copy
  (const char* b, const char* e);
  static std::allocator<char> alloc;
  char* elements;
  char* first_free;
  char* cap;
};

std::allocator<char> String::alloc;
std::ostream& operator<<(std::ostream&, const String&);
bool operator==(const String&, const String&);
bool operator!=(const String&, const String&);
