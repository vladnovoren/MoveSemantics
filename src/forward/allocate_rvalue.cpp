#include "forward/allocate_forward.hpp"
#include "log_initer.hpp"
#include "log_int.hpp"

int main() {
  LogIniter::GetInstance(LogType::GV);
  FUNC_LOG;

  LogInt* p1 = Allocate<LogInt>(LogInt(42));
  delete p1;

  return 0;
}
