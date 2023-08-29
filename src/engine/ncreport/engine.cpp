#include "ncreportsource.h"
#include <engine/ncreport/engine.h>
#include <core/log.h>
#include <core/report.h>
#include <ncreport.h>
#include <qelapsedtimer.h>
#include <filesystem>
#include <qvariant.h>
#include <string>

namespace neoreport::engine::ncreport
{
    namespace core = neoreport::core;
    namespace fs = std::filesystem;

    QString pathJoin(std::string, std::string);

    core::Validation NCReportEngine::validateTemplate(std::string template_path)
    {
        NCReport rpt;

        return core::Validation::Success();
    }

    core::Response NCReportEngine::generate(const core::Request &request)
    {
        NCReport rpt;
        core::Response resp {.result=core::ReportResult::Success };
        QElapsedTimer timer;

        if (!this->m_zint_dir.empty()) {
            rpt.setZintPath(QString(this->m_zint_dir.c_str()));
        }

        // set template
        rpt.setReportSourceType(NCReportSource::File);
        rpt.setReportFile(pathJoin(this->m_template_dir, request.template_path));

        // set parameters
        for (const auto& [key, value]: request.parameters) {
            rpt.addParameter(QString::fromStdString(key), QString::fromStdString(value));
        }

        auto outputPath = pathJoin(this->m_output_dir, request.output_path);
        
        timer.start();
        switch (request.output_format) {
            case core::OutputFormat::PDF:
                rpt.runReportToPdfWriter(outputPath);
                break;
            case core::OutputFormat::XLS:
                rpt.runReportToExcelHtml(outputPath);
                break;
            case core::OutputFormat::HML:
                rpt.runReportToHTML(outputPath);
                break;
            default:
                return core::Response::failed();
                break;
        }

        // construct response
        resp.elapsed = timer.elapsed();
        if (rpt.hasError() || !rpt.lastErrorMsg().isEmpty())
        {
            resp.result = core::ReportResult::Failed;
            resp.error = rpt.lastErrorMsg().toStdString();    
        }

        return std::move(resp);
    }

    QString pathJoin(std::string p1, std::string p2)
    {
        return QString((fs::path{p1} /fs::path{p2}).c_str());
    }
}