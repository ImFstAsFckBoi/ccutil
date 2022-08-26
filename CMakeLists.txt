cmake_minimum_required(VERSION 3.0.0)

project(ccutil VERSION 1.0.0 LANGUAGES CXX)

file(GLOB SOURCE 
  "src/**/*.c" "src/**/*.cc" "src/**/*.cpp" "src/**/*.cxx"
  "src/*.c" "src/*.cc" "src/*.cpp" "src/*.cxx"
  "include/**/*.h" "include/**/*.hh" "include/**/*.hpp" "include/**/*.tcc" "include/**/*.tpp"
  "include/*.h" "include/*.hh" "include/*.hpp" "include/*.tcc" "include/*.tpp"
)


add_library(${PROJECT_NAME} ${SOURCE})

#set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

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
  "include/ccutil/zip/"
  "include/ccutil/str_util/"
  "include/ccutil/sockstream/"
  "include/ccutil/progress/"
)
