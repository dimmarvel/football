#include <mock.hpp>
#include <storage/storage.hpp>
#include <server/server.hpp>
namespace tests
{
    mock_app::mock_app(fb::settings s)
    : 
    _setting(s),
    _context(),
    _storage_real(std::make_shared<fb::storage>()),
    _server_real(std::make_shared<fb::tcp_server>(*this))
    {}
    
    void mock_app::start()
    {
        
    }
    
    std::shared_ptr<fb::api::api_storage> mock_app::get_storage()
    {
        return _storage_real;
    }

    boost::asio::any_io_executor mock_app::get_context()
    {
        return _context.get_executor();
    }
}
