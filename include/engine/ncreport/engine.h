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


    class NCReportEngine : public core::Report
    {
        public:
            NCReportEngine(const ReportSetting& setting) : 
                m_zint_dir(setting.zint_dir), 
                m_template_dir(setting.template_dir), 
                m_output_dir(setting.output_dir)
            {
                LOG(debug) << "initiating ncreport engine";
            }

            virtual ~NCReportEngine() {
                LOG(debug) << "destroying ncreport engine";
            }
    
            virtual core::Validation validateTemplate(std::string template_path) override;
            virtual core::Response generate(const core::Request &request) override;

        private:
            std::string m_zint_dir;
            std::string m_template_dir;
            std::string m_output_dir;
    };
}