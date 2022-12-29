#pragma once
#include <api_types.hpp>
#include <api_application.hpp>
#include <boost/asio.hpp> // TODO: change to needable hpp

namespace fb::api 
{
    using namespace boost::asio; // TODO: delete?

    class api_server
    {
    public:
        virtual ~api_server() {}

        virtual std::string read(ip::tcp::socket & socket) = 0;
        virtual void send(ip::tcp::socket & socket, const std::string& message) = 0;
    };
}
