#include "func_logger.hpp"
#include "con_logger.hpp"
#include "log_int.hpp"
#include "log_initer.hpp"
#include "html_logger.hpp"
#include "move_semantics.hpp"

template<typename T, typename Arg>
T* Alloc(Arg&& arg) {
  FUNC_LOG;
  return new T(my_forward<Arg>(arg));
}

class MeowedInt {
 public:
  void SetValue(LogInt value) {
    FUNC_LOG;
    value_ = my_move(value);
  }

 protected:
  LOG_INT_DECL(value_);
  /*
    implementation is skipped
  */
};

int main() {
  LogIniter::GetInstance(LogType::GV);
  FUNC_LOG;

  LOG_INT_INIT_BY_VALUE(a, 42);
  MeowedInt meowed_int;
  meowed_int.SetValue(my_move(a));

  return 0;
}
