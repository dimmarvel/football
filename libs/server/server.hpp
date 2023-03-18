#pragma once

#define BOOST_BIND_NO_PLACEHOLDERS

#include <api_server.hpp>
#include <mutex>

namespace fb
{
    using namespace boost::asio; // TODO: delete?

    class tcp_server :  public api::api_server,
                        public std::enable_shared_from_this<tcp_server>,
                        public api::server_events
    {
    public:
        tcp_server(api::api_application& app);

        virtual void start() override;

    private:
        void start_accept() override;
        void handle_accept(api::connect_ptr new_conn, const boost::system::error_code& error) override;

    private:
        std::mutex              _mutex;
        api::api_application&   _app;
        ip::tcp::endpoint       _endpoint;
        ip::tcp::acceptor       _acceptor;
    };

}