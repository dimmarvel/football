#include "server.hpp"
#include <spdlog/spdlog.h>

namespace fb
{
    server::server(api::api_application& app)
    :
    _app(app),
    _acceptor(_app.get_context(), ip::tcp::endpoint(ip::tcp::v4(), 8080)),
    _socket(app.get_context())
    {

        spdlog::info("Accept on ip: {}", _acceptor.local_endpoint().address().to_string());
        _acceptor.accept(_socket);
        std::string message = read(_socket);
        spdlog::info("Recieve message: {}", message);
        send(_socket, "Hello From Server!");
    }

    std::string server::read(ip::tcp::socket& socket) 
    {
        boost::asio::streambuf buf;
        boost::asio::read_until( socket, buf, "\n" );
        std::string data = boost::asio::buffer_cast<const char*>(buf.data());
        return data;
    }

    void server::send(ip::tcp::socket& socket, const std::string& message) 
    {
        const std::string msg = message + "\n";
        boost::asio::write(socket, boost::asio::buffer(message) );
    }
    
    void server::start()
    {

    }

    void server::stop()
    {
        
    }
}