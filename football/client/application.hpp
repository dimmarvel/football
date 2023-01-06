#pragma once
#include <config/settings.hpp>
#include <boost/asio.hpp>

namespace boost::asio
{
    class any_io_executor;
}

namespace fb
{
    class rpc;
}

namespace fb::client
{
    class application
    {
    public:
        application(settings& s);
        ~application() {}

    public:
        void start();
        void stop();

        boost::asio::any_io_executor get_context();

    private:
        settings& _setting;
        boost::asio::io_context _context;

        std::shared_ptr<fb::rpc> _client;
    };
}
