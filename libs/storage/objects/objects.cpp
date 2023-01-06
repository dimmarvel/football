#include "objects.hpp"

namespace fb::objects
{

    object::object(const object& obj)
    :
    id(obj.id)
    {}

    child::child(std::string name, std::string surname, std::string patronymic, std::string pos,
                api::mheight height, api::mweight weight, best_foot b_foot, std::string notes,
                const skills& skill)
    :   object(),
    name(name), surname(surname), patronymic(patronymic), position(pos), height(height), 
    weight(weight), b_foot(b_foot), notes(notes), skill(skill)
    {}

    team::team(std::string name, const std::vector<child>& players)
    :   object(),
    name(name), players(std::move(players))
    {}
}