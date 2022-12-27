#include <api_application.hpp>
#include <config/settings.hpp>
#include <storage/storage.hpp>
#include <server/server.hpp>

namespace fb
{
    class application : public api::api_application
    {
    public:
        application(settings& s);
        ~application() override {}

    public:
        virtual std::shared_ptr<api::api_storage> get_storage() override;
        virtual boost::asio::io_context& get_context() override;
        
        void start();
        void stop();

    private:
        settings& _setting;
        boost::asio::io_context _context;

        std::shared_ptr<api::api_storage>   _storage;
        std::shared_ptr<api::api_server>    _server;
    };
}
