#pragma once

namespace api 
{
    class api_settings
    {
    public:
        virtual ~api_settings() {}
        virtual void parse(int argc, const char** argv) = 0;
    };
}
