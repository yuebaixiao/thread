
class Base{
public:
  void pub_mem();
protected:
  int prot_mem;
private:
  char pri_mem;
};

class Pub_derv : public Base{
  int f(){
    pub_mem();
    return prot_mem;
  }
  //char g(){return pri_mem;}//error
};

class Pro_derv : protected Base{
  int f(){
    pub_mem();
    return prot_mem;
  }
  //char g(){return pri_mem;}//error
};

class Pri_derv : private Base{
  int f(){
    pub_mem();
    return prot_mem;
  }
};


class Pub_Pub_derv : public Pub_derv{
  int f(){
    pub_mem();
    return prot_mem;
  }
  //char g(){return pri_mem;}//error
};

class Pri_Pri_derv : private Pri_derv{
  int f(){
    //pub_mem();
    //return prot_mem;
  }
};


int main(){
  Pub_derv pub;
  Pro_derv pro;
  Pri_derv pri;
  
  Base& b1 = pub;
  Base& b2 = pro;
  //Base& b3 = pri;
}
