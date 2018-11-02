#include <mutex>
#include <climits>//ULONG_MAX

class hierarchical_mutex{
  std::mutex mtx;
  unsigned long const hcl_val;
  unsigned long pre_hcl_val;

  static thread_local unsigned long this_hcl_val;

  void check_for_hcl_violaction(){
    if(this_hcl_val <= hcl_val){
      throw std::logic_error("mutex hierarchy violated");
    }
  }
  void update_hierarchy_value(){
    pre_hcl_val = this_hcl_val;
    this_hcl_val = hcl_val;
  }

public:
  explicit hierarchical_mutex(unsigned long val):
    hcl_val(val), pre_hcl_val(0){}

  void lock(){
    check_for_hcl_violaction();
    mtx.lock();
    update_hierarchy_value();
  }

  void unlock(){
    this_hcl_val = pre_hcl_val;
    mtx.unlock();
  }

  bool try_lock(){
    check_for_hcl_violaction();
    if(!mtx.try_lock())
      return false;
    update_hierarchy_value();
    return true;
  }
};

thread_local unsigned long
hierarchical_mutex::this_hcl_val(ULONG_MAX);

hierarchical_mutex high_level_mutex(10000);
hierarchical_mutex low_level_mutex(5000);

int do_low_level_stuff(){
  return 1;
}
int low_level_func(){
  std::lock_guard<hierarchical_mutex> lk(low_level_mutex);
  return do_low_level_stuff();
}

void high_level_stuff(int param){
  
}
void high_level_func(){
  std::lock_guard<hierarchical_mutex> lk(high_level_mutex);
  high_level_stuff(low_level_func());
}

void thread_a(){
  high_level_func();
}

hierarchical_mutex other_mutex(100);
void do_other_stuff(){
  
}

void other_stuff(){
  high_level_func();
  do_other_stuff();
}

void thread_b(){
  std::lock_guard<hierarchical_mutex> lk(other_mutex);
  other_stuff();
}

int main(){

}
