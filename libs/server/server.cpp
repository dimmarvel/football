#include "server.hpp"
#include <spdlog/spdlog.h>
#include <boost/asio/io_context.hpp>

namespace fb
{
    tcp_server::tcp_server(api::api_application& app)
    :
    _app(app), 
    _endpoint(boost::asio::ip::address_v4::any(), 80),
    _acceptor(app.get_context())
    {}

    void tcp_server::start()
    {
        if(_acceptor.is_open())
            return; //TODO: handler
        
        _acceptor.open(_endpoint.protocol());
        _acceptor.set_option(ip::tcp::socket::reuse_address(true));
        
        _acceptor.bind(_endpoint);
        _acceptor.listen();
        start_accept();
    }
    
    void tcp_server::start_accept()
    {
        connection::con_ptr new_connection =
        connection::create(_acceptor.get_executor());

        _acceptor.async_accept(new_connection->socket(),
            boost::bind(&tcp_server::handle_accept, 
                this, 
                new_connection,
                boost::asio::placeholders::error));
    }

    void tcp_server::handle_accept(connection::con_ptr new_connection, const boost::system::error_code& error)
    {
        if (!error)
        {
            new_connection->send("Success connection");
        }

        start_accept();
    }

    ip::tcp::socket& connection::socket()
    {
        return _socket;
    }

    void connection::send(std::string message)
    {
        boost::asio::async_write(_socket, boost::asio::buffer(message),
            boost::bind(&connection::handle_write, shared_from_this(),
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }

    connection::connection(boost::asio::any_io_executor ctx)
    : _socket(ctx)
    {}

    void connection::handle_write(const boost::system::error_code& err, size_t s)
    {

    }
}