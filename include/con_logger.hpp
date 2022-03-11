#ifndef CON_LOGGER_HPP
#define CON_LOGGER_HPP

#include <cstdio>
#include <cassert>
#include <string>
#include "itext_logger.hpp"

class LogInt;

class ConLogger: public ITextLogger {
 public:
  ConLogger() = default;
  ~ConLogger() override = default;

  void LogDefaultCtor(const LogInt& elem) override;
  void LogValueCtor(const LogInt& elem) override;
  void LogCopyCtor(const LogInt& dst, const LogInt& src) override;
  void LogMoveCtor(const LogInt& dst, const LogInt& src) override;
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

  void SetDefaultText() override;
  void SetRedBlinkText() override;
  void SetGreenText() override;
  void SetYellowBoldText() override;
};

#endif /* con_logger.hpp */
