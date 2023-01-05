#include "application.hpp"
#include <spdlog/spdlog.h>

namespace fb
{
    application::application(settings& s)
    :   
    _setting(s),
    _context(),
    //_threads(_context),
    _server(std::make_shared<tcp_server>(*this)),
    _storage(std::make_shared<storage>())
    {
        spdlog::info("[APP] Application created");
    }

    void application::start()
    {
        spdlog::info("[APP] Application start");
        _server->start();
        _context.run();
    }

    void application::stop()
    {
        spdlog::info("[APP] Application stop");
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
