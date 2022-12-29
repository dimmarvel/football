#include <mock.hpp>
#include <storage/storage.hpp>
#include <server/server.hpp>
namespace tests
{
    mock_app::mock_app(fb::settings s)
    : 
    _setting(s),
    _storage_real(std::make_shared<fb::storage>()),
    _server_real(std::make_shared<fb::server>(*this))
    {}
    
    std::shared_ptr<fb::api::api_storage> mock_app::get_storage()
    {
        return _storage_real;
    }

    boost::asio::io_context& mock_app::get_context()
    {
        return _context;
    }
}
