#ifndef HTML_LOGGER_HPP
#define HTML_LOGGER_HPP

#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <string>
#include "ilogger.hpp"
#include "itext_logger.hpp"
#include "log_int.hpp"

class LogInt;

class HTMLLogger: public ITextLogger {
 public:
  HTMLLogger();
  ~HTMLLogger() override;

  void LogDefaultCtor(const LogInt& elem) override;
  void LogValueCtor(const LogInt& elem) override;
  void LogCopyCtor(const LogInt& dst, const LogInt& src) override;
  size_t LogMoveCtorPrefix(const LogInt& src) override;
  void LogMoveCtorSuffix(const LogInt& dst, const LogInt& src, const size_t ctor_node) override;
  void LogDtor(const LogInt& elem) override;

  void LogAssOptor(const LogInt& dst, const LogInt& src) override;
  void LogMoveAssOptor(const LogInt& dst, const LogInt& src) override;

  void LogUnaryOptor(const LogInt& elem, const LogInt& parent, const std::string& op) override;
  void LogBinaryOptor(const LogInt& elem, const LogInt& parent1, const LogInt& parent2, const std::string& op) override;
  void LogBinaryAssOptor(const LogInt& elem, const LogInt& other, const std::string& op) override;

  void LogFuncEntry(const std::string& func) override;
  void LogFuncEnd() override;

 private:
  void LogShift() override;
  void LogElem(const LogInt& elem) override;
  void LogElemValue(const LogInt& elem) override;

  void LogName(const LogInt& elem);

  void SetDefaultText() override;
  void SetRedBlinkText() override;
  void SetGreenText() override;
  void SetYellowBoldText() override;

  FILE* log_file_ = nullptr;

  bool is_blink_ = false;
  bool is_bold_  = false;
};

#endif /* html_logger.hpp */
