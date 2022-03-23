#include "log_initer.hpp"
#include "log_int.hpp"

template<typename T>
void Func(T&& object) {
  FUNC_LOG;
  LOG_INT_DECL(dst);
  dst = static_cast<T&&>(object);
}

int main() {
  LogIniter::GetInstance(LogType::GV);
  FUNC_LOG;

  LOG_INT_INIT_BY_VALUE(a, 42);
  Func(a);
  Func(LogInt());

  return 0;
}
