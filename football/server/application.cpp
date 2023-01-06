#include "application.hpp"
#include <spdlog/spdlog.h>

namespace fb
{
    application::application(settings& s)
    :   
    _setting(s),
    _context(),
    _server(std::make_shared<tcp_server>(*this)),
    _storage(std::make_shared<storage>())
    {
        spdlog::info("[app] Application server created");
    }

    void application::start()
    {
        spdlog::info("[app] Application server start");
        _server->start();
        _context.run();
    }

    void application::stop()
    {
        spdlog::info("[app] Application server stop");
        _context.stop();
    }

    std::shared_ptr<api::api_storage> application::get_storage()
    {
        return _storage;
    }

    boost::asio::any_io_executor application::get_context()
    {
        return _context.get_executor();
    }
}
