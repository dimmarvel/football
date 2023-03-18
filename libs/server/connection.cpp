#define BOOST_BIND_NO_PLACEHOLDERS

#include <server/connection.hpp>
#include <server/application.hpp>
#include <functional>
#include <spdlog/spdlog.h>
#include <boost/bind.hpp>
#include <core/serialize.hpp>

namespace fb
{
    ip::tcp::socket& connection::socket()
    {
        return _socket;
    }

    void connection::send(std::string message)
    {
        spdlog::info("[server] send message: {}", message);

        boost::asio::async_write(_socket, boost::asio::buffer(message),
            boost::bind(&connection::handle_receive, shared_from_this(),
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }

    connection::connection(api::api_application& app)
    :
    _app(app),
    _socket(_app.get_context()),
    _rstrand(_app.get_context())
    {}
    
    void connection::start()
    {
        async_read();
    }

    void connection::async_read()
    {
        spdlog::info("[{}] start receive...", _socket.remote_endpoint().address().to_string());
        boost::asio::async_read(_socket, boost::asio::buffer(&_rsize, sizeof(decltype(_rsize))),
            [self = shared_from_this()](const boost::system::error_code& err, size_t read_bytes)
            {
                if(err)
                {
                    spdlog::error("connection error");
                    return;
                }
                
                spdlog::error("2 _rsize({}) read_bytes({}) _rbuffer({})", self->_rsize, read_bytes, self->_rbuffer);
                assert(read_bytes == sizeof(decltype(_rsize)));
                self->on_read();
            });
    }

    void connection::handle_receive(const boost::system::error_code & err, size_t read_bytes)
    {
        spdlog::info("[{}] recieve {}", _socket.remote_endpoint().address().to_string(), _rbuffer);
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

                spdlog::error("2 _rsize({}) read_bytes({}) _rbuffer({})", self->_rsize, read_bytes, self->_rbuffer);
                assert(read_bytes == sizeof(decltype(_rsize)));
                self->on_msg_ready();
            });
            
    }

    void connection::on_msg_ready()
    {
        spdlog::error("3 _rbuffer({})", _rbuffer);
        uint32_t num;
        memcpy(&num, _rbuffer.data(), 4);
        spdlog::error("3 _rbuffer({})", num);
        boost::asio::post(_rstrand, [self = shared_from_this()]() 
            { self->message_ev(self, self->_rbuffer); });
            
        async_read();
    }
}