#include "storage.hpp"
#include <string>
#include <spdlog/spdlog.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>

namespace fb 
{
    storage::storage()
    {
        spdlog::info("[Storage] Storage created");
    }

    std::string storage::next_id()
    {
        boost::uuids::uuid tag = boost::uuids::random_generator()();
        std::string str = boost::lexical_cast<std::string>(tag);
        return str;
    }

    void storage::add(const objects::child& child)
    {
        _db.write(CHILDRENS_DB, {child.id, child.to_json()});
    }

    std::optional<objects::child> storage::get_child(api::object_id child_id)
    {
        std::string ch = _db.get(CHILDRENS_DB, child_id);
        if(ch.empty()) return {};
        return fb::core::from_json<objects::child>(ch);
    }

    std::optional<api::childrens> storage::get_child()
    {
        std::unordered_set<std::string> keys = _db.get_keys(CHILDRENS_DB);
        if(keys.empty()) return {};
        
        api::childrens childrens;
        for(const auto& it : keys)
            childrens.emplace_back(fb::core::from_json<objects::child>(_db.get(CHILDRENS_DB, it)));
        return childrens;
    }

    size_t storage::erase_child(api::object_id child_id)
    {
        return _db.erase(CHILDRENS_DB, child_id);
    }

    void storage::add(const objects::team& team)
    {
        _db.write(TEAM_DB, {team.name, team.to_json()});
    }

    std::optional<objects::team> storage::get_team(api::object_id team_id)
    {
        std::string t = _db.get(TEAM_DB, team_id);
        if(t.empty()) return {};
        return fb::core::from_json<objects::team>(_db.get(TEAM_DB, team_id));
    }

    std::optional<api::teams> storage::get_team()
    {
        std::unordered_set<std::string> keys = _db.get_keys(TEAM_DB);
        if(keys.empty()) return {};
        
        api::teams teams;
        for(const auto& it : keys)
            teams.emplace_back(fb::core::from_json<objects::team>(_db.get(TEAM_DB, it)));
        return teams;
    }

    size_t storage::erase_team(api::object_id team_id)
    {
        return _db.erase(TEAM_DB, team_id);
    }


}
