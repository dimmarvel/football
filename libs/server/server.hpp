#pragma once
#include <api_application.hpp>
#include <api_server.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

namespace fb
{
    using namespace boost::asio; // TODO: delete?

    class connection : public std::enable_shared_from_this<connection>
    {
    public:
        typedef std::shared_ptr<connection> con_ptr;

        static con_ptr create(boost::asio::any_io_executor ctx)
        {
            return con_ptr{new connection(ctx)};
        }

        ip::tcp::socket& socket();
        void send(std::string message);

    private:
        connection(boost::asio::any_io_executor ctx);

        void handle_write(const boost::system::error_code& err, size_t s);

    private:
        ip::tcp::socket _socket;
    };

    class tcp_server
    {
    public:
        tcp_server(api::api_application& app);

        void start();
    private:
        void start_accept();
        void handle_accept(connection::con_ptr new_connection, const boost::system::error_code& error);

        api::api_application&   _app;
        ip::tcp::endpoint       _endpoint;
        ip::tcp::acceptor       _acceptor;
    };

}