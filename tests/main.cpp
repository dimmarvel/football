#include <iostream>
#include <spdlog/spdlog.h>
#include <gtest/gtest.h>

int main(int argc, char** argv)
{
    try
    {
        ::testing::InitGoogleTest(&argc, argv);
    }
    catch(const std::exception& e)
    {
        spdlog::error("unhandled exception: {}", e.what());
        return 1; 
    }

    return RUN_ALL_TESTS();
}
