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

        spdlog::info("[server] server start at: {}", _endpoint.address().to_string());

        start_accept();
    }
    
    void tcp_server::start_accept()
    {
        spdlog::info("[server] start accept connections...");
        auto self = shared_from_this();
        _acceptor.async_accept([self](const boost::system::error_code& error, api::socket_t sock)
        {
            //TODO: handle errors
            self->handle_accept(std::move(sock), error);
        });
    }

    void tcp_server::handle_accept(api::socket_t&& sock, const boost::system::error_code& error)
    {
        spdlog::info("[server] new connection from: {}", sock.remote_endpoint().address().to_string());

        if (error)
        {
            spdlog::error("[server] error connection accept");
            return;
        }
        auto c = connection::create(_app, std::move(sock));
        
        _app.get_context().post([self = shared_from_this(), c]()
            { self->accept_connection_ev(std::move(c)); });
        _app.get_context().
        start_accept();
    }


}