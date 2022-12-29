#pragma once
#include <api_storage.hpp>

#include <boost/asio/ip/address.hpp>
#include <core/database/defines.hpp>
#include <sw/redis++/redis++.h>

namespace fb::core
{
    using namespace boost::asio;
    using port = unsigned short;

    class redis_wrap
    {
    public:
        redis_wrap(std::string address, port p);
        redis_wrap();
    
    public:
        void write(api::table t, std::pair<std::string, std::string> key_val);
        void write(api::table t, std::pair<int, int> key_val);

        std::string get(api::table t, std::string key);
        std::string get(api::table t, int key);
        std::unordered_set<std::string> get_keys(api::table t, std::string pattern = "*");

        size_t erase(api::table t, std::string key);
        size_t erase(api::table t, int key);
    
    protected:
        void choice_table(api::table t);
        
    protected:
        ip::address     _addr;
        port            _port;
        api::table      _table_cache;
        std::string     _full_addr;   // example: tcp://127.0.0.1:6379

        sw::redis::Redis _redis;
    };
}
