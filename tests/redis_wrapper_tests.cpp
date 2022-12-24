#include "mock.hpp"

using namespace tests;

TEST_F(mock_redis, get_write)
{
    _redis_wrap->write(0, {"test1", "test2"});
    _redis_wrap->write(0, std::pair<int, int>(1,2));

    EXPECT_EQ(_redis_wrap->get(0, {"test1"}), "test2");
    EXPECT_EQ(_redis_wrap->get(0, 1), "2");
}
