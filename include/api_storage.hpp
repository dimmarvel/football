#pragma once
#include <cstdint>
namespace fb::objects
{
    class child;
    class team;
}

namespace fb::api 
{
    using table = uint16_t;

    class api_storage
    {
    public:
        virtual ~api_storage() {}
        virtual void add_child(objects::child& child) = 0;
        virtual void add_team(const objects::team& team) = 0;
    };
}
