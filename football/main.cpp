#include <iostream>
#include <spdlog/spdlog.h>
#include "application.hpp"
#include <config/settings.hpp>

int main(int argc, const char** argv)
{
    fb::settings setting;
    setting.parse(argc, argv);


    fb::application app(setting);
    app.start();
    spdlog::info("Hello world");
    return 0;
}