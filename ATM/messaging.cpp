#include <mutex>
#include <condition_variable>
#include <queue>
#include <memory>

namespace messaging{
  struct message_base{
    virtual ~message_base(){}
  };
  template<typename Msg>
  struct wrapped_message: message_base{//每个消息类型有特殊的定义
    Msg contents;
    explicit wrapped_message(Msg const& con) : contents(con){}
  };

  class queue{//消息队列
    std::mutex m;
    std::condition_variable c;
    std::queue<std::shared_ptr<message_base>> q;//实际的队列存储message_base的指针
  public:
    template<typename T>
    void push(T const& msg){
      std::lock_guard<std::mutex> lk(m);
      q.push(std::make_shared<wrapped_message<T>>(msg));//将发出的消息封装并且存储指针
      c.notify_all();//通知所有等待的线程
    }

    std::shared_ptr<message_base> wait_and_pop(){
      std::unique_lock<std::mutex> lk(m);
      c.wait(lk, [&]{return !q.empty();});//阻塞直到队列非空
      auto res = q.front();
      q.pop();
      return res;
    }
  };

  class sender{
    queue* q;//sender就是封装了队列指针
  public:
    sender():q(nullptr){}//默认的sender没有队列
    explicit sender(queue* q_) : q(q_){}//允许从指向队列的指针进行构造

    template<typename Message>
    void send(Message const& msg){
      if(q){
	q->push(msg);//在队列上发送推送消息
      }
    }
  };


  class close_queue{};
  class dispatcher{
    queue* q;
    bool chained;

    dispatcher(dispatcher const&) = delete;
    dispatcher& operator=(dispatcher const&) = delete;

    template<
      typename Dispatcher,
      typename Msg,
      typename Func>
    friend class TemplateDispatcher;

    void wait_and_dispatch(){
      while(true){//循环，等待和调度消息
	auto msg = q->wait_and_pop();
	dispatch(msg);
      }
    }

    bool dispatch(std::shared_ptr<message_base> const& msg){
      //dispatch()检查close_queue消息，并抛出
      if(dynamic_cast<wrapped_message<close_queue>*>(msg.get())){
	throw close_queue();
      }
      return false;
    }
  public:
    dispatcher(dispatcher&& other)://调度器可以移动
      q(other.q), chained(other.chained){
      other.chained = true;//源头不可以等待消息
    }
    explicit dispatcher(queue* q_) : q(q_), chained(false){}
  };
  
  class receiver{
    queue q;//一个receiver拥有此队列
  public:
    operator sender(){//看不懂？？？
      return sender(&q);
    }

    dispatcher wait(){
      return dispatcher(&q);
    }
  };

}

int main(){}
