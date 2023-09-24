#include "app/app_options.h"
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>
#include <iostream>

namespace po = boost::program_options;

void parse_options(int argc, char** argv, AppOptions& options)
{
    po::options_description desc("Report service");
    desc.add_options()
        ("help,h", "Print this help message and exit")

        ("log_level", po::value<uint>()->default_value(0), "log verbosity")
        ("template_dir", po::value<std::string>()->default_value("./template"), "path to template directory")
        ("output_dir", po::value<std::string>()->default_value("./output"), "path to output directory")
        ("num_worker", po::value<uint>()->default_value(4), "number of worker")
        
        // ncreport section
        ("zint_dir", po::value<std::string>()->default_value("./zint"), "path to zint directory")

        // http section 
        ("http_port", po::value<uint>()->default_value(5050), "http port")
        ("base_url", po::value<std::string>()->default_value("http://localhost", "service base url"))
    ;

    // TODO: add sub command

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(desc).run(), vm);
    po::notify(vm);

    if (vm.count("help"))
    {
        std::cout << desc << std::endl;
        return;
    }

    options.template_dir = vm["template_dir"].as<std::string>();
    options.output_dir = vm["output_dir"].as<std::string>();
    options.num_worker = vm["num_worker"].as<uint>();
    
    // ncreport
    options.zint_dir = vm["zint_dir"].as<std::string>();

    // http
    options.port = vm["http_port"].as<uint>();
    options.base_url = vm["base_url"].as<std::string>();
}