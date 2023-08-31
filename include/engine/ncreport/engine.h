#pragma once

#include <core/report.h>
#include <core/log.h>

namespace neoreport::engine::ncreport
{
    namespace core = neoreport::core;

    // report setting (dunno if needed)
    struct ReportSetting 
    {
        std::string zint_dir;
        std::string template_dir;
        std::string output_dir;
    };

    class NCReportEngine;
    core::Report* createNCReportEngine(const ReportSetting &setting);

    class NCReportManager;
    core::ReportManager* createNCReportManager(const ReportSetting &setting);    
}