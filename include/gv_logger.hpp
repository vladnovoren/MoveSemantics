#ifndef GV_LOGGER_HPP
#define GV_LOGGER_HPP

#include <cstdlib>
#include <map>
#include "ilogger.hpp"
#include "log_int.hpp"
#include <vector>


struct Edge {
  size_t src_ = 0;
  size_t dst_ = 0;

  std::string style_ = "solid";
};


class GVLogger: public ILogger {
 public:
  GVLogger();
  ~GVLogger();

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

  void LogElem(const LogInt& elem) override;

 protected:
  size_t FetchAddId();

  void LogNodesLink(const Edge& edge);

  size_t LogOptorNode(const std::string& name);
  size_t LogCtorNode(const std::string& name, const std::string& color);

  void LogShift() override;
  void LogElemValue(const LogInt& elem) override;
  void LogElemName(const LogInt& elem);
  void LogElemAddress(const LogInt& elem);

  void LogEdges();

  size_t NewOccurrence(const LogInt& elem);
  size_t LastElemId(const LogInt& elem);

  const char* GetElemColor(const LogInt& elem);

  FILE* log_file_ = nullptr;
  size_t funcs_cnt_ = 0;

  std::map<size_t, size_t> node_match_;
  std::map<size_t, bool> logged_;
  size_t last_node_id_ = 0;

  std::vector<Edge> edges_;
};

#endif /* gv_logger.hpp */
