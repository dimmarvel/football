project(server)

set(LIBRARIES
        Boost::boost
        Boost::context)

file(GLOB_RECURSE SERVER_CPP "${PROJECT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE SERVER_HPP "${PROJECT_SOURCE_DIR}/*.hpp")

add_library(${PROJECT_NAME} STATIC ${SERVER_CPP} ${SERVER_HPP})

target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBRARIES})
