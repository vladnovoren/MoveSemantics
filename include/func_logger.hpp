#ifndef FUNC_LOGGER_HPP
#define FUNC_LOGGER_HPP

#include "ilogger.hpp"

class FuncLogger {
 public:
  FuncLogger(const std::string& func);
  ~FuncLogger();
};

#define FUNC_LOG FuncLogger func_logger(__PRETTY_FUNCTION__)

#endif /* func_logger.hpp */
