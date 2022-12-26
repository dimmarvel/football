cmake_minimum_required(VERSION 3.2)
include("cmake/HunterGate.cmake")
HunterGate(
    URL "https://github.com/cpp-pm/hunter/archive/v0.24.2.tar.gz"
    SHA1 "17fd3b9f0b8c271eac9b71e30a6aa1b9fecab299"
)

project(Football)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

hunter_add_package(Boost COMPONENTS regex system filesystem)
hunter_add_package(RedisClient)
hunter_add_package(GTest)

find_package(Threads REQUIRED)
find_package(Boost CONFIG REQUIRED regex system filesystem)
find_package(GTest CONFIG REQUIRED)

include_directories("include")
include_directories("libs")
include_directories("tests")
include_directories("3rd/spdlog/include")
include_directories("3rd/yas/include")
include_directories("3rd/hiredis")
include_directories("3rd/redis-plus-plus")
include_directories(${HIREDIS_HEADER})
include_directories(${REDIS_PLUS_PLUS_HEADER})

message("HIREDIS_HEADER - " ${HIREDIS_HEADER})
message("REDIS_PLUS_PLUS_HEADER - " ${REDIS_PLUS_PLUS_HEADER})

find_library(HIREDIS_LIB hiredis)
message("HIREDIS_LIB - " ${HIREDIS_LIB})
find_library(REDIS_PLUS_PLUS_LIB redis++)
message("REDIS_PLUS_PLUS_LIB - " ${REDIS_PLUS_PLUS_LIB})

set(PROJECT_MODULES database config storage)

add_subdirectory(3rd)
add_subdirectory(libs)
add_subdirectory(football)
add_subdirectory(tests)
