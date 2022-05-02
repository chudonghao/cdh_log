//
// Created by chudonghao on 2022/5/2.
//

#ifndef INC_CHUDONGHAO_2022_5_2_6FD41F42859B42EFA705A2D8BFA37A5E_
#define INC_CHUDONGHAO_2022_5_2_6FD41F42859B42EFA705A2D8BFA37A5E_

#include <boost/log/attributes/constant.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/keywords/start_thread.hpp>
#include <boost/log/sinks/basic_sink_backend.hpp>
#include <boost/log/sinks/frontend_requirements.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/sources/basic_logger.hpp>
#include <boost/log/sources/exception_handler_feature.hpp>
#include <boost/log/sources/features.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/utility/exception_handler.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/strictest_lock.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/mpl/quote.hpp>
#include <boost/parameter/keyword.hpp>
#include <boost/scope_exit.hpp>
#include <boost/smart_ptr/make_shared_object.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/thread/locks.hpp>
#include <boost/thread/shared_mutex.hpp>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace sinks = boost::log::sinks;
namespace attrs = boost::log::attributes;
namespace keywords = boost::log::keywords;

#endif // INC_CHUDONGHAO_2022_5_2_6FD41F42859B42EFA705A2D8BFA37A5E_
