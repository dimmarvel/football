#include <iostream>
#include <spdlog/spdlog.h>
#include "application.hpp"
#include <config/settings.hpp>

int main(int argc, const char** argv)
{
    try
    {
        fb::settings setting;
        setting.parse(argc, argv);

        fb::client::application app(setting);
        app.start();
    }
    catch(const std::exception& e)
    {
        spdlog::error("unhandled exception: {}", e.what());
        return 1; 
    }

    return 0;
}
