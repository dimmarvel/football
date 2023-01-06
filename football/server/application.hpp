#pragma once
#include <api_application.hpp>
#include <server/server.hpp>
#include <config/settings.hpp>
#include <storage/storage.hpp>

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

        std::shared_ptr<tcp_server>         _server;
        std::shared_ptr<api::api_storage>   _storage;
    };
}
