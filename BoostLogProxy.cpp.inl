
namespace {
logging::record &as_record(char *ptr) { return reinterpret_cast<logging::record &>(*ptr); }
} // namespace

namespace cdhlog {

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

cdhlog::BoostLogProxy::BoostLogProxy(const char *file, const char *func, size_t line, Severity severity) : _file(file), _func(func), _line(line) {
  logging::attribute_set as;
  as[tag::Severity::get_name()] = attrs::constant<tag::Severity::value_type>(severity);

  as_record(_record) = logging::core::get()->open_record(as);
}

bool cdhlog::BoostLogProxy::FilterCheck() { return !!as_record(_record); }

void cdhlog::BoostLogProxy::Emit() {
  as_record(_record).attribute_values().insert(tag::File::get_name(), attrs::make_attribute_value((tag::File::value_type)_file));
  as_record(_record).attribute_values().insert(tag::Func::get_name(), attrs::make_attribute_value((tag::Func::value_type)_func));
  as_record(_record).attribute_values().insert(tag::Line::get_name(), attrs::make_attribute_value((tag::Line::value_type)_line));

  logging::record_ostream os(as_record(_record));
  os << _stream.str();
  os.flush();

  logging::core::get()->push_record(std::move(as_record(_record)));
}

} // namespace cdhlog
