#include "storage.hpp"
#include <spdlog/spdlog.h>

namespace fb 
{
    storage::storage()
    {
        spdlog::info("[Storage] Storage created");
        //TODO: add child id init
    }

    void storage::add_child(objects::child& child)
    {
        child.id = _child_id++;
        _db.write(CHILDRENS_DB, {std::to_string(child.id), child.to_json()});
    }

    void storage::add_team(const objects::team& team)
    {
        _db.write(TEAM_DB, {"team", team.to_json()});
    }

}
