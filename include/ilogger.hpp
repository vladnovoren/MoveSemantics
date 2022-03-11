#ifndef ILOGGER_HPP
#define ILOGGER_HPP

#include <cstdio>
#include <cassert>
#include <string>

class LogInt;

class ILogger {
 public:
  ILogger() = default;
  virtual ~ILogger() = 0;

  static ILogger* curr_logger_;

  static size_t GetDepth();

  virtual void LogDefaultCtor(const LogInt& elem) = 0;
  virtual void LogValueCtor(const LogInt& elem) = 0;
  virtual void LogCopyCtor(const LogInt& dst, const LogInt& src) = 0;
  virtual void LogMoveCtor(const LogInt& dst, const LogInt& src) = 0;
  virtual void LogDtor(const LogInt& elem) = 0;

  virtual void LogAssOptor(const LogInt& dst, const LogInt& src) = 0;
  virtual void LogMoveAssOptor(const LogInt& dst, const LogInt& src) = 0;

  virtual void LogUnaryOptor(const LogInt& elem, const LogInt& parent, const std::string& op) = 0;
  virtual void LogBinaryOptor(const LogInt& elem, const LogInt& parent1, const LogInt& parent2, const std::string& op) = 0;
  virtual void LogBinaryAssOptor(const LogInt& elem, const LogInt& other, const std::string& op) = 0;

  virtual void LogFuncEntry(const std::string& func) = 0;
  virtual void LogFuncEnd() = 0;

 protected:
  virtual void LogShift() = 0;
  virtual void LogElem(const LogInt& elem) = 0;
  virtual void LogElemValue(const LogInt& elem) = 0;

  static size_t depth_;
};

void SetDefault();
void SetRedBlink();
void SetGreen();
void SetYellowBold();

#endif /* logger.hpp */
