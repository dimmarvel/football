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
        _storage->add_child({});
        _storage->add_team({});
    }

    void application::start()
    {
        spdlog::info("[APP] Application start");
    }
}
