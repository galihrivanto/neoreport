#pragma once 

#include <core/report.h>
#include <engine/ncreport/engine.h>
#include <memory>
#include <qapplication.h>

namespace neoreport::engine::ncreport
{ 
    class NCReportEngine : public core::Report
    {
        public:
            NCReportEngine(const ReportSetting& setting) : 
                m_zint_dir(setting.zint_dir), 
                m_template_dir(setting.template_dir), 
                m_output_dir(setting.output_dir)
            {
                LOG(debug) << "initiating ncreport engine";

                int argc;
                m_app = new QApplication(argc, nullptr);
            }

            NCReportEngine(QApplication* app, const ReportSetting& setting) :
                m_zint_dir(setting.zint_dir), 
                m_template_dir(setting.template_dir), 
                m_output_dir(setting.output_dir)
            {
                LOG(debug) << "initiating ncreport engine";

                m_app = app;
            }

            virtual ~NCReportEngine() {
                LOG(debug) << "destroying ncreport engine";

                delete m_app;
            }
    
            virtual core::Validation validateTemplate(std::string template_path) override;
            virtual core::Response generate(const core::Request &request) override;

        private:
            QApplication* m_app;
            std::string m_zint_dir;
            std::string m_template_dir;
            std::string m_output_dir;
    };

    class NCReportManager : core::ReportManager
    {
        public:
            NCReportManager(const ReportSetting& setting) : 
                m_zint_dir(setting.zint_dir), 
                m_template_dir(setting.template_dir), 
                m_output_dir(setting.output_dir)
            {
                LOG(debug) << "initiating ncreport manager";

                int argc;
                m_app = new QApplication(argc, nullptr);
            }

            NCReportManager(QApplication* app, const ReportSetting& setting) :
                m_zint_dir(setting.zint_dir), 
                m_template_dir(setting.template_dir), 
                m_output_dir(setting.output_dir)
            {
                LOG(debug) << "initiating ncreport manager";

                m_app = app;
            }

            virtual ~NCReportManager() {
                LOG(debug) << "destroying ncreport manager";

                delete m_app;
            }

            virtual std::future<core::Response> enqueue(const core::Request &request) override;

        private:
            QApplication* m_app;
            std::string m_zint_dir;
            std::string m_template_dir;
            std::string m_output_dir;
    };
}