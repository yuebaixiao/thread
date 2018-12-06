#include <set>
#include <string>

class Message;
class Folder{
public:
  Folder() = default;
  //Folder(const Message* const);
  void addMsg(Message* msg);
  void remMsg(Message* msg);
private:
  std::set<Message*> msgs;
};

void Folder::addMsg(Message* msg){
  msgs.insert(msg);
}

void Folder::remMsg(Message* msg){
  msgs.erase(msg);
}

class Message{
  friend class Folder;
  friend void swap(Message&, Message&);
public:
  explicit Message(const std::string& str = "") : contents(str){}
  Message(const Message&);
  Message& operator=(const Message&);
  ~Message();

  void save(Folder&);
  void remove(Folder&);
private:
  std::string contents;
  std::set<Folder*> folders;
};

void Message::save(Folder& fo){
  fo.addMsg(this);
  folders.insert(&fo);
}

void Message::remove(Folder& fo){
  fo.remMsg(this);
  folders.erase(&fo);
}

Message::Message(const Message& rhs) :
  contents(rhs.contents), folders(rhs.folders){
  for(auto a : folders){
    a->addMsg(this);
  }
}

Message::~Message(){
  for(auto a : folders){
    a->remMsg(this);
  }
}

Message& Message::operator=(const Message& msg){
  //必须先删除在添加。
  //理由：如果是自己给自己赋值的话，先添加，再删除，就会再把自己删除掉.
  for(auto a : folders){
    a->remMsg(this);
  }
  contents = msg.contents;
  for(auto a : msg.folders){
    a->addMsg(this);
  }
  return *this;
}

void swap(Message& lhs, Message& rhs){

  using std::swap;//本例子并不需要，但是个好习惯.好处是，在下面调用swap时，如果有自己类型的swap函数，就会调用自己类型的swap函数，如果没有，才会调用std::swap。
  
  swap(lhs.contents, rhs.contents);

  //必须先删除在添加。
  //理由：如果是自己给自己赋值的话，先添加，再删除，就会再把自己删除掉.
  for(auto a : lhs.folders){
    a->remMsg(&lhs);
  }
  for(auto a : rhs.folders){
    a->remMsg(&rhs);
  }

  for(auto a : lhs.folders){
    a->addMsg(&rhs);
  }
  for(auto a : rhs.folders){
    a->addMsg(&lhs);
  }
}

int main(){}
