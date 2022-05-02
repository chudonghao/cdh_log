//
// Created by chudonghao on 2022/5/2.
//

#include "ConsoleBackend.h"

#include "cdhlog.h"

BOOST_LOG_ATTRIBUTE_KEYWORD(Severity, "Severity", cdhlog::Severity)

namespace cdhlog {

void cdhlog::ConsoleBackend::consume(const logging::record_view &rec, const ConsoleBackendBase::string_type &message) {
  auto s = rec[::Severity];
  if (s.empty()) {
    std::cout << message.c_str() << std::endl;
    return;
  }

#ifdef __linux__
  auto CYAN = "\033[36m";
  auto LIGHT_GRAY = "\033[37m";
  auto DEFAULT = "\033[0m";
  auto ORANGE = "\033[33m";
  auto RED = "\033[31m";
  auto RED_BACKGROUND = "\033[41m";

  switch ((Severity)s.get()) {
  case SEVERITY_TRACE:
    std::cout << CYAN;
    break;
  case SEVERITY_DEBUG:
    std::cout << LIGHT_GRAY;
    break;
  case SEVERITY_INFO:
    std::cout << DEFAULT;
    break;
  case SEVERITY_WARN:
    std::cout << ORANGE;
    break;
  case SEVERITY_ERROR:
    std::cout << RED;
    break;
  case SEVERITY_FATAL:
    std::cout << RED_BACKGROUND;
    break;
  }
  std::cout << message.c_str() << DEFAULT << std::endl;
#elifdef WIN32
  // TODO
  std::cout << message.c_str() << std::endl;
#else
  std::cout << message.c_str() << std::endl;
#endif
}

void cdhlog::ConsoleBackend::flush() {}

} // namespace cdhlog
