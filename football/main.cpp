#include <iostream>
#include <spdlog/spdlog.h>
#include "application.hpp"

int main()
{
    fb::application app;
    app.start();
    spdlog::info("Hello world");
    return 0;
}