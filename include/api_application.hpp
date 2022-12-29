#pragma once
#include <api_storage.hpp>
#include <memory>
#include <boost/asio/io_context.hpp> 

namespace fb::api 
{
    
    class api_application
    {
    public:
        virtual ~api_application() {}

        virtual std::shared_ptr<api::api_storage> get_storage() = 0;
        virtual boost::asio::io_context& get_context() = 0;
    };
}
