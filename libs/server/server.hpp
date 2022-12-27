#pragma once
#include <api_application.hpp>
#include <api_server.hpp>

namespace fb
{
    using namespace boost::asio; // TODO: delete?

    class server : public api::api_server
    {
    public:
        server(api::api_application& app);
        ~server() override {}

        virtual std::string read(ip::tcp::socket & socket) override;
        virtual void send(ip::tcp::socket & socket, const std::string& message) override;

        void start();
        void stop();

    private:
        api::api_application&   _app;
        ip::tcp::acceptor       _acceptor;
        ip::tcp::socket         _socket;
    }
}