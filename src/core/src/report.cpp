#include <boost/uuid/uuid.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <string>
#include "core/report.h"

namespace neoreport::report
{

    std::string random_id()
    {
        boost::uuids::uuid id = boost::uuids::random_generator()();
        return boost::uuids::to_string(id);       
    }
}