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
        api::rating_t technic = 0;
        api::rating_t protection = 0;
        api::rating_t speed = 0;
        api::rating_t endurance = 0;
        api::rating_t hit = 0;
        api::rating_t pass = 0;
        api::rating_t physic = 0;
        api::rating_t game_thinking = 0;
        api::rating_t sociability = 0;
        api::rating_t learnability = 0;
        
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

        api::mheight_t height = 0;
        api::mweight_t weight = 0;

        best_foot b_foot;

        std::string notes;

        skills  skill;
        std::vector<std::string> team_names;

    public:
        child() = default;
        child(  std::string name, std::string surname, std::string patronymic, std::string pos,
                api::mheight_t height, api::mweight_t weight, best_foot b_foot, std::string notes,
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