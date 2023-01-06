#pragma once
#include <api_storage.hpp>
#include <memory>

namespace boost::asio
{
    class any_io_executor;
}

namespace fb::api 
{
    
    class api_application
    {
    public:
        virtual ~api_application() {}

        virtual void start() = 0;
        virtual boost::asio::any_io_executor get_context() = 0;
        virtual std::shared_ptr<api::api_storage> get_storage() = 0;
    };
}
