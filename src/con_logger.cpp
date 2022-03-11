#include "con_logger.hpp"
#include "log_int.hpp"

void ConLogger::LogDefaultCtor(const LogInt& elem) {
  LogShift();
  if (elem.IsImp()) {
    SetRedBlinkText();
  }
  printf("(New) ");
  printf("%s", elem.GetName().c_str());
  SetDefaultText();
  printf(" {");
  LogElemValue(elem);
  printf("} ");
  LogElem(elem);
  printf("\n");
}

void ConLogger::LogValueCtor(const LogInt& elem) {
  LogShift();
  if (elem.IsImp()) {
    SetRedBlinkText();
  }
  printf("(New) ");
  printf("%s", elem.GetName().c_str());
  SetDefaultText();
  printf("(%d) ", elem.value_);
  printf("{");
  LogElemValue(elem);
  printf("} ");
  LogElem(elem);
  printf("\n");
}

void ConLogger::LogCopyCtor(const LogInt& dst, const LogInt& src) {
  LogShift();
  if (dst.IsImp()) {
    SetRedBlinkText();
  }
  printf("(New) ");
  printf("%s", dst.GetName().c_str());
  SetDefaultText();
  printf("(%s) ", src.GetName().c_str());
  printf("{");
  LogElemValue(dst);
  printf("} ");
  LogElem(dst);
  printf(" ");
  LogElem(src);
  printf("\n");
}

void ConLogger::LogMoveCtor(const LogInt&, const LogInt&) {}

void ConLogger::LogDtor(const LogInt&) {}

void ConLogger::LogAssOptor(const LogInt& dst, const LogInt& src) {
  LogShift();
  printf("%s = %s ", dst.GetName().c_str(), src.GetName().c_str());
  printf("{");
  LogElemValue(dst);
  printf("} ");
  LogElem(dst);
  printf(" ");
  LogElem(src);
  printf("\n");
}

void ConLogger::LogMoveAssOptor(const LogInt&, const LogInt&) {}

void ConLogger::LogUnaryOptor(const LogInt& elem, const LogInt& parent, const std::string& op) {
  LogShift();
  if (elem.IsImp()) {
    SetRedBlinkText();
  }
  printf("(New) ");
  printf("%s", elem.GetName().c_str());
  SetDefaultText();
  printf(" = %s%s ", op.c_str(), parent.GetName().c_str());
  printf("{");
  LogElemValue(elem);
  printf("} ");
  LogElem(elem);
  printf(" ");
  LogElem(parent);
  printf("\n");
}

void ConLogger::LogBinaryOptor(const LogInt& elem, const LogInt& parent1, const LogInt& parent2, const std::string& op) {
  LogShift();
  if (elem.IsImp()) {
    SetRedBlinkText();
  }
  printf("(New) ");
  printf("%s", elem.GetName().c_str());
  SetDefaultText();
  printf(" = %s %s %s ", parent1.GetName().c_str(), op.c_str(), parent2.GetName().c_str());
  printf("{");
  LogElemValue(elem);
  printf("} ");
  LogElem(elem);
  printf(" ");
  LogElem(parent1);
  printf(" ");
  LogElem(parent2);
  printf("\n");
}

void ConLogger::LogBinaryAssOptor(const LogInt& elem, const LogInt& other, const std::string& op) {
  LogShift();
  printf("%s %s %s ", elem.GetName().c_str(), op.c_str(), other.GetName().c_str());
  printf("{");
  LogElemValue(elem);
  printf("} ");
  LogElem(other);
  printf("\n");
}

void ConLogger::LogFuncEntry(const std::string& func) {
  LogShift();
  ++depth_;
  printf("%s {\n", func.c_str());
}

void ConLogger::LogFuncEnd() {
  --depth_;
  LogShift();
  printf("}\n");
}

void ConLogger::LogShift() {
  for (size_t i = 0; i < depth_; ++i) {
    printf("  ");
  }
}

void ConLogger::LogElem(const LogInt& elem) {
  printf("%s[%p]", elem.GetName().c_str(), static_cast<const void*>(&elem));
}

void ConLogger::LogElemValue(const LogInt& elem) {
  printf("%s.value_ = %d", elem.GetName().c_str(), elem.value_);
}

void ConLogger::SetDefaultText() {
  printf("\x1b[0m");
}

void ConLogger::SetRedBlinkText() {
  printf("\x1b[5;33m");
}

void ConLogger::SetGreenText() {
  printf("\x1b[32m");
}

void ConLogger::SetYellowBoldText() {
  printf("\x1b[1;33m");
}
