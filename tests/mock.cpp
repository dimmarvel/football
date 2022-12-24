#include "mock.hpp"
#include <storage/storage.hpp>

namespace tests
{
    mock_app::mock_app(fb::settings s)
    : _storage_real(std::make_shared<fb::api::api_storage>())
    {}
    
    std::shared_ptr<fb::api::api_storage> mock_app::get_storage()
    {
        return _storage_real;
    }
}
