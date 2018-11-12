#include <map>
#include <string>
#include <thread>
#include <mutex>
#include <functional>
#include <boost/thread/shared_mutex.hpp>

class dns_entry{

};
class dns_cache{
  std::map<std::string, dns_entry> entries;
  mutable boost::shared_mutex entry_mutex;
public:
  dns_entry find_entry(std::string const& domain)const{
    boost::shared_lock<boost::shared_mutex> lk(entry_mutex);
    std::map<std::string, dns_entry>::const_iterator const it =
      entries.find(domain);
    return (it == entries.end()) ? dns_entry() : it->second;
  }
  void update_or_add_entry(std::string const& domain, dns_entry const& dns_details){
    std::lock_guard<boost::shared_mutex> lk(entry_mutex);
    entries[domain] = dns_details;
  }
};
int main(){
  dns_entry de;
  dns_cache cache1, cache2, cache3;
  std::thread t(&dns_cache::find_entry, std::ref(cache3), "aaa");
  t.join();
  std::thread t1(&dns_cache::update_or_add_entry, std::ref(cache1), "aaa", de);
  t1.join();
  std::thread t2(&dns_cache::find_entry, std::ref(cache2), "aaa");
  t2.join();
}
