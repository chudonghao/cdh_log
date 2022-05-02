//
// Created by chudonghao on 2022/5/2.
//

#ifndef INC_CHUDONGHAO_2022_5_2_9DCFDAB943A9465888139B72BCECDE8A_
#define INC_CHUDONGHAO_2022_5_2_9DCFDAB943A9465888139B72BCECDE8A_

#include "boost_log.h"

namespace cdhlog {

using ConsoleBackendBase = sinks::basic_formatted_sink_backend< //
    char,                                                       //
    sinks::combine_requirements<                                //
        sinks::synchronized_feeding,                            //
        sinks::formatted_records,                               //
        sinks::flushing                                         //
        >::type>;

class ConsoleBackend : public ConsoleBackendBase {
public:
  ConsoleBackend() = default;
  void consume(logging::record_view const &rec, const ConsoleBackendBase::string_type &message);
  void flush();
};

} // namespace cdhlog

#endif // INC_CHUDONGHAO_2022_5_2_9DCFDAB943A9465888139B72BCECDE8A_
