#include <storage/objects/objects.hpp>
#include <database/defines.hpp>
#include <mock.hpp>

TEST(objects, child)
{
    fb::objects::child ch;
    ch.name = "name";
    ch.surname = "surname";
    ch.patronymic = "patronymic";
    ch.position = "position";
    ch.height = 190;
    ch.weight = 90;
    ch.b_foot = fb::objects::best_foot::right;
    ch.notes = "best player";
    ch.skill.technic = 10;
    ch.skill.protection = 10;
    ch.skill.speed = 10;
    ch.skill.endurance = 10; 
    ch.skill.hit = 10;
    ch.skill.pass = 10;
    ch.skill.physic = 10;
    ch.skill.game_thinking = 10;
    ch.skill.sociability = 10;
    ch.skill.learnability = 10;
    ch.skill.average_rating = 10;
    ch.team_names.push_back("team1");
    ch.team_names.push_back("team2");

    std::string child = ch.to_json();
    fb::objects::child ch2 = fb::core::from_json<fb::objects::child>(child);
    EXPECT_EQ(ch2.to_json(), child);
}

TEST(objects, team)
{
    fb::objects::team team;
    fb::objects::child ch;

    team.name = "BESTTEAM";

    team.players.push_back(ch);
    team.players.push_back(ch);
    team.players.push_back(ch);

    std::string team_json = team.to_json();
    fb::objects::team team2 = fb::core::from_json<fb::objects::team>(team_json);

    EXPECT_EQ(team2.to_json(), team_json);
}