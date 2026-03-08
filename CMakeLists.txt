cmake_minimum_required(VERSION 3.31.0)

project(poor-choices-only VERSION 0.0.0)

add_compile_options(-Wall -Wpedantic -Wextra)

add_executable(
    ${PROJECT_NAME}
    ${CMAKE_SOURCE_DIR}/src/main.cpp
)