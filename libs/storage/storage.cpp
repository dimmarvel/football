#include "storage.hpp"
#include <spdlog/spdlog.h>

namespace fb 
{
    storage::storage()
    {
        spdlog::info("[Storage] Storage created");
    }

    void storage::add_child(const objects::child& child)
    {
        _db.write({"children", child.to_json()});
    }

    void storage::add_team(const objects::team& team)
    {
        _db.write({"team", team.to_json()});
    }

}
