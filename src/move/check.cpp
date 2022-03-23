#include "move_semantics.hpp"
#include "log_initer.hpp"
#include "log_int.hpp"



int main() {
  LogIniter::GetInstance(LogType::GV);
  FUNC_LOG;

  LOG_INT_INIT_BY_VALUE(clear, 42);

  LOG_INT_INIT_BY_VALUE(for_lvref, 42);
  LogInt& lvalue_ref = for_lvref;

  LOG_INT_INIT_BY_VALUE(for_rvref, 42);
  LogInt&& rvalue_ref = static_cast<LogInt&&>(for_rvref);

  LOG_INT_INIT_BY_OTHER(clear_result, my_move(clear));
  LOG_INT_INIT_BY_OTHER(lvalue_result, my_move(lvalue_ref));
  LOG_INT_INIT_BY_OTHER(rvalue_result, my_move(rvalue_ref));

  return 0;
}
