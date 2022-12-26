#pragma once
#include <api_types.hpp>
#include <cstdint>
#include <vector>
#include <optional>

namespace fb::objects
{
    class child;
    class team;
}

namespace fb::api 
{
    using childrens = std::vector<objects::child>;
    using teams = std::vector<objects::team>;
    using table = uint16_t;

    class api_storage
    {
    public:
        virtual ~api_storage() {}
        
        virtual std::string next_id() = 0;

        virtual void add(const objects::child& child) = 0;
        virtual std::optional<objects::child> get_child(object_id child_id) = 0;
        virtual std::optional<childrens> get_child() = 0;
        virtual size_t erase_child(object_id child_id) = 0;
        
        virtual void add(const objects::team& team) = 0;
        virtual std::optional<objects::team> get_team(object_id team_id) = 0;
        virtual std::optional<teams> get_team() = 0;
        virtual size_t erase_team(object_id team_id) = 0;
        
    };
}
