#include <core/database/redis_wrap.hpp>
#include <api_storage.hpp>
#include <api_application.hpp>
#include <api_settings.hpp>
#include <api_server.hpp>

#include <config/settings.hpp>
#include <gtest/gtest.h>
#include <memory>

namespace tests
{
    class mock_redis : public fb::core::redis_wrap
    {
    public:
        
    };

    class mock_app : public fb::api::api_application
    {
    public:
        mock_app(fb::settings s = fb::settings());
        ~mock_app() override {}
    
        virtual std::shared_ptr<fb::api::api_storage> get_storage() override;
        virtual boost::asio::io_context& get_context() override;

    private:
        fb::settings& _setting;
        boost::asio::io_context _context;

        std::shared_ptr<fb::api::api_storage>   _storage_real;
        std::shared_ptr<fb::api::api_server>    _server_real;
    };

}
