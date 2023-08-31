#include "core/log.h"
#include "ncreport.h"
#include "ncreportsource.h"
#include <boost/log/trivial.hpp>
#include <cstdlib>
#include <format>
#include <qapplication.h>
#include <QtConcurrent/QtConcurrent>
#include <iostream>
#include "worker.h"
#include <fmt/core.h>

int main(int argc, char** argv)
{
    QApplication a(argc, argv);

    if (argc != 2)
    {
        std::cout << "invalid argument" << std::endl;
        return EXIT_FAILURE;
    }

    // std::cout << "testing";

    // std::cout << "from thread"<< std::endl;
    // NCReport rpt;
    // std::cout << "argv"<< std::endl;;
    // rpt.setReportFile("../reports/google_charts.xml");

    // std::cout << "rendering"<< std::endl;
    // rpt.runReportToPdfWriter("./output.pdf");

    for (int i=1; i<=5;i++) {
        QThread* thread = new QThread();
        Worker* worker = new Worker(argv[1], fmt::format("output{}.pdf", i).c_str());

        QObject::connect(worker, &Worker::progress, [](QString message){
            std::cout << "Progress: " << message.toStdString() << std::endl;
        });

        // QObject::connect(worker, &Worker::finished, &a, &QCoreApplication::quit);    
        QObject::connect(thread, &QThread::started, worker, &Worker::run);

        worker->moveToThread(thread);
        thread->start();
    }
    

    return a.exec();
}