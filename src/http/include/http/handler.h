#ifndef HTTP_HANDLER_H
#define HTTP_HANDLER_H 

#include <string>
#include <core/report.h>
#include <crow.h>

namespace neoreport::api
{
    struct HttpOptions {
        uint port;
        std::string base_url;
    };

    struct RegisterRequest
    {
        std::string slug;
        std::string template_content;
    };

    // testing middleware from example
    struct RequestLogger
    {
        struct context
        {};

        // This method is run before handling the request
        void before_handle(crow::request& req, crow::response& /*res*/, context& /*ctx*/)
        {
            CROW_LOG_INFO << "Request to:" + req.url;
        }

        // This method is run after handling the request
        void after_handle(crow::request& /*req*/, crow::response& /*res*/, context& /*ctx*/)
        {}
    };

    template <class E>
    void setup_http_handlers(core::ReportManager<E> *manager, const HttpOptions& options) {
        // test with middleware
        crow::App<RequestLogger> app;
        
        CROW_ROUTE(app, "/register")
        .methods("POST"_method)([](const crow::request& req) {
            auto x = crow::json::load(req.body);
            if (!x)
                return crow::response(400);
            
            // TODO: parse body

            return crow::response{};
        });

        CROW_ROUTE(app, "/generate")
        .methods("POST"_method)([&](const crow::request& req) {
            auto x = crow::json::load(req.body);
            if (!x)
                return crow::response(400);
            
            // dummy generate
            manager->generate(core::Request{
                .template_path = "../reports/google_charts/xml",
                .output_path = "neoresult/pdf"
            });

            return crow::response{};
        });
    }
}

#endif 