#define BOOST_BIND_NO_PLACEHOLDERS

#include "server.hpp"
#include <spdlog/spdlog.h>
#include <boost/asio.hpp>
#include <server/connection.hpp>
#include <boost/bind.hpp>

namespace fb
{
    tcp_server::tcp_server(api::api_application& app)
    :
    _app(app), 
    _endpoint(boost::asio::ip::address_v4::any(), 8080),
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

        spdlog::info("[server] server start at: {}:{}", _endpoint.address().to_string(), _endpoint.port());

        start_accept();
    }
    
    void tcp_server::start_accept()
    {
        spdlog::info("[server] start accept connections...");
        api::connect_ptr new_connection = connection::create(_app);
        
        _acceptor.async_accept(new_connection->socket(),
            boost::bind(&tcp_server::handle_accept, 
                this, 
                new_connection,
                boost::asio::placeholders::error));

    }

    void tcp_server::handle_accept(api::connect_ptr new_connection, const boost::system::error_code& error)
    {
        spdlog::info("[server] new connection from: {}", new_connection->socket().remote_endpoint().address().to_string());

        if (error)
        {
            spdlog::error("[server] error connection accept");
            return;
        }

        _app.get_context().execute([self = shared_from_this(), new_connection]()
            { self->accept_connection_ev(std::move(new_connection)); });

        start_accept();
    }


}