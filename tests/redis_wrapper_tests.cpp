#include <mock.hpp>
#include <iostream>

using namespace tests;

TEST(redis_wrapper, get_write)
{
    mock_redis _redis_wrap;
    _redis_wrap.write(0, {"test1", "test2"});
    _redis_wrap.write(0, std::pair<int, int>(1337,2));
    _redis_wrap.write(1, {"test2", "test2"});
    auto keys = _redis_wrap.get_keys(1);

    EXPECT_EQ(_redis_wrap.get(0, {"test1"}), "test2");
    EXPECT_EQ(_redis_wrap.get(0, 1337), "2");
    EXPECT_EQ(_redis_wrap.get(1, "test2"), "test2");
    EXPECT_EQ(keys.size(), 1);
    EXPECT_EQ(*keys.find("test2"), "test2");

    EXPECT_EQ(_redis_wrap.erase(1, "test2"), 1);
    EXPECT_EQ(_redis_wrap.erase(0, "test1"), 1);
    EXPECT_EQ(_redis_wrap.erase(0, std::to_string(1337)), 1);
}
