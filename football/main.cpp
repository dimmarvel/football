#include <iostream>
#include <spdlog/spdlog.h>
#include "application.hpp"
#include <config/settings.hpp>
#include <core/redis_wrap.hpp>

int main(int argc, const char** argv)
{
    try
    {
        fb::core::redis_wrap rw;
        rw.write({"qwe", "asd1"});
        spdlog::info("GET - {}", rw.get({"qwe"}));

        fb::settings setting;
        setting.parse(argc, argv);

        fb::application app(setting);
        app.start();
    }
    catch(const std::exception& e)
    {
        spdlog::error("unhandled exception: {}", e.what());
        return 1; 
    }

    return 0;
}
