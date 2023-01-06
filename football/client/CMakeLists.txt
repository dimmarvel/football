project(fbclient)

set(LIBRARIES 
        ${PROJECT_MODULES}
        Boost::boost
        Boost::context)

file(GLOB_RECURSE FBCLIENT_CPP "${PROJECT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE FBCLIENT_HPP "${PROJECT_SOURCE_DIR}/*.hpp")

add_executable(fbclient ${FBCLIENT_CPP})

target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBRARIES})
