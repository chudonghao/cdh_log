//
// Created by chudonghao on 2022/5/2.
//

#ifndef INC_CHUDONGHAO_2022_5_2_0207F33F54884B458BEB18A13F4A273C_
#define INC_CHUDONGHAO_2022_5_2_0207F33F54884B458BEB18A13F4A273C_

#include <sstream>

namespace cdhlog {

enum Severity {
  SEVERITY_TRACE,
  SEVERITY_DEBUG,
  SEVERITY_INFO,
  SEVERITY_WARN,
  SEVERITY_ERROR,
  SEVERITY_FATAL,
};

class BoostLogProxy {
public:
  BoostLogProxy(const char *file, const char *func, size_t line, Severity severity);

  std::stringstream &Stream() { return _stream; }

  bool FilterCheck();

  void Emit();

private:
  const char *_file;
  const char *_func;
  size_t _line;

  std::stringstream _stream;
  char _record[8]{};
};

enum {
  ENABLE_CONSOLE_SINK = 1u,
  // ENABLE_FILE_SINK = 1u << 1u,
};

void Init(unsigned enable = ENABLE_CONSOLE_SINK);

struct InitOption {
  bool enable_console_sink{true};
  Severity console_severity{SEVERITY_TRACE};

  // bool enable_file_sink{true};
  // Severity file_severity{SEVERITY_TRACE};
};

void Init(const InitOption &option);

} // namespace cdhlog

#define CLOG_(LEVEL)                                                                                                                                 \
  for (cdhlog::BoostLogProxy record{__FILE__, __FUNCTION__, __LINE__, cdhlog::SEVERITY_##LEVEL}; record.FilterCheck(); record.Emit())                \
  record.Stream()

#define CLOG_TRACE CLOG_(TRACE)
#define CLOG_DEBUG CLOG_(DEBUG)
#define CLOG_INFO CLOG_(INFO)
#define CLOG_WARN CLOG_(WARN)
#define CLOG_ERROR CLOG_(ERROR)
#define CLOG_FATAL CLOG_(FATAL)

#endif // INC_CHUDONGHAO_2022_5_2_0207F33F54884B458BEB18A13F4A273C_
