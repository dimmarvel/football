#pragma once
#include <core/database/redis_wrap.hpp>
#include <api_storage.hpp>
#include "objects/objects.hpp"

namespace fb 
{

    class storage : public api::api_storage
    {
    public:
        storage();
        ~storage() {}

        virtual std::string next_id() override;

        virtual void add(const objects::child& child) override;
        virtual std::optional<objects::child> get_child(api::object_id child_id) override;
        virtual std::optional<api::childrens> get_child() override;
        virtual size_t erase_child(api::object_id child_id) override;

        virtual void add(const objects::team& team) override;
        virtual std::optional<objects::team> get_team(api::object_id team_id) override;
        virtual std::optional<api::teams> get_team() override;
        virtual size_t erase_team(api::object_id team_id) override;

    private:
        fb::core::redis_wrap _db;
    };
}
