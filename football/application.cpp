#include "application.hpp"
#include <iostream>
#include <spdlog/spdlog.h>

namespace fb
{
    application::application(settings& s)
    :   _setting(s)
    {
        spdlog::info("[APP] Application created");
    }

    void application::start()
    {
        spdlog::info("[APP] Application start");
    }
}