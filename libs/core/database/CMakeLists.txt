project(database)

set(LIBRARIES 
        Boost::boost
        RedisClient::RedisClient)

file(GLOB_RECURSE REDIS_CPP "${PROJECT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE REDIS_HPP "${PROJECT_SOURCE_DIR}/*.hpp")

add_library(${PROJECT_NAME} STATIC ${REDIS_CPP} ${REDIS_HPP})

target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBRARIES})
