cmake_minimum_required(VERSION 3.23)

project(StackProject C)

add_executable(${PROJECT_NAME} src/main.c src/stack.c)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)