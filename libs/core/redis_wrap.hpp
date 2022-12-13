#pragma once
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/address.hpp>
#include <redisclient/redissyncclient.h>
#include <memory>

namespace fb::core
{
    using ip_address = boost::asio::ip::address;
    using tcp_endpoint = boost::asio::ip::tcp::endpoint;
    using port = unsigned short;

    class redis_wrap
    {
    public:
        redis_wrap(std::string address, port p);
        redis_wrap();
    
    public:
        void connect();
        void write(std::pair<std::string, std::string> key_val);
        void write(std::pair<int, int> key_val);
        std::string get(std::string key);
        
    private:
        ip_address      _addr;
        port            _port;
        tcp_endpoint   _endpoint;

        boost::asio::io_service         _io_service;
        redisclient::RedisSyncClient    _redis_client;
    };
}
