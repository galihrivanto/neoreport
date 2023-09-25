#include "core/report.h"
#include <ncreport/engine.h>
#include <ncreport.h>
#include <qthread.h>
#include "q_engine.h"

namespace neoreport::engine
{
    void QWorker::process() 
    {
        if (this->m_template_path.isEmpty() || this->m_output_path.isEmpty())
        {
            emit error("template or destination is empty");
            return;
        }

        emit progress("processing report");

        NCReport rpt;
        rpt.setReportSourceType(NCReportSource::ReportSourceType::File);
        rpt.setReportFile(this->m_template_path);

        emit progress("generating report");
        rpt.runReportToPdfWriter(this->m_output_path);

        emit progress("report done");
        emit finished();
    }


    core::Response generate(QString zint_dir, QString template_path, QString output_path, core::OutputFormat format)
    {
        QThread* thread = new QThread();
        QWorker* worker = new QWorker(template_path, output_path, zint_dir, format);
        worker->moveToThread(thread);

        QObject::connect(worker, &QWorker::progress, [](QString message){
            LOG(debug) << message.toStdString() << std::endl;
        });
        QObject::connect(worker, &QWorker::error, [](QString message){
            
        });
        QObject::connect(thread, &QThread::started, worker, &QWorker::process);
        QObject::connect(worker, &QWorker::finished, thread, &QThread::quit);
        QObject::connect(worker, &QWorker::finished, [](){
            
        });
        QObject::connect(worker, &QWorker::finished, worker, &QWorker::deleteLater);
        QObject::connect(thread, &QThread::finished, thread, &QThread::deleteLater);
        thread->start(); 

        thread->wait();

        return core::Response::failed();
    }

    core::Validation validate(const core::Request& request) {
        return core::Validation::Success();
    }

    void NCReportEngine::generate(std::string template_path, std::string output_path, core::OutputFormat output_format, core::Completed callback) {
        auto resp = m_manager->generate(
            QString::fromStdString(m_options.zint_dir),
            QString::fromStdString(template_path),
            QString::fromStdString(output_path),
            output_format
        );

        callback(std::move(resp));
    }

    void NCReportEngine::setup()
    {
        m_manager = new QManager();
    }

    void NCReportEngine::teardown()
    {
        delete m_manager;
    }
}