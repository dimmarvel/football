#pragma once

namespace api 
{
    class api_application
    {
    public:
        virtual ~api_application() {}
        virtual void start() = 0;
    };
}