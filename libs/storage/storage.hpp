#pragma once
#include <core/database/redis_wrap.hpp>
#include <api_storage.hpp>
#include "objects.hpp"

namespace fb 
{
    class storage : public api::api_storage
    {
    public:
        storage();
        ~storage() {}
        
        virtual void add_child(objects::child& child) override;
        virtual void add_team(const objects::team& team) override;

    private:
        fb::core::redis_wrap _db;

        uint32_t _child_id;
    };
}
