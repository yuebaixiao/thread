
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
  friend void pro_fri(Pro_derv&);
  int f(){
    Base& b = *this;//不论子类B以何种方式继承父类A，在子类B的成员函数和子类B的友元（非用户代码）里，都能把子类B的对象转换成父类A的对象。
    pub_mem();
    return prot_mem;
  }
  //char g(){return pri_mem;}//error
};

class Pri_derv : private Base{
  friend void pri_fri(Pri_derv&);
  int f(){
    Base& b = *this;//不论子类B以何种方式继承父类A，在子类B的成员函数和子类B的友元（非用户代码）里，都能把子类B的对象转换成父类A的对象。
    pub_mem();
    return prot_mem;
  }
};

void pro_fri(Pro_derv& pro){
  Base& b = pro;//不论子类B以何种方式继承父类A，在子类B的成员函数和子类B的友元（非用户代码）里，都能把子类B的对象转换成父类A的对象。
}

void pri_fri(Pri_derv& pro){
  Base& b = pro;//不论子类B以何种方式继承父类A，在子类B的成员函数和子类B的友元（非用户代码）里，都能把子类B的对象转换成父类A的对象。
}
int main(){
  Pub_derv pub;
  Pro_derv pro;
  Pri_derv pri;
  
  Base& b1 = pub;
  //Base& b2 = pro;
  //Base& b3 = pri;
}
