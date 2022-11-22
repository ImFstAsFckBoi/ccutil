cmake_minimum_required(VERSION 3.0.0)
project(tests)

file(GLOB SOURCE_FILES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ccutil pthread)

include(ParseAndAddCatchTests.cmake)
ParseAndAddCatchTests(${PROJECT_NAME})
