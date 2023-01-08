#include "server.hpp"
#include <spdlog/spdlog.h>
#include <boost/asio/io_context.hpp>

namespace fb
{
    tcp_server::tcp_server(api::api_application& app)
    :
    _app(app), 
    _endpoint(boost::asio::ip::address_v4::any(), 80),
    _acceptor(app.get_context()),
    _timer(_app.get_context(), 5000) //5000 to constant
    {
        _timer.start([this]() -> bool
        {
            show_connections();
            return false;
        });
    }

    void tcp_server::start()
    {
        spdlog::info("[server] server start at: {}", _endpoint.address().to_string());
        
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
        connection::con_ptr new_connection = connection::create(_acceptor.get_executor());
        
        _acceptor.async_accept(new_connection->socket(),
            boost::bind(&tcp_server::handle_accept, 
                this, 
                new_connection,
                boost::asio::placeholders::error));

    }

    void tcp_server::handle_accept(connection::con_ptr new_connection, const boost::system::error_code& error)
    {
        spdlog::info("[server] new connection from: {}", new_connection->socket().remote_endpoint().address().to_string());

        if (!error)
            new_connection->send("ping\n");

        _connections.push_back(new_connection);
        start_accept();
    }

    void tcp_server::show_connections()
    {
        spdlog::info("----------Connections({})----------", _connections.size());
        for(size_t i = 0; i < _connections.size(); i++)
            spdlog::info("{}) address - {}", i, _connections[i]->socket().remote_endpoint().address().to_string());
        spdlog::info("----------------------------------");
    }

    ip::tcp::socket& connection::socket()
    {
        return _socket;
    }

    void connection::send(std::string message)
    {
        spdlog::info("[server] send message: {}", message);
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
        char buff[1024] = {};
        _socket.async_receive(boost::asio::buffer(buff), std::bind(&connection::send, shared_from_this(), "ping\n"));
    }
}