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
        virtual void start() override;

    private:
        settings& _setting;

        std::shared_ptr<storage> _storage;
    };
}
