#include "forward/allocate_value.hpp"
#include "log_initer.hpp"
#include "log_int.hpp"

int main() {
  LogIniter::GetInstance(LogType::GV);
  FUNC_LOG;

  LOG_INT_INIT_BY_VALUE(a, 42);

  LogInt* p1 = Allocate<LogInt>(a);
  delete p1;

  return 0;
}
