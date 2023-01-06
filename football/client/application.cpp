#include "application.hpp"
#include <rpc/rpc.hpp>
#include <spdlog/spdlog.h>

namespace fb::client
{
    application::application(settings& s)
    :   
    _setting(s),
    _context(),
    _client(std::make_shared<rpc>(*this))
    {
        spdlog::info("[app] Application client created");
    }

    void application::start()
    {
        spdlog::info("[app] Application client start");
        _client->start(boost::asio::ip::tcp::endpoint(boost::asio::ip::address_v4::any(), 80));
        _context.run();
    }

    void application::stop()
    {
        spdlog::info("[app] Application client stop");
        _context.stop();
    }

    boost::asio::any_io_executor application::get_context()
    {
        return _context.get_executor();
    }
}
