#include <api_application.hpp>
#include <config/settings.hpp>
#include <storage/storage.hpp>

namespace fb
{
    class application : public api::api_application
    {
    public:
        application(settings& s);
        ~application() override {}

    public:
        virtual std::shared_ptr<api::api_storage> get_storage() override;
        
        void start();

    private:
        settings& _setting;

        std::shared_ptr<api::api_storage> _storage;
    };
}
