#include "application.hpp"
#include <server/server.hpp>
#include <iostream>
#include <spdlog/spdlog.h>

namespace fb
{
    application::application(settings& s)
    :   
    _setting(s),
    _storage(std::make_shared<storage>()),
    _server(std::make_shared<server>(*this))
    {
        spdlog::info("[APP] Application created");
    }

    void application::start()
    {
        spdlog::info("[APP] Application start");
        auto work = boost::asio::make_work_guard(_context);
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

    boost::asio::io_context& application::get_context()
    {
        return _context;
    }
}
