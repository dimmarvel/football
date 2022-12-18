project(fbserver)

set(LIBRARIES 
        ${PROJECT_MODULES})

file(GLOB_RECURSE FBSERVER_CPP "${PROJECT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE FBSERVER_HPP "${PROJECT_SOURCE_DIR}/*.hpp")

add_executable(fbserver ${FBSERVER_CPP})

target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBRARIES})
