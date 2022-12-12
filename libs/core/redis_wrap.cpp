#include "redis_wrap.hpp"
#include <spdlog/spdlog.h>

namespace fb::core
{
    void error_handle(redisclient::RedisValue r)
    {
        if(r.isError())
            spdlog::error("[RedisDB] Error: " + r.toString());
        if(!r.isOk())
            spdlog::error("[RedisDB] Error: " + r.toString());
    }

    redis_wrap::redis_wrap(std::string address, port p)
    :
    _addr(ip_address::from_string(address)),
    _port(p),
    _endpoint(_addr, _port),
    _redis_client(_io_service)
    {
        spdlog::info("[RedisDB] Connect to: {}:{}", _addr.to_string(), _port);
        connect();
    }

    redis_wrap::redis_wrap()
    :
    _addr(ip_address::from_string("127.0.0.1")), // TODO: create constant
    _port(6379),
    _endpoint(_addr, _port),
    _redis_client(_io_service)
    {
        spdlog::info("[RedisDB] Connect to local: {}:{}", _addr.to_string(), _port);
        connect();
    }

    void redis_wrap::connect()
    {
        boost::system::error_code ec;
        _redis_client.connect(_endpoint, ec);
        if(ec) throw std::runtime_error("[RedisDB] Can't connect to redis: " + ec.message());
    }

    void redis_wrap::write(std::pair<std::string, std::string> key_val)
    {
        redisclient::RedisValue r = _redis_client.command("SET", {key_val.first, key_val.second});
        error_handle(r);
    }

    void redis_wrap::write(std::pair<int, int> key_val)
    {
        redisclient::RedisValue r = 
            _redis_client.command("SET", {std::to_string(key_val.first), std::to_string(key_val.second)});
        error_handle(r);
    }
    

    std::string redis_wrap::get(std::string key)
    {
        redisclient::RedisValue r = _redis_client.command("GET", {key});
        error_handle(r);
        return r.toString();
    }
}