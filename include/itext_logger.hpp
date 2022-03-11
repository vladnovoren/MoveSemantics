#ifndef ITEXT_LOGGER_HPP
#define ITEXT_LOGGER_HPP

#include "ilogger.hpp"

class ITextLogger: public ILogger {
 protected:
  virtual void LogShift() = 0;

  virtual void SetDefaultText() = 0;
  virtual void SetRedBlinkText() = 0;
  virtual void SetGreenText() = 0;
  virtual void SetYellowBoldText() = 0;
};

#endif /* itext_logger.hpp */
