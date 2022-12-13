#include "settings.hpp"
#include <spdlog/spdlog.h>

namespace fb 
{
    settings::settings()
    {
        spdlog::info("[Settings] Settings created");
    }
    
    void settings::parse(int argc, const char** argv)
    {
        if(argc > 1)
        {
            spdlog::info("[Settings] Start with arg: {}", argv[1]);
        }
        else
        {
            spdlog::info("[Settings] Start without args");
        }
    }
}
