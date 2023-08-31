// worker.h

#ifndef WORKER_H
#define WORKER_H

#include "ncreport.h"
#include <QObject>
#include <qeventloop.h>

class Worker : public QObject {
    Q_OBJECT

public:
    Worker(QString reportFile, QString outputFile) : m_report_file(reportFile), m_output_file(outputFile) {}
    ~Worker();

public slots:
    void run();

signals:
    void progress(QString);
    void finished();

private:
QString m_report_file;
QString m_output_file;
};

#endif // WORKER_H