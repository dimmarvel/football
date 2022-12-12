#include <iostream>
#include <spdlog/spdlog.h>
#include "application.hpp"
#include <config/settings.hpp>


#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/address.hpp>
#include <redisclient/redissyncclient.h>

void redis_test()
{
    boost::asio::ip::address address = boost::asio::ip::address::from_string("127.0.0.1");
    const unsigned short port = 6379;
    boost::asio::ip::tcp::endpoint endpoint(address, port);

    boost::asio::io_service ioService;
    redisclient::RedisSyncClient redis(ioService);
    boost::system::error_code ec;

    redis.connect(endpoint, ec);

    if(ec)
    {
        std::cerr << "Can't connect to redis: " << ec.message() << std::endl;
    }

    redisclient::RedisValue result;

    result = redis.command("SET", {"key", "value"});

    if( result.isError() )
    {
        std::cerr << "SET error: " << result.toString() << "\n";
    }

    result = redis.command("GET", {"key"});

    if( result.isOk() )
    {
        std::cout << "GET: " << result.toString() << "\n";
    }
    else
    {
        std::cerr << "GET error: " << result.toString() << "\n";
    }
}

int main(int argc, const char** argv)
{
    try
    {
        redis_test();
        fb::settings setting;
        setting.parse(argc, argv);

        fb::application app(setting);
        app.start();
        spdlog::info("Hello world");
    }
    catch(const std::exception& e)
    {
        spdlog::error("unhandled exception: {}", e.what());
        return 1; 
    }

    return 0;
}
