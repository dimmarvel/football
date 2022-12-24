#pragma once
#include <api_storage.hpp>

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/address.hpp>
#include <redisclient/redissyncclient.h>
#include <core/database/defines.hpp>

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
        void write(api::table t, std::pair<std::string, std::string> key_val);
        void write(api::table t, std::pair<int, int> key_val);
        void write_list(api::table t, std::pair<std::string, std::string> key_val);

        std::string get(api::table t, std::string key);
        std::string get(api::table t, int key);
    
    private:
        void change_table(api::table t);
        void connect();

    private:
        ip_address      _addr;
        port            _port;
        tcp_endpoint    _endpoint;
        api::table      _table_cache;

        boost::asio::io_service         _io_service;
        redisclient::RedisSyncClient    _redis_client;

    };
}
