#include <core/redis_wrap.hpp>
#include <gtest/gtest.h>
#include <memory>

class mock_redis : public testing::Test
{
public:
    fb::core::redis_wrap* _redis_wrap;
    
    void SetUp() { _redis_wrap = new fb::core::redis_wrap(); }
    void TearDown() { delete _redis_wrap; }
};

TEST_F(mock_redis, get_write)
{
    _redis_wrap->write({"test1", "test2"});
    _redis_wrap->write(std::pair<int, int>(1,2));

    EXPECT_EQ(_redis_wrap->get({"test1"}), "test2");
    EXPECT_EQ(_redis_wrap->get(1), "2");
}
