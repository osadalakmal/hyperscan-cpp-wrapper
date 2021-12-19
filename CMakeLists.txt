cmake_minimum_required(VERSION 3.16.3)

project(hyperscan-cpp)

add_library(hs-cpp STATIC ${CMAKE_CURRENT_SOURCE_DIR}/hs_wrapper.cpp)
add_executable ( hs-cpp.t.tsk main.t.cpp )
find_package(Threads REQUIRED)
find_package(GTest REQUIRED)
target_link_libraries(hs-cpp.t.tsk hs-cpp ${Threads_LIBRARIES} GTest::GTest hs)
target_include_directories(hs-cpp.t.tsk PUBLIC ${Threads_INCLUDE_DIRS} ${GTest_INCLUDE_DIRS})
