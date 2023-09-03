// worker.cpp
#include "worker.h"
#include "ncreport.h"
#include "ncreportsource.h"
#include <QThread>
#include <iostream>
#include <memory>
#include <qthread.h>

Worker::~Worker() {}

void Worker::run() {
    emit progress("preparing report");

    NCReport rpt;
    rpt.setReportSourceType(NCReportSource::ReportSourceType::File);
    rpt.setReportFile(this->m_report_file);

    emit progress("generating report");
    rpt.runReportToPdfWriter(this->m_output_file);

    emit progress("report done");

    emit finished();
}

QWorker::QWorker(const QRequest &request) : m_request(request) {}

QWorker::~QWorker() {}

void QWorker::process() 
{
    if (this->m_request.templatePath.isEmpty() || this->m_request.resultPath.isEmpty())
    {
        emit error("template or destination is empty");
        return;
    }

    emit progress("processing report");

    NCReport rpt;
    rpt.setReportSourceType(NCReportSource::ReportSourceType::File);
    rpt.setReportFile(this->m_request.templatePath);

    emit progress("generating report");
    rpt.runReportToPdfWriter(this->m_request.resultPath);

    emit progress("report done");
    emit finished();
}

QManager::QManager() {}

QManager::~QManager() {}

QFuture<QResult> QManager::enqueue(QRequest request)
{
    auto futureInterface = std::make_shared<QFutureInterface<QResult>>(QFutureInterface<QResult>());
    futureInterface->reportStarted();

    QThread* thread = new QThread();
    QWorker* worker = new QWorker(request);
    worker->moveToThread(thread);

    connect(worker, &QWorker::progress, [](QString message){
        std::cout << message.toStdString() << std::endl;
    });
    connect(worker, &QWorker::error, [futureInterface](QString message){
        futureInterface->reportResult(QResult{
            .result = ResultType::Failed,
            .error = message 
        });
        futureInterface->reportFinished();
    });
    connect(thread, &QThread::started, worker, &QWorker::process);
    connect(worker, &QWorker::finished, thread, &QThread::quit);
    connect(worker, &QWorker::finished, [futureInterface](){
        std::cout << "finished signal" << std::endl;
        futureInterface->reportResult(QResult{
            .result = ResultType::Success,
        });
        futureInterface->reportFinished();
        std::cout << "what the hell is this" << std::endl;
    });
    connect(worker, &QWorker::finished, worker, &QWorker::deleteLater);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    thread->start(); 

    return futureInterface->future();
}

