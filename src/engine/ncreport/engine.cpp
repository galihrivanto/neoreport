#include <engine/ncreport/engine.h>
#include <core/log.h>
#include <core/report.h>
#include <ncreport.h>

namespace neoreport::engine::ncreport
{

    namespace core = neoreport::core;

    core::Validation NCReportEngine::validateTemplate(std::string template_path)
    {
        NCReport rpt;
        return core::Validation::Success();
    }

    core::Response NCReportEngine::generate(const core::Request &request)
    {
        NCReport rpt;
        return core::Response::failed();
    }
}