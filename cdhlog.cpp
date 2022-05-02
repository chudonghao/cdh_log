//
// Created by chudonghao on 2022/5/2.
//

#include "cdhlog.h"

#include "ConsoleBackend.h"

#include "boost_log.h"

BOOST_LOG_ATTRIBUTE_KEYWORD(Severity, "Severity", cdhlog::Severity)
BOOST_LOG_ATTRIBUTE_KEYWORD(File, "File", const char *)
BOOST_LOG_ATTRIBUTE_KEYWORD(Func, "Func", const char *)
BOOST_LOG_ATTRIBUTE_KEYWORD(Line, "Line", size_t)

#include "BoostLogProxy.cpp.inl"

namespace {

struct EH {
  typedef void result_type;
  void operator()(std::exception const &e) const { std::cerr << "logger got std::exception: " << e.what() << std::endl; }
  void operator()() const { std::cerr << "logger got exception(unknown type) " << std::endl; }
};

void Format(logging::record_view const &rec, logging::formatting_ostream &strm) {
  strm << expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S.%f")(rec);
  strm << "|" << rec[File] << ":" << rec[Line];
  strm << "|" << logging::extract<logging::thread_id>("ThreadID", rec);
  strm << "|" << rec[Func];
  strm << "|" << rec[Severity];
  strm << "|" << rec[expr::message];
}

} // namespace

namespace cdhlog {

void Init(unsigned int enable) {
  InitOption option;
  option.enable_console_sink = true;
  option.console_severity = SEVERITY_TRACE;
  Init(option);
}

void Init(const InitOption &option) {
  logging::core::get()->remove_all_sinks();
  logging::core::get()->set_logging_enabled(false);
  if (!option.enable_console_sink /*&& !option.enable_file_sink*/) {
    return;
  }

  // exception handler
  logging::core::get()->set_exception_handler(logging::make_exception_handler<std::exception>(EH(), std::nothrow));

  // common attributes
  logging::add_common_attributes();

  // console sink
  if (option.enable_console_sink) {
    typedef sinks::synchronous_sink<ConsoleBackend> sink_t;
    boost::shared_ptr<sink_t> sink(new sink_t());

    sink->set_filter(expr::attr<Severity>("Severity") >= option.console_severity);
    sink->set_formatter(&Format);

    logging::core::get()->add_sink(sink);
  }

  // enable log
  logging::core::get()->set_logging_enabled(true);
}

} // namespace cdhlog
