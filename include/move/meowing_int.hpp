#ifndef MEOWING_INT_HPP
#define MEOWING_INT_HPP

#include "log_int.hpp"

namespace cats {

class MeowingInt {
 public:
  void Meow();

  void Set(LogInt value);

 private:
  LOG_INT_DECL(value_);

};

}

#endif /* meowing_int.hpp */
