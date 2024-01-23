cmake_minimum_required (VERSION 3.13 FATAL_ERROR)

project ("glone")

set(CMAKE_CXX_STANDARD 17)

add_executable(
    ${PROJECT_NAME}
    "main.cpp"
    "shader_compiler/shader_compiler.cpp"
)

add_subdirectory(glad)
add_subdirectory(glfw)

target_include_directories(${PROJECT_NAME} PRIVATE "glfw/include" "glad/include")
target_link_libraries(${PROJECT_NAME} glfw glad)

add_custom_target(copy_shaders ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/shaders ${CMAKE_BINARY_DIR}/shaders
    DEPENDS ${MY_TARGET}
)
