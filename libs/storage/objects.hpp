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
        uint32_t id;
    };

    class skills 
    {
    public:
        api::rating technic;
        api::rating protection;
        api::rating speed;
        api::rating endurance;
        api::rating hit;
        api::rating pass;
        api::rating physic;
        api::rating game_thinking;
        api::rating sociability;
        api::rating learnability;
        
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

        api::mheight height;
        api::mweight weight;

        best_foot b_foot;

        std::string notes;

        skills  skill;

        std::vector<std::string> team_names;

    SERIALIZABLE_OBJ(   name, surname, patronymic, position, height,
                        weight, b_foot, notes, skill, team_names);
    CONVERTION_IMPL();
    };

    class team : public object
    {
    public:
        std::string name;
        std::vector<child> players;

    SERIALIZABLE_OBJ(name, players);
    CONVERTION_IMPL();
    };


}