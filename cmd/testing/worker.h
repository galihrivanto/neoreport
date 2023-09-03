// worker.h

#ifndef WORKER_H
#define WORKER_H

#include "ncreport.h"
#include <QObject>
#include <qeventloop.h>
#include <qfuture.h>
#include <qobject.h>
#include <qobjectdefs.h>
#include <qthread.h>

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

struct QRequest 
{
    QString templatePath;
    QString resultPath;
};

enum ResultType 
{
    Success = 1,
    Failed = 2
};

struct QResult 
{
    ResultType result;
    QString error;
};

class QWorker : public QObject
{
    Q_OBJECT

    public:
        QWorker(const QRequest &request);
        ~QWorker();

    public slots:
        void process();
    
    signals:
        void progress(QString message);
        void finished();
        void error(QString err);

    private:
        QRequest m_request;        
};

Q_DECLARE_METATYPE( QFutureInterface<QResult> );
class QManager : public QObject {
    Q_OBJECT 

    public:
        QManager();
        ~QManager();

        QFuture<QResult> enqueue(QRequest request);
        
};

#endif // WORKER_H