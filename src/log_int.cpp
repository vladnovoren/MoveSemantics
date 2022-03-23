#include "log_int.hpp"

size_t LogInt::last_num_ = 0;

LogInt::LogInt(const std::string& name) {
  FUNC_LOG;
  SetName(name);
  history_ += name_ + "(" + std::to_string(value_) + ")";
  ILogger::curr_logger_->LogDefaultCtor(*this);
}

LogInt::LogInt(const int value, const std::string& name): value_(value) {
  FUNC_LOG;
  SetName(name);
  history_ += name_ + "(" + std::to_string(value) + ")";
  ILogger::curr_logger_->LogValueCtor(*this);
}

LogInt::LogInt(const LogInt& other, const std::string& name): value_(other.value_) {
  FUNC_LOG;
  SetName(name);
  history_ += name_ + "(" + other.history_ + ")";
  ILogger::curr_logger_->LogCopyCtor(*this, other);
}

LogInt::LogInt(LogInt&& other, const std::string& name) {
  FUNC_LOG;
  size_t ctor_node_id = ILogger::curr_logger_->LogMoveCtorPrefix(other);
  SetName(name);
  std::swap(value_, other.value_);
  history_ += name_ + "(" + other.history_ + ")";
  ILogger::curr_logger_->LogMoveCtorSuffix(*this, other, ctor_node_id);
}

LogInt::~LogInt() {
  FUNC_LOG;
  ILogger::curr_logger_->LogDtor(*this);
}

const std::string& LogInt::GetName() const {
  return name_;
}

const std::string& LogInt::GetHistory() const {
  return history_;
}

size_t LogInt::GetNum() const {
  return num_;
}

bool LogInt::IsImp() const {
  return is_imp_;
}

const char* LogInt::GetTypeStr() const {
  return is_imp_ ? IMP : EXP;
}

LogInt& LogInt::operator=(const LogInt& other) {
  FUNC_LOG;
  value_ = other.value_;
  history_ = other.history_;
  ILogger::curr_logger_->LogAssOptor(*this, other);
  return *this;
}

LogInt& LogInt::operator=(LogInt&& other) {
  FUNC_LOG;
  size_t optor_node_id = ILogger::curr_logger_->LogMoveAssOptorPrefix(other);
  std::swap(value_, other.value_);
  history_ = other.history_;
  ILogger::curr_logger_->LogMoveAssOptorSuffix(*this, other, optor_node_id);
  return *this;
}

#define UNARY_OPTOR(op) \
LogInt LogInt::operator op() const { \
  return LogInt(*this, op value_, #op, #op + history_); \
}

#define BINARY_OPTOR(op) \
LogInt LogInt::operator op(const LogInt& other) const { \
  FUNC_LOG; \
  return LogInt(*this, other, this->value_ op other.value_, #op, "(" + history_ + ") " + #op + " (" + other.history_ + ")"); \
}

#define BINARY_ASS_OPTOR(op) \
LogInt& LogInt::operator op(const LogInt& other) { \
  value_ op other.value_; \
  history_ = "(" + history_ + ") " + #op + " (" + other.history_ + ")"; \
  ILogger::curr_logger_->LogBinaryAssOptor(*this, other, #op); \
  return *this; \
}

#define BINARY_COMP_OPTOR(op) \
bool LogInt::operator op(const LogInt& other) const { \
  FUNC_LOG; \
  return value_ op other.value_; \
}

#include "optors.hpp"

#undef BINARY_OPTOR
#undef UNARY_OPTOR
#undef BINARY_ASS_OPTOR
#undef BINARY_COMP_OPTOR

LogInt::LogInt(const LogInt& parent, const int value, const std::string& op, const std::string& history): value_(value), history_(history) {
  SetName();
  ILogger::curr_logger_->LogUnaryOptor(*this, parent, op);
}

LogInt::LogInt(const LogInt& parent1, const LogInt& parent2, const int value, const std::string& op, const std::string& history): value_(value), history_(history) {
  SetName();
  ILogger::curr_logger_->LogBinaryOptor(*this, parent1, parent2, op);
}

void LogInt::SetName(const std::string& name) {
  num_ = last_num_++;
  if (name != "") {
    is_imp_ = false;
    name_ = name + "#" + std::to_string(num_);
  } else {
    is_imp_ = true;
    name_ = "IMP#" + std::to_string(num_);
  }
}
