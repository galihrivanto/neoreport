#ifndef NCREPORT_ENGINE_H
#define NCREPORT_ENGINE_H 

#include <core/report.h>

namespace neoreport::engine
{
    class QWorker;
    class QManager;

    struct NCReportEngineOptions
    {
        std::string zint_dir;
    };

    class NCReportEngine {
        public:
            NCReportEngine(const NCReportEngineOptions& options, int argc = 1) : m_options(options), m_manager(nullptr)
            {
                LOG(debug) << "NCReportEngine()";
                setup();
            }

            ~NCReportEngine() {
                LOG(debug) << "~NCReportEngine()";
                teardown();
            }

            core::Validation validate(const core::Request& req);
            void generate(std::string template_path, std::string output_path, core::OutputFormat output_format, core::Completed callback);

        private:
            QManager* m_manager;
            NCReportEngineOptions m_options;

            void setup();
            void teardown();
    };
}

#endif 