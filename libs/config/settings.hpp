#pragma once

#include <api_settings.hpp>

namespace fb 
{
    class settings : api::api_settings
    {
    public:
        settings();
        ~settings() override {}
        virtual void parse(int argc, const char** argv) override;
    };
}
