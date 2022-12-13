#include <api_application.hpp>
#include <config/settings.hpp>

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
    };
}
