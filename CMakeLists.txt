cmake_minimum_required(VERSION 3.23)

project(crank)

find_package(glfw3 REQUIRED)

add_library(glad STATIC src/glad/glad.c)
target_include_directories(glad PUBLIC include)

file(GLOB CRANK_SRC "src/crank/*.cpp")
add_library(crankengine STATIC ${CRANK_SRC})
target_include_directories(crankengine PUBLIC include)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE glad glfw crankengine)
target_compile_definitions(${PROJECT_NAME} PRIVATE SHADER_DIR="${PROJECT_SOURCE_DIR}/shaders")
