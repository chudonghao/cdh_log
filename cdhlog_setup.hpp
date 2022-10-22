#pragma once

#include "cdhlog.hpp"

#include <boost/log/core.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/utility/exception_handler.hpp>
#include <boost/log/utility/setup.hpp>

namespace cdhlog {

BOOST_LOG_ATTRIBUTE_KEYWORD(SeverityKeyword, "Severity", cdhlog::Severity)

namespace logging = boost::log;
// namespace src = boost::log::sources;
// namespace expr = boost::log::expressions;
namespace sinks = boost::log::sinks;
// namespace attrs = boost::log::attributes;
// namespace keywords = boost::log::keywords;

struct ExceptionHandler {
  typedef void result_type;
  void operator()(std::exception const &e) const { std::cerr << "cdhlog got exception: " << e.what() << std::endl; }
  void operator()() const { std::cerr << "cdhlog got exception(unknown type) " << std::endl; }
};

using ConsoleBackendBase = sinks::basic_formatted_sink_backend<  //
    char,                                                        //
    sinks::combine_requirements<                                 //
        sinks::synchronized_feeding,                             //
        sinks::formatted_records,                                //
        sinks::flushing                                          //
        >::type>;

class ConsoleBackend : public ConsoleBackendBase {
 public:
  ConsoleBackend() = default;
  void consume(logging::record_view const &rec, const ConsoleBackendBase::string_type &message) {
    auto s = rec[SeverityKeyword];
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
#endif
#ifdef WIN32
      // TODO
#endif

    std::cout << message.c_str();

#ifdef __linux__
    std::cout << DEFAULT;
#endif

    std::cout << std::endl;
  }

  void flush() {}
};

class ConsoleBackendFactory : public logging::sink_factory<char> {
 public:
  boost::shared_ptr<sinks::sink> create_sink(settings_section const &settings) {
    boost::shared_ptr<ConsoleBackend> backend = boost::make_shared<ConsoleBackend>();
    boost::shared_ptr<sinks::synchronous_sink<ConsoleBackend> > sink = boost::make_shared<sinks::synchronous_sink<ConsoleBackend> >(backend);

    if (boost::optional<std::string> param = settings["Filter"]) {
      sink->set_filter(logging::parse_filter(param.get()));
    }
    if (boost::optional<std::string> param = settings["Format"]) {
      sink->set_formatter(logging::parse_formatter(param.get()));
    }

    return sink;
  }
};

std::ostream &operator<<(std::ostream &strm, Severity level) {
  static const char *strings[] = {
      "trace", "debug", "info", "warn", "error", "fatal",
  };

  if (static_cast<std::size_t>(level) < sizeof(strings) / sizeof(*strings))
    strm << strings[level];
  else
    strm << static_cast<int>(level);

  return strm;
}

std::istream &operator>>(std::istream &strm, Severity &level) {
  std::string s;
  strm >> s;
  if (s == "trace") {
    level = SEVERITY_TRACE;
  } else if (s == "debug") {
    level = SEVERITY_DEBUG;
  } else if (s == "info") {
    level = SEVERITY_INFO;
  } else if (s == "warn") {
    level = SEVERITY_WARN;
  } else if (s == "error") {
    level = SEVERITY_ERROR;
  } else if (s == "fatal") {
    level = SEVERITY_FATAL;
  } else {
    strm.setstate(std::ios_base::failbit);
  }
  return strm;
}

static inline void Setup(logging::settings settings) {
  logging::core::get()->set_exception_handler(logging::make_exception_handler<std::exception>(ExceptionHandler(), std::nothrow));

  logging::register_simple_filter_factory<Severity>("Severity");
  logging::register_simple_formatter_factory<Severity, char>("Severity");
  logging::register_sink_factory("ColoredConsole", boost::make_shared<ConsoleBackendFactory>());

  logging::add_common_attributes();

  logging::init_from_settings(settings);
}

static inline void Setup() {
  logging::settings settings;
  settings["Sinks.Console.Destination"] = "ColoredConsole";
  settings["Sinks.Console.Format"] = "%TimeStamp% %File%:%Line% <%Severity%>[%ThreadID%][%Func%]: %Message%";
  settings["Sinks.Console.AutoFlush"] = true;

  Setup(std::move(settings));
}

}  // namespace cdhlog
