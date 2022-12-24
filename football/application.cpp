#include "application.hpp"
#include <iostream>
#include <spdlog/spdlog.h>

namespace fb
{
    application::application(settings& s)
    :   
    _setting(s),
    _storage(std::make_shared<storage>())
    {
        spdlog::info("[APP] Application created");
    }

    void application::start()
    {
        spdlog::info("[APP] Application start");
    }

    std::shared_ptr<api::api_storage> application::get_storage()
    {
        return _storage;
    }
}
