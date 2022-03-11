#include "func_logger.hpp"

FuncLogger::FuncLogger(const std::string& func) {
  ILogger::curr_logger_->LogFuncEntry(func);
}

FuncLogger::~FuncLogger() {
  ILogger::curr_logger_->LogFuncEnd();
}
