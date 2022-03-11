#include "ilogger.hpp"

ILogger* ILogger::curr_logger_ = nullptr;
size_t ILogger::depth_ = 0;

ILogger::~ILogger() = default;

size_t ILogger::GetDepth() {
  return depth_;
}
