project(config)

set(LIBRARIES Boost::boost)
file(GLOB_RECURSE CONFIG_CPP "${PROJECT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE CONFIG_HPP "${PROJECT_SOURCE_DIR}/*.hpp")

add_library(${PROJECT_NAME} STATIC ${CONFIG_CPP} ${CONFIG_HPP})

target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBRARIES})