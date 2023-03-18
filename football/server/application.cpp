#include "application.hpp"
#include <spdlog/spdlog.h>
#include <storage/storage.hpp>
#include <server/hub.hpp>

namespace fb
{
    application::application(settings& s)
    :   
    _setting(s),
    _context(),
    _hub(std::make_shared<hub>(*this)),
    _storage(std::make_shared<storage>())
    {
        spdlog::info("[app] Application server created");
    }

    void application::start()
    {
        spdlog::info("[app] Application server start");
        _hub->start();
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
