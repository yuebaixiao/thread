
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


class Pub_Pub_derv : private Pub_derv{
  friend void pubpubfri(Pub_Pub_derv&);
  int f(){
    Base& b = *this;//只用当子类B以public或者protected方式继承父类A后，在子类B的子类C的成员函数和子类B的子类C的友元里，才能把子类B的对象转换成父类A的对象
    pub_mem();
    return prot_mem;
  }
  //char g(){return pri_mem;}//error
};

class Pro_Pro_derv : private Pro_derv{
  friend void proprofri(Pro_derv&);
  int f(){
    Base& b = *this;//只用当子类B以public或者protected方式继承父类A后，在子类B的子类C的成员函数和子类B的子类C的友元里，才能把子类B的对象转换成父类A的对象
    pub_mem();
    return prot_mem;
  }
  //char g(){return pri_mem;}//error
};

class Pri_Pri_derv : private Pri_derv{
  friend void priprifri(Pri_derv&);
  int f(){
    //Base* b = *this;//error,只用当子类B以public或者protected方式继承父类A后，在子类B的子类C的成员函数和子类B的子类C的友元里，才能把子类B的对象转换成父类A的对象
    //pub_mem();
    //return prot_mem;
  }
};

void pubpubfri(Pub_derv& pd){
  Base& b = pd;//只用当子类B以public或者protected方式继承父类A后，在子类B的子类C的成员函数和子类B的子类C的友元里，才能把子类B的对象转换成父类A的对象
}
void proprofri(Pro_derv& pd){
  Base& b = pd;//只用当子类B以public或者protected方式继承父类A后，在子类B的子类C的成员函数和子类B的子类C的友元里，才能把子类B的对象转换成父类A的对象
}
void priprifri(Pri_derv& pd){
  //Base& b = pd;//error,只用当子类B以public或者protected方式继承父类A后，在子类B的子类C的成员函数和子类B的子类C的友元里，才能把子类B的对象转换成父类A的对象
}
int main(){
  Pub_derv pub;
  Pro_derv pro;
  Pri_derv pri;
  
  Base& b1 = pub;
  //Base& b2 = pro;
  //Base& b3 = pri;
}
