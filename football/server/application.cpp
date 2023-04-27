#include "application.hpp"
#include <spdlog/spdlog.h>
#include <storage/storage.hpp>
#include <server/hub.hpp>

namespace fb
{
    application::application(settings& s)
    :   
    _setting(s),
    _threads(_context),
    _hub(std::make_shared<hub>(*this)),
    _storage(std::make_shared<storage>())
    {
        spdlog::info("[app] Application server created");
    }

    void application::start()
    {
        std::size_t n = _threads.start(4);
        spdlog::info("[app] Application server start at {} threads", n);
        _hub->start();
        _threads.join();
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

    boost::asio::io_context& application::get_context()
    {
        return _context;
    }
}
