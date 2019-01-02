

class Base{
  friend class Friend;
public:
  void pub_mem();
protected:
  int prot_mem;
private:
  char pri_mem;
};

class D : public Base{
private:
  int j;
};

class Friend{
  friend class C;
  friend void fri(Base& b);
  int f(Base& b){
    return b.pri_mem;
  }
  int f1(D& d){
    //return d.j;
  }
  int f2(D& d){
    return d.pri_mem;
  }
};

class Bom : public Friend{
  int mem(Base& b){
    //return b.pri_mem;
  }
};

void fri(Base& b){
  //b.pri_mem;//error
}
class C{
  int f(Base& b){
    
    //return b.pri_mem;//error
  }
};
int main(){

}
