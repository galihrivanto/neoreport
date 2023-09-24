#pragma once

#include <boost/log/attributes.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/expressions/predicates/channel_severity_filter.hpp>
#include <boost/log/trivial.hpp>

#define DEFAULT_LOG_FORMAT "[%TimeStamp%][%Severity%] %Message%"

#define LOG(severity) BOOST_LOG_TRIVIAL(severity)

namespace attrs = boost::log::attributes;

BOOST_LOG_ATTRIBUTE_KEYWORD(a_timestamp, "TimeStamp", attrs::local_clock::value_type);
BOOST_LOG_ATTRIBUTE_KEYWORD(a_severity, "Severity", boost::log::trivial::severity_level);
BOOST_LOG_ATTRIBUTE_KEYWORD(a_message, "Message", std::string);

namespace neoreport::core
{

void init_log(int log_level, const std::string &log_file);

inline void init_log(int log_level)
{
    init_log(log_level, "");
}
} // namespace core