project(rpc)

set(LIBRARIES
        Boost::boost
        Boost::context)

file(GLOB_RECURSE RPC_CPP "${PROJECT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE RPC_HPP "${PROJECT_SOURCE_DIR}/*.hpp")

add_library(${PROJECT_NAME} STATIC ${RPC_CPP} ${RPC_HPP})

target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBRARIES})
