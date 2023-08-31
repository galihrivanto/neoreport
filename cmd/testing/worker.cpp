// worker.cpp
#include "worker.h"
#include "ncreport.h"
#include "ncreportsource.h"
#include <QThread>
#include <iostream>

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