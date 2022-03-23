#include "log_initer.hpp"
#include "log_int.hpp"
#include "move_semantics.hpp"

class Cat {
 public:
  void Meow() {
    // not implemented
    // depends on happiness
  }

  void SetHappiness(LogInt happiness) {
    happiness_ = my_move(happiness); // moving assignment
  }

 private:
  LOG_INT_DECL(happiness_);

};

int main() {
  LogIniter::GetInstance(LogType::GV);
  FUNC_LOG;

  LOG_INT_INIT_BY_VALUE(a, 42);

  Cat cat;
  cat.SetHappiness(a);
  cat.SetHappiness(LogInt());

  return 0;
}