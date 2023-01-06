#pragma once
#include <api_objects.hpp>
#include <api_types.hpp>
#include <string>
#include <vector>
#include <core/serialize.hpp>

namespace fb::objects
{
    class object
    {
    public:
        object() = default;
        object(const object& obj);
        virtual ~object() {}

    public:
        std::string id;
    };

    class skills 
    {
    public:
        api::rating technic = 0;
        api::rating protection = 0;
        api::rating speed = 0;
        api::rating endurance = 0;
        api::rating hit = 0;
        api::rating pass = 0;
        api::rating physic = 0;
        api::rating game_thinking = 0;
        api::rating sociability = 0;
        api::rating learnability = 0;
        
        double average_rating;

    SERIALIZABLE_OBJ(   technic, protection, speed, endurance, hit,
                        pass, physic,game_thinking, sociability, learnability);
    CONVERTION_IMPL();
    };

    class child : public object
    {
    public:
        std::string name;
        std::string surname;
        std::string patronymic;

        std::string position;

        api::mheight height = 0;
        api::mweight weight = 0;

        best_foot b_foot;

        std::string notes;

        skills  skill;
        std::vector<std::string> team_names;

    public:
        child() = default;
        child(  std::string name, std::string surname, std::string patronymic, std::string pos,
                api::mheight height, api::mweight weight, best_foot b_foot, std::string notes,
                const skills& skill);

    SERIALIZABLE_OBJ(   id, name, surname, patronymic, position, height,
                        weight, b_foot, notes, skill, team_names);
    CONVERTION_IMPL();
    };

    class team : public object
    {
    public:
        std::string name;
        std::vector<child> players;

    public:
        team() = default;
        team(std::string name, const std::vector<child>& players);

    SERIALIZABLE_OBJ(id, name, players);
    CONVERTION_IMPL();
    };


}