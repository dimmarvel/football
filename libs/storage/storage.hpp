#pragma once
#include <core/database/redis_wrap.hpp>
#include "objects.hpp"

namespace fb 
{
    class storage 
    {
    public:
        storage();
        ~storage() {}
        
        void add_child(const objects::child& child);
        void add_team(const objects::team& team);

    private:
        fb::core::redis_wrap _db;
    };
}
