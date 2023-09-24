#pragma once 

#include "thread_pool.h"
#include <boost/log/trivial.hpp>
#include <map>
#include <string>
#include "log.h"
#include <boost/filesystem.hpp>
#include <functional>

namespace fs = boost::filesystem;

namespace neoreport::core
{
    const std::string TEMPLATE_FILE = "template.xml";

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

    // generate random id 
    std::string random_id();

    struct ReportManagerOption
    {
        std::string template_dir;
        std::string output_dir;

        uint num_worker;
    };

    using Completed = std::function<void(Response)>;

    template <class E>
    class ReportManager
    {
        public:
            ReportManager() = delete;
            ReportManager(const ReportManager<E>&) = delete;

            ReportManager(E* engine, const ReportManagerOption& options) : m_engine(engine), m_options(options) {
                LOG(debug) << "ReportManager()";
                if (m_options.num_worker <= 0) {
                    m_options.num_worker = 1;
                }

                LOG(debug) << "initial thread pool with num_worker: " << m_options.num_worker;

                // initiatelize thread pool
                m_pool = new ThreadPool(m_options.num_worker);
            }

            ~ReportManager() {
                LOG(debug) << "~ReportManager()";
                if (m_pool != nullptr)
                {
                    delete m_pool;
                }
            }

            Validation validate(const Request& req) {
                m_engine->validate(req);
            }

            std::string generate(const Request& req) {
                // connstruct request 
                auto id = random_id();

                // set template and output location
                auto templatePath =  fs::path(m_options.template_dir).append(req.template_path).append(TEMPLATE_FILE);
                auto outputPath = fs::path(m_options.output_dir).append(id);

                switch (req.output_format)
                {
                    case OutputFormat::PDF:
                        outputPath.replace_extension(".pdf");
                        break;
                    case OutputFormat::XLS:
                        outputPath.replace_extension(".xls");
                        break;
                    default:
                        break;
                }

                m_pool->enqueue([&](const Request& req){
                    m_engine->generate(
                        templatePath.string(),
                        outputPath.string(),
                        req.output_format,
                        [&](Response resp) {
                            // TODO: handle on completion status
                            LOG(debug) << "response " << resp.error;
                        }
                    );
                }, req);
            }

        private:
            E* m_engine;
            ThreadPool* m_pool;

            ReportManagerOption m_options;
    };
}