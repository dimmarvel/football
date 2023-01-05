project(database)

set(LIBRARIES 
        Boost::boost)

file(GLOB_RECURSE REDIS_CPP "${PROJECT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE REDIS_HPP "${PROJECT_SOURCE_DIR}/*.hpp")

add_library(${PROJECT_NAME} STATIC ${REDIS_CPP} ${REDIS_HPP})

target_link_libraries(${PROJECT_NAME} PUBLIC ${HIREDIS_LIB} -lpthread ${REDIS_PLUS_PLUS_LIB} -lpthread ${LIBRARIES})
