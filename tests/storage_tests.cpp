#include <mock.hpp>
#include <database/defines.hpp>
#include <storage/objects/objects.hpp>

using namespace tests;

TEST(storage, child)
{
    mock_app app;
    
    fb::objects::child ch;
    fb::objects::child ch2;
    
    ch.id = app.get_storage()->next_id();
    ch.name = "qweasd";
    ch2.id = app.get_storage()->next_id();
    ch2.name = "qweasd2";

    app.get_storage()->add(ch);
    EXPECT_EQ(app.get_storage()->get_child(ch.id).value().name, ch.name);
    
    app.get_storage()->add(ch2);
    auto all_ch = app.get_storage()->get_child();
    EXPECT_EQ(all_ch.value().size(), 2);
    
    EXPECT_EQ(app.get_storage()->erase_child(ch.id), 1);
    EXPECT_EQ(app.get_storage()->erase_child(ch2.id), 1);

    bool is_created = false;
    if(app.get_storage()->get_child(ch.id)) // try get child who doesnt exist
        is_created = true;
    
    EXPECT_EQ(is_created, false);
}

TEST(storage, team)
{
    mock_app app;
    
    fb::objects::team t;
    fb::objects::team t2;
    t.id = app.get_storage()->next_id();
    t.name = "qweasd";
    t2.id = app.get_storage()->next_id();
    t2.name = "qweasd2";

    app.get_storage()->add(t);
    EXPECT_EQ(app.get_storage()->get_team(t.name).value().name, t.name);
    
    app.get_storage()->add(t2);
    auto all_team = app.get_storage()->get_team();
    EXPECT_EQ(all_team.value().size(), 2);

    EXPECT_EQ(app.get_storage()->erase_team(t.name), 1);
    EXPECT_EQ(app.get_storage()->erase_team(t2.name), 1);

    bool is_created = false;
    if(app.get_storage()->get_team(t.id)) // try get team who doesnt exist
        is_created = true;
    
    EXPECT_EQ(is_created, false);
}