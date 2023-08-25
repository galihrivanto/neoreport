#include "core/report.h"
#include <boost/program_options/variables_map.hpp>
#include <iostream>
#include <memory>
#include <sstream>
#include <utility>
#include <zlib.h>
#include <stdio.h>
#include <cstring>
#include <boost/program_options.hpp>
#include <core/log.h>
#include <engine/ncreport/engine.h>

namespace core = neoreport::core;
namespace engine = neoreport::engine;

int main(int argc, char **argv)
{
    core::init_log(0);

    LOG(debug) << "test debug";
    LOG(info) << "test info";
    LOG(error) << "test error";

    auto rpt = std::unique_ptr<core::Report>(new engine::ncreport::NCReportEngine(engine::ncreport::ReportSetting{
        .zint_dir = "./zint",
        .template_dir = "./template" ,  
        .output_dir  = "./output"            
    }));

    auto result = rpt->validateTemplate("test.rpt");
    LOG(info) << "validate result" << result.valid;

    return EXIT_SUCCESS;
}