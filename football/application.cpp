#include "application.hpp"
#include <iostream>
#include <spdlog/spdlog.h>

namespace fb
{
    application::application()
    {
        spdlog::info("Application created");
    }

    void application::start()
    {
        spdlog::info("Application start");
    }
}