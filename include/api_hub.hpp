#pragma once
#include <api_types.hpp>
#include <api_connection.hpp>

namespace fb::api 
{
    class api_hub
    {
    public:
        virtual ~api_hub() {}
        virtual void start() = 0;

        virtual void subscribe_on_server() = 0;
        virtual void on_new_connect(api::connect_ptr con) = 0;
    };
}