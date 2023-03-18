#pragma once
#include <api_application.hpp>
#include <api_hub.hpp>
#include <server/server.hpp>
#include <config/settings.hpp>
#include <api_storage.hpp>

namespace fb
{
    class application : public api::api_application
    {
    public:
        application(settings& s);
        ~application() override {}

    public:
        virtual void start() override;
        virtual boost::asio::any_io_executor get_context() override;
        virtual std::shared_ptr<api::api_storage> get_storage() override;
        
        void stop();

    private:
        settings& _setting;
        boost::asio::io_context _context;

        std::shared_ptr<api::api_hub>       _hub;
        std::shared_ptr<api::api_storage>   _storage;
    };
}
