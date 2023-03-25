#pragma once

#define BOOST_BIND_NO_PLACEHOLDERS

#include <client/application.hpp>
#include <boost/bind.hpp>
#include <spdlog/spdlog.h>

namespace fb::client
{
    class application;
}

namespace fb
{
    using boost::asio::ip::tcp;

    class rpc
    {
    public:
        rpc(boost::asio::io_context& io_context, const std::string& server, const std::string& path);
        void start(ip::tcp::endpoint ep);
        
    private:
        void handle_resolve(const boost::system::error_code& err, const tcp::resolver::results_type& endpoints);
        void handle_connect(const boost::system::error_code& err);
        void handle_write_request(const boost::system::error_code& err);
        void handle_read_status_line(const boost::system::error_code& err);
        void handle_read_headers(const boost::system::error_code& err);
        void handle_read_content(const boost::system::error_code& err);

        tcp::resolver _resolver;
        tcp::socket _socket;
        boost::asio::streambuf _request;
        boost::asio::streambuf _response;
    };

}