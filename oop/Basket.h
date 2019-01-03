#include "Quote3.h"
#include <set>

class Basket{
 public:
  void add_item(const std::shared_ptr<Quote>& sale){
    items.insert(sale);
  }
  double total_receipt(std::ostream) const;
 private:
  static bool compare(const std::shared_ptr<Quote>& lhs,
		      const std::shared_ptr<Quote>& rhs){
    return lhs->isbn() < rhs->isbn();
  }
  std::multiset<std::shared_ptr<Quote, decltype(compare)*>
    items{compare};
};
