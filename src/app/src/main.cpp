#include "core/report.h"
#include <app/app_options.h>
#include <core/log.h>
#include <ncreport/engine.h>
#include <http/handler.h>

namespace core = neoreport::core;
namespace engine = neoreport::engine;
namespace api = neoreport::api;

int main(int argc, char** argv) {
    AppOptions options;
    parse_options(argc, argv, options);

    core::init_log(options.log_level);

    LOG(debug) << "template: " << options.template_dir;

    auto engine = new engine::NCReportEngine(engine::NCReportEngineOptions{});
    auto manager = new core::ReportManager<engine::NCReportEngine>(engine, core::ReportManagerOption{
        .template_dir = options.template_dir,
        .output_dir = options.output_dir,
        .num_worker = options.num_worker
    });

    // setup and run http api 
    api::setup_http_handlers(manager, api::HttpOptions{
        .port = options.port,
        .base_url = options.base_url
    });

    return 0;
}