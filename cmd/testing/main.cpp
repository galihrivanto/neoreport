// main.cpp

#include "ncreport.h"
#include "ncreportsource.h"
#include <cstdlib>
#include <format>
#include <qapplication.h>
#include <QtConcurrent/QtConcurrent>
#include <iostream>
#include "worker.h"
#include <fmt/core.h>
#include <qfuture.h>
#include <vector>

int main(int argc, char** argv)
{
    QApplication a(argc, argv);

    if (argc != 2)
    {
        std::cout << "invalid argument" << std::endl;
        return EXIT_FAILURE;
    }


    QManager manager;   
    std::vector<QFuture<QResult>> promises; 

    for (int i=1; i<=15;i++) {        
        promises.emplace_back(manager.enqueue(QRequest{
            .templatePath = argv[1],
            .resultPath = fmt::format("output{}.pdf", i).c_str()
        }));
    }

    for (auto promise: promises)
    {
        std::cout << "wait completed" << std::endl;
        promise.waitForFinished();
        std::cout << "completed" << std::endl;
        auto result  =promise.result();
        
        std::cout << "result :" << (result.result == ResultType::Success ? "success" : "failed") << std::endl;
    }
    

    return EXIT_SUCCESS;
}

// main.cpp