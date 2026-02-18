cmake_minimum_required(VERSION 3.23)

project(crank)

find_package(glfw3 REQUIRED)

add_library(glad STATIC src/glad/glad.c)
target_include_directories(glad PUBLIC include)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE glad glfw)
target_compile_definitions(${PROJECT_NAME} PRIVATE SHADER_DIR="${PROJECT_SOURCE_DIR}/shaders")
