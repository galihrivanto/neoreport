#ifndef NCREPORT_ENGINE_H
#define NCREPORT_ENGINE_H 

#include <qobject.h>
#include <core/report.h>

namespace neoreport::engine
{
    class QWorker : public QObject
    {
        Q_OBJECT

        public:
            QWorker(
                QString template_path,
                QString output_path,
                QString zint_dir,
                core::OutputFormat output_format
            ) : 
            m_template_path(template_path),
            m_output_path(output_path),
            m_zint_dir(zint_dir),
            m_format(output_format) {}

            ~QWorker();

        public slots:
            void process();
        
        signals:
            void progress(QString message);
            void finished();
            void error(QString err);

        private:
            QString m_template_path;
            QString m_output_path;
            QString m_zint_dir;
            core::OutputFormat m_format;     
    };

    class QManager : public QObject {
        Q_OBJECT 

        public:
            QManager() {}
            ~QManager() {}

        core::Response generate(QString zint_dir, QString template_path, QString output_path, core::OutputFormat format);            
    };

    struct NCReportEngineOptions
    {
        std::string zint_dir;
    };

    class NCReportEngine {
        public:
            NCReportEngine(const NCReportEngineOptions& options) : m_options(options)
            {
                LOG(debug) << "NCReportEngine()";
                m_manager = new QManager();
            }

            ~NCReportEngine() {
                LOG(debug) << "~NCReportEngine()";
                delete m_manager;
            }

            core::Validation validate(const core::Request& req);
            void generate(std::string template_path, std::string output_path, core::OutputFormat output_format, core::Completed callback);

        private:
            QManager* m_manager;
            NCReportEngineOptions m_options;
    };
}

#endif 