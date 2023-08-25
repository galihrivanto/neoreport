#pragma once 

#include <map>
#include <string>

namespace neoreport::core
{
    enum class ReportResult 
    {
        Success = 1, 
        Failed = 2 
    };

    enum class OutputFormat 
    {
        PDF = 1,
        XLS = 2,
        HML = 3,
        NONE 
    };

    // Response define report execution result
    struct Response 
    {
        ReportResult result;

        // completion time
        int elapsed;  

        // error message when failed
        std::string error;

        static Response failed() 
        {
            return Response {
                .result = ReportResult::Failed
            };
        }
    };

    // Validation define template validation result 
    struct Validation 
    {
        bool valid;

        std::string error;

        static Validation Success() {
            return Validation{
                .valid = true 
            };
        };
    };

    // Request define report parameters 
    struct Request 
    {
        std::string id;
        std::string template_path;
        std::string output_path;
        OutputFormat output_format;

        // TODO: use dynamic variant type
        std::map<std::string, std::string> parameters;

        bool valid() const {
            return !id.empty()
                && !output_path.empty()
                && !template_path.empty()
                && output_format != OutputFormat::NONE;
        }
    };
  
    // define report operation
    class Report 
    {
        public:
            virtual ~Report() = default;

            virtual Validation validateTemplate(std::string template_path) = 0; 
            virtual Response generate(const Request &request) = 0;
    };
}