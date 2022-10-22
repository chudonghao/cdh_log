#pragma once

#include <boost/log/attributes/attribute_value_impl.hpp>
#include <boost/log/core/core.hpp>
#include <boost/log/core/record.hpp>
#include <boost/log/sources/record_ostream.hpp>

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
  explicit BoostLogProxy(cdhlog::Severity s) {
    boost::log::attribute_value_set vs;
    vs.insert("Severity", boost::log::attributes::make_attribute_value(s));
    _record = boost::log::core::get()->open_record(vs);
  }

  boost::log::record &Record(const char *file, const char *func, size_t line) {
    auto &vs = _record.attribute_values();
    vs.insert("File", boost::log::attributes::make_attribute_value(std::string(file)));
    vs.insert("Func", boost::log::attributes::make_attribute_value(std::string(func)));
    vs.insert("Line", boost::log::attributes::make_attribute_value(line));
    return _record;
  }

  bool FilterCheck() { return !!_record; }

  void Emit() { boost::log::core::get()->push_record(std::move(_record)); }

 private:
  const char *_file{};
  const char *_func{};
  size_t _line{};

  boost::log::record _record;
};

}  // namespace cdhlog

#define CLOG_(L) \
  for (cdhlog::BoostLogProxy proxy{L}; proxy.FilterCheck(); proxy.Emit()) boost::log::record_ostream(proxy.Record(__FILE__, __FUNCTION__, __LINE__))

#define CLOG_SEVERITY_(LEVEL) CLOG_(cdhlog::SEVERITY_##LEVEL)

#define CLOG_TRACE CLOG_SEVERITY_(TRACE)
#define CLOG_DEBUG CLOG_SEVERITY_(DEBUG)
#define CLOG_INFO CLOG_SEVERITY_(INFO)
#define CLOG_WARN CLOG_SEVERITY_(WARN)
#define CLOG_ERROR CLOG_SEVERITY_(ERROR)
#define CLOG_FATAL CLOG_SEVERITY_(FATAL)
