#pragma once
#include <api_storage.hpp>
#include <memory>

namespace fb::api 
{
    
    class api_application
    {
    public:
        virtual ~api_application() {}

        virtual std::shared_ptr<api::api_storage> get_storage() = 0;
    };
}
