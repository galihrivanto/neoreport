#include "boost/log/trivial.hpp"
#include "core/report.h"
#include <boost/program_options/variables_map.hpp>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <sstream>
#include <utility>
#include <zlib.h>
#include <stdio.h>
#include <cstring>
#include <boost/program_options.hpp>
#include <core/log.h>
#include <engine/ncreport/engine.h>
#include <core/thread_pool.h>

namespace core = neoreport::core;
namespace engine = neoreport::engine;

int main(int argc, char **argv)
{
    core::init_log(0);
    if (argc != 2) {
        LOG(error) << "invalid argument";
        return EXIT_FAILURE;
    }

    LOG(debug) << "file: " << argv[1];

    //core::ThreadPool tp(5);

    auto rpt1 = std::unique_ptr<core::Report>(engine::ncreport::createNCReportEngine(
        engine::ncreport::ReportSetting{
        .zint_dir = "",
        .template_dir = "" ,  
        .output_dir  = ""            
    }));

    // auto rpt2 = std::unique_ptr<core::Report>(engine::ncreport::createNCReportEngine(
    //     engine::ncreport::ReportSetting{
    //     .zint_dir = "",
    //     .template_dir = "" ,  
    //     .output_dir  = ""            
    // }));

    //tp.enqueue([&rpt1, &argc, &argv](){
    auto result = rpt1->generate(core::Request{
        .template_path = argv[1],
        .output_path = "./result1.pdf",
        .output_format = core::OutputFormat::PDF
    });
    LOG(info) << "generate result: " << (result.result == core::ReportResult::Success ? "success" : "failed") << " in " << result.elapsed;
    //});

    // tp.enqueue([&rpt2, &argc, &argv](){
    //     auto result = rpt2->generate(core::Request{
    //         .template_path = argv[1],
    //         .output_path = "./result2.pdf",
    //         .output_format = core::OutputFormat::PDF
    //     });
    //     LOG(info) << "generate result: " << (result.result == core::ReportResult::Success ? "success" : "failed") << " in " << result.elapsed;
    // });

        //  result = rpt->generate(core::Request{
        //     .template_path = argv[1],
        //     .output_path = "./result3.pdf",
        //     .output_format = core::OutputFormat::PDF
        // });
        // LOG(info) << "generate result: " << (result.result == core::ReportResult::Success ? "success" : "failed") << " in " << result.elapsed;

    // tp.enqueue([&rpt, &argc, &argv](){
    //     auto result = rpt->generate(core::Request{
    //         .template_path = argv[1],
    //         .output_path = "./result2.pdf",
    //         .output_format = core::OutputFormat::PDF
    //     });
    //     LOG(info) << "generate result: " << (result.result == core::ReportResult::Success ? "success" : "failed") << " in " << result.elapsed;
    // });

    // tp.enqueue([&rpt, &argc, &argv](){
    //     auto result = rpt->generate(core::Request{
    //         .template_path = argv[1],
    //         .output_path = "./result3.pdf",
    //         .output_format = core::OutputFormat::PDF
    //     });
    //     LOG(info) << "generate result: " << (result.result == core::ReportResult::Success ? "success" : "failed") << " in " << result.elapsed;
    // });
    

    

    // auto rpt = std::unique_ptr<core::Report>(engine::ncreport::createNCReportEngine(
    //     argc,
    //     argv,
    //     engine::ncreport::ReportSetting{
    //     .zint_dir = "",
    //     .template_dir = "" ,  
    //     .output_dir  = ""            
    // }));

    // auto result = rpt->generate(core::Request{
    //     .template_path = argv[1],
    //     .output_path = "./result.pdf",
    //     .output_format = core::OutputFormat::PDF
    // });
    // LOG(info) << "generate result: " << (result.result == core::ReportResult::Success ? "success" : "failed") << " in " << result.elapsed;

    return EXIT_SUCCESS;
}