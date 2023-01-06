#include "redis_wrap.hpp"
#include <spdlog/spdlog.h>

namespace fb::core
{
    std::string to_connect_str(std::string addr, port p)
    {
        return std::string("tcp://" + addr + ":" + std::to_string(p));
    }
    
    redis_wrap::redis_wrap(std::string address, port p)
    :
    _addr(ip::make_address(address)),
    _port(p),
    _table_cache(0),
    _full_addr(to_connect_str(address, p)),
    _redis(_full_addr)
    {
        spdlog::info("[RedisDB] Connect to: {}", _full_addr);
    }

    redis_wrap::redis_wrap()
    :
    _addr(ip::make_address("127.0.0.1")), // TODO: create constant
    _port(6379),
    _table_cache(0),
    _full_addr(to_connect_str("127.0.0.1", _port)),
    _redis(_full_addr)
    {
        spdlog::info("[RedisDB] Connect to local: {}", _full_addr);
    }

    void redis_wrap::write(api::table t, std::pair<std::string, std::string> key_val)
    {
        choice_table(t);
        _redis.set(key_val.first, key_val.second);
    }

    void redis_wrap::write(api::table t, std::pair<int, int> key_val)
    {
        choice_table(t);
        _redis.set(std::to_string(key_val.first), std::to_string(key_val.second));
    }

    std::string redis_wrap::get(api::table t, std::string key)
    {
        choice_table(t);
        auto val = _redis.get(key);
        if (val) return *val;
        return "";
    }

    std::string redis_wrap::get(api::table t, int key)
    {
        choice_table(t);
        auto val = _redis.get(std::to_string(key));
        if (val) return *val;
        return "";
    }

    void redis_wrap::choice_table(api::table t)
    {
        if(_table_cache == t) return;
        _table_cache = t;
        _redis.command<void>("SELECT", t);
    }

    std::unordered_set<std::string> redis_wrap::get_keys(api::table t, std::string pattern)
    {
        choice_table(t);
        std::unordered_set<std::string> keys;
        _redis.keys(pattern, std::inserter(keys, keys.begin()));
        return keys;
    }

    size_t redis_wrap::erase(api::table t, std::string key)
    {
        choice_table(t);
        return _redis.del(key);
    }

    size_t redis_wrap::erase(api::table t, int key)
    {
        choice_table(t);
        return _redis.del(std::to_string(key));
    }
}
