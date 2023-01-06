#include "settings.hpp"
#include <spdlog/spdlog.h>

namespace fb 
{
    settings::settings()
    {
        spdlog::info("[settings] Settings created");
    }
    
    void settings::parse(int argc, const char** argv)
    {
        if(argc > 1)
        {
            spdlog::info("[settings] Start with arg: {}", argv[1]);
        }
        else
        {
            spdlog::info("[settings] Start without args");
        }
    }
}
