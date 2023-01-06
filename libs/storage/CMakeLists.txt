project(storage)

set(LIBRARIES database)

file(GLOB_RECURSE STORAGE_CPP "${PROJECT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE STORAGE_HPP "${PROJECT_SOURCE_DIR}/*.hpp")

add_library(${PROJECT_NAME} STATIC ${STORAGE_CPP} ${STORAGE_HPP})

target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBRARIES})
