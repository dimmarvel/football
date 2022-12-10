#include <api_application.hpp>

namespace fb
{
    class application : public api::api_application
    {
    public:
        application();
        ~application() override {}
        virtual void start() override;
    };
}