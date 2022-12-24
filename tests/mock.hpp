#include <core/database/redis_wrap.hpp>
#include <api_storage.hpp>
#include <api_application.hpp>
#include <api_settings.hpp>
#include <config/settings.hpp>
#include <gtest/gtest.h>
#include <memory>

namespace tests
{
    class mock_redis : public testing::Test
    {
    public:
        fb::core::redis_wrap* _redis_wrap;
        
        void SetUp() { _redis_wrap = new fb::core::redis_wrap(); }
        void TearDown() { delete _redis_wrap; }
    };

    class mock_app : public fb::api::api_application
    {
    public:
        mock_app(fb::settings s = fb::settings());
        ~mock_app() override {}
    
        virtual std::shared_ptr<fb::api::api_storage> get_storage() override;
    
    private:
        fb::api::api_settings& _setting;

        std::shared_ptr<fb::api::api_storage> _storage_real;
    };

}
