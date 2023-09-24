#ifndef APP_OPTIONS_H
#define APP_OPTIONS_H

#include <boost/program_options/variables_map.hpp>
#include <string>
#include <boost/program_options.hpp>

struct AppOptions {
    // general setting 
    uint log_level;

    std::string template_dir;
    std::string output_dir;
    uint num_worker;

    // TODO: add compile directive for ncreport specific options
    std::string zint_dir;

    // TODO: add compile directive for http api specific options
    uint port;
    std::string base_url;
};

void parse_options(int argc, char** argv, AppOptions& options); 

#endif 