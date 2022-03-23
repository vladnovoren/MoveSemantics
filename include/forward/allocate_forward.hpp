#ifndef ALLOCATE_HPP
#define ALLOCATE_HPP

#include "ilogger.hpp"
#include "log_initer.hpp"
#include "move_semantics.hpp"

template<typename T, typename Arg>
T* Allocate(Arg&& arg) {
  FUNC_LOG;
  return new T(my_forward<Arg>(arg));
}

#endif /* allocate.hpp */
