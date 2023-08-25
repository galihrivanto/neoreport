#include "core/log.h"

#include <boost/log/core/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/expressions/formatters/date_time.hpp>
#include <boost/log/keywords/file_name.hpp>
#include <boost/log/keywords/format.hpp>
#include <boost/log/keywords/rotation_size.hpp>
#include <boost/log/keywords/time_based_rotation.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>

namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;
namespace logging = boost::log;

namespace neoreport::core
{
static void colored_formatter(logging::record_view const &rec, logging::formatting_ostream &strm);

void init_log(int log_level, const std::string &log_file)
{
    if (!log_file.empty())
        logging::add_file_log(keywords::file_name = log_file, keywords::rotation_size = 10 * 1024 * 1024,
                              keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
                              keywords::format = DEFAULT_LOG_FORMAT);

    auto console_sink = logging::add_console_log(std::cout, boost::log::keywords::format = DEFAULT_LOG_FORMAT);
    console_sink->set_formatter(&colored_formatter);

    logging::add_common_attributes();
    logging::core::get()->set_filter(logging::trivial::severity >= log_level);
}

void colored_formatter(const boost::log::record_view &rec, boost::log::formatting_ostream &strm)
{
    auto severity = rec[logging::trivial::severity];
    if (severity)
    {
        switch (severity.get())
        {
        case logging::trivial::severity_level::debug:
            strm << "\033[96m";
            break;
        case logging::trivial::severity_level::warning:
            strm << "\033[33m";
            break;
        case logging::trivial::severity_level::error:
        case logging::trivial::severity_level::fatal:
            strm << "\033[31m";
            break;
        default:
            strm << "\033[37m";
            break;
        }
    }

    // Format the message here...
    strm << "[" << rec[a_timestamp] << "]"
         << "[" << rec[a_severity] << "] " << rec[logging::expressions::smessage];

    if (severity)
    {
        strm << "\033[0m";
    }
}
} 