cmake_minimum_required(VERSION 3.2)
include("cmake/HunterGate.cmake")
HunterGate(
    URL "https://github.com/cpp-pm/hunter/archive/v0.24.2.tar.gz"
    SHA1 "17fd3b9f0b8c271eac9b71e30a6aa1b9fecab299"
)

project(Football)

hunter_add_package(Boost COMPONENTS regex system filesystem)
hunter_add_package(RedisClient)

find_package(Boost CONFIG REQUIRED regex system filesystem)
find_package(RedisClient CONFIG REQUIRED)

include_directories("include")
include_directories("libs")
include_directories("3rd/spdlog/include")

set(PROJECT_MODULES core config)

add_subdirectory(libs)
add_subdirectory(football)