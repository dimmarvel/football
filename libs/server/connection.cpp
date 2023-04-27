#define BOOST_BIND_NO_PLACEHOLDERS

#include <server/connection.hpp>
#include <server/application.hpp>
#include <functional>
#include <spdlog/spdlog.h>
#include <boost/bind.hpp>
#include <core/serialize.hpp>
#include <boost/lexical_cast.hpp>

namespace fb
{

    connection::connection(api::api_application& app, api::socket_t s)
    :
    _app(app),
    _socket(std::move(s))
    {}

    ip::tcp::socket& connection::socket()
    {
        return _socket;
    }

    void connection::start()
    {
        async_read();
    }

    void connection::send(std::string message)
    {
        spdlog::info("[server] send message: {}", message);

        boost::asio::async_write(_socket, boost::asio::buffer(message),
            boost::bind(&connection::handle_receive, shared_from_this(),
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }

    void connection::async_read()
    {
        spdlog::info("[{}] start receive...", _socket.remote_endpoint().address().to_string());
        
        boost::asio::async_read(_socket, boost::asio::buffer(&_rsize, sizeof(size_t)),
            [self = shared_from_this()](const boost::system::error_code& err, size_t read_bytes)
            {
                if(err)
                {
                    spdlog::error("connection error");
                    return;
                }
                spdlog::warn("read size -> {}", self->_rsize);
                self->on_read();
            });
    }

    void connection::handle_receive(const boost::system::error_code & err, size_t read_bytes)
    {
        spdlog::info("[{}] recieve {}", _socket.remote_endpoint().address().to_string(), _rbuffer);
        async_read();
    }

    void connection::on_read()
    {
        if(_rbuffer.size() < _rsize) //TODO: refactor
            _rbuffer.resize(_rsize);

        spdlog::info("[{}] read buffer from {}", _socket.remote_endpoint().address().to_string(), _rbuffer);
        boost::asio::async_read(_socket, boost::asio::buffer(_rbuffer.data(), _rsize),
            [self = shared_from_this()](const boost::system::error_code& err, size_t read_bytes)
            {
                if(err)
                {
                    spdlog::error("connection error 2");
                    return;
                }
                spdlog::info("[con] read size == {}", self->_rsize);
                assert(read_bytes == self->_rsize);
                self->on_msg_ready();
            });
            
    }

    void connection::on_msg_ready()
    {
        spdlog::info("[] recieve {}", _socket.remote_endpoint().address().to_string(), _rbuffer);
        _app.get_context().post([self = shared_from_this()]() 
            { self->message_ev(self, self->_rbuffer); });
            
        async_read();
    }
}