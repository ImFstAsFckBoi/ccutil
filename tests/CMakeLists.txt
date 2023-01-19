cmake_minimum_required(VERSION 3.0.0)
project(tests)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/modules")

file(GLOB SOURCE_FILES "src/*.cpp")
find_package(Catch2 3 REQUIRED)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ccutil pthread Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(${PROJECT_NAME})
