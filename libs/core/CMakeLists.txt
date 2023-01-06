project(core)

set(LIBRARIES)

file(GLOB_RECURSE CORE_CPP "${PROJECT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE CORE_HPP "${PROJECT_SOURCE_DIR}/*.hpp")

add_library(${PROJECT_NAME} STATIC ${CORE_CPP} ${CORE_HPP})

target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBRARIES})
