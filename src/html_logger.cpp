#include "html_logger.hpp"

HTMLLogger::HTMLLogger() {
  log_file_ = fopen("log.html", "w");
  fprintf(log_file_, "<pre>\n");
}

HTMLLogger::~HTMLLogger() {
  fprintf(log_file_, "</pre>");
  fclose(log_file_);
}

void HTMLLogger::LogDefaultCtor(const LogInt& elem) {
  LogShift();
  if (elem.IsImp()) {
    SetRedBlinkText();
  }
  fprintf(log_file_, "(New) ");
  LogName(elem);
  if (elem.IsImp()) {
    SetDefaultText();
  }
  fprintf(log_file_, " {");
  LogElemValue(elem);
  fprintf(log_file_, "} ");
  LogElem(elem);
  fprintf(log_file_, "\n");
}

void HTMLLogger::LogValueCtor(const LogInt& elem) {
  LogShift();
  if (elem.IsImp()) {
    SetRedBlinkText();
  }
  fprintf(log_file_, "(New) ");
  LogName(elem);
  if (elem.IsImp()) {
    SetDefaultText();
  }
  fprintf(log_file_, "(%d) ", elem.value_);
  fprintf(log_file_, "{");
  LogElemValue(elem);
  fprintf(log_file_, "} ");
  LogElem(elem);
  fprintf(log_file_, "\n");
}

void HTMLLogger::LogCopyCtor(const LogInt& dst, const LogInt& src) {
  LogShift();
  if (dst.IsImp()) {
    SetRedBlinkText();
  }
  fprintf(log_file_, "(New) ");
  LogName(dst);
  if (dst.IsImp()) {
    SetDefaultText();
  }
  fprintf(log_file_, "(");
  LogName(src);
  fprintf(log_file_, ") ");
  fprintf(log_file_, "{");
  LogElemValue(dst);
  fprintf(log_file_, "} ");
  LogElem(dst);
  fprintf(log_file_, " ");
  LogElem(src);
  fprintf(log_file_, "\n");
}

size_t HTMLLogger::LogMoveCtorPrefix(const LogInt&) {return 0;}
void HTMLLogger::LogMoveCtorSuffix(const LogInt&, const LogInt&, const size_t) {}

void HTMLLogger::LogDtor(const LogInt&) {}

void HTMLLogger::LogAssOptor(const LogInt& dst, const LogInt& src) {
  LogShift();
  LogName(dst);
  fprintf(log_file_, " = ");
  LogName(src);
  fprintf(log_file_, " {");
  LogElemValue(dst);
  fprintf(log_file_, "} ");
  LogElem(dst);
  fprintf(log_file_, " ");
  LogElem(src);
  fprintf(log_file_, "\n");
}

void HTMLLogger::LogMoveAssOptor(const LogInt&, const LogInt&) {}


void HTMLLogger::LogUnaryOptor(const LogInt& elem, const LogInt& parent, const std::string& op) {
  LogShift();
  if (elem.IsImp()) {
    SetRedBlinkText();
  }
  fprintf(log_file_, "(New) ");
  LogName(elem);
  if (elem.IsImp()) {
    SetDefaultText();
  }
  fprintf(log_file_, " = %s ", op.c_str());
  LogName(parent);
  fprintf(log_file_, " {");
  LogElemValue(elem);
  fprintf(log_file_, "} ");
  LogElem(elem);
  fprintf(log_file_, " ");
  LogElem(parent);
  fprintf(log_file_, "\n");
}

void HTMLLogger::LogBinaryOptor(const LogInt& elem, const LogInt& parent1, const LogInt& parent2, const std::string& op) {
  LogShift();
  if (elem.IsImp()) {
    SetRedBlinkText();
  }
  fprintf(log_file_, "(New) ");
  LogName(elem);
  if (elem.IsImp()) {
    SetDefaultText();
  }
  fprintf(log_file_, " = ");
  LogName(parent1);
  fprintf(log_file_, " %s ", op.c_str());
  LogName(parent2);
  fprintf(log_file_, " ");
  fprintf(log_file_, "{");
  LogElemValue(elem);
  fprintf(log_file_, "} ");
  LogElem(elem);
  fprintf(log_file_, " ");
  LogElem(parent1);
  fprintf(log_file_, " ");
  LogElem(parent2);
  fprintf(log_file_, "\n");
}

void HTMLLogger::LogBinaryAssOptor(const LogInt& elem, const LogInt& other, const std::string& op) {
  LogShift();
  fprintf(log_file_, "%s %s %s ", elem.GetName().c_str(), op.c_str(), other.GetName().c_str());
  fprintf(log_file_, "{");
  LogElemValue(elem);
  fprintf(log_file_, "} ");
  LogElem(other);
  fprintf(log_file_, "\n");
}

void HTMLLogger::LogFuncEntry(const std::string& func) {
  LogShift();
  ++depth_;
  fprintf(log_file_, "%s {\n", func.c_str());
}

void HTMLLogger::LogFuncEnd() {
  --depth_;
  LogShift();
  fprintf(log_file_, "}\n");
}

void HTMLLogger::LogShift() {
  for (size_t i = 0; i < depth_; ++i) {
    fprintf(log_file_, "  ");
  }
}

void HTMLLogger::LogElem(const LogInt& elem) {
  fprintf(log_file_, "%s[%p]", elem.GetName().c_str(), static_cast<const void*>(&elem));
}

void HTMLLogger::LogElemValue(const LogInt& elem) {
  fprintf(log_file_, "%s.value_ = %d", elem.GetName().c_str(), elem.value_);
}

void HTMLLogger::LogName(const LogInt& elem) {
  fprintf(log_file_, "<h title=\"%s\">%s</h>", elem.GetHistory().c_str(), elem.GetName().c_str());
}

void HTMLLogger::SetDefaultText() {
  fprintf(log_file_, "</font>");
  if (is_bold_) {
    fprintf(log_file_, "</b>");
    is_bold_ = false;
  }
  if (is_blink_) {
    fprintf(log_file_, "</span>");
    is_blink_ = false;
  }
}

void HTMLLogger::SetGreenText() {
  fprintf(log_file_, "<font color=#00FF00>");
}

void HTMLLogger::SetRedBlinkText() {
  fprintf(log_file_, "<span class=\"blinking\">");
  is_blink_ = true;
  fprintf(log_file_, "<font color=#FF0000>");
}

void HTMLLogger::SetYellowBoldText() {
  fprintf(log_file_, "<b>");
  fprintf(log_file_, "<font color=#FFFF00>");
}
