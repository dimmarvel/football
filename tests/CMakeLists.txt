project(fbtests)

set(LIBRARIES 
        ${PROJECT_MODULES}
        Boost::boost
        GTest::gtest)

file(GLOB_RECURSE FBTESTS_CPP "${PROJECT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE FBTESTS_HPP "${PROJECT_SOURCE_DIR}/*.hpp")

add_executable(fbtests ${FBTESTS_CPP})

target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBRARIES})
