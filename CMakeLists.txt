cmake_minimum_required(VERSION 3.0.0)

project(ccutil VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCE 
  "src/**/*.c" "src/**/*.cc" "src/**/*.cpp" "src/**/*.cxx"
  "src/*.c" "src/*.cc" "src/*.cpp" "src/*.cxx"
  "include/**/*.h" "include/**/*.hh" "include/**/*.hpp" "include/**/*.tcc" "include/**/*.tpp"
  "include/*.h" "include/*.hh" "include/*.hpp" "include/*.tcc" "include/*.tpp"
)

add_library(${PROJECT_NAME} ${SOURCE})



if (CMAKE_COMPILER_IS_GNUCXX)
  target_compile_options(${PROJECT_NAME} PRIVATE 
    -Wall
    -Wextra
    -pedantic
    -Weffc++
    -Woverloaded-virtual 
    -fmax-errors=3
    -fdiagnostics-color
  )
endif()

target_include_directories(${PROJECT_NAME} INTERFACE
  "include/"
)

target_include_directories(${PROJECT_NAME} PRIVATE
  "include/ccutil/"
  "include/ccutil/io/"
  "include/ccutil/zip/"
  "include/ccutil/str/"
  "include/ccutil/progress/"
  "include/ccutil/sockstream/"
)

if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
  message(STATUS "Debug enabled, adding tests")
  enable_testing()
  add_subdirectory(tests/)

  file(GLOB mainfile main.cpp)
  
  if ("${mainfile}" STREQUAL "")
    message(STATUS "No main.cpp test file")
  else()
    message(STATUS "main.cpp test file found")
    add_executable(main main.cpp)
    target_link_libraries(main ccutil)
  endif()
endif()
