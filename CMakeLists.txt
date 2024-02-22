cmake_minimum_required (VERSION 3.13 FATAL_ERROR)

project ("glone")

set(CMAKE_CXX_STANDARD 17)

add_compile_definitions("GLM_ENABLE_EXPERIMENTAL" "STB_IMAGE_IMPLEMENTATION")

add_executable(
    ${PROJECT_NAME}
    "main.cpp"
    "game/camera/camera.cpp"
    "input/input.cpp"
    "rendering/texture/texture.cpp"
    "rendering/texture/texture.h"
    "rendering/sprite/sprite.cpp"
    "rendering/sprite/sprite.h"
    "rendering/sprite/sprite_renderer.cpp"
    "rendering/sprite/sprite_renderer.h"
    "shader_compiler/shader_compiler.cpp"
    "shader_compiler/shader_compiler.h"
    "shader_compiler/shader_program.cpp"
    "shader_compiler/shader_program.h"
    "stb/stb_image.h"
)

add_subdirectory(glad)
add_subdirectory(glfw)
add_subdirectory(glm)

target_include_directories(${PROJECT_NAME} PRIVATE "glfw/include" "glad/include" "glm" "shader_compiler" "rendering" "game" "stb" "input")
target_link_libraries(${PROJECT_NAME} glfw glad glm)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(RESOURCE_DIR ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})
else()
    set(RESOURCE_DIR ${CMAKE_BINARY_DIR})
endif()

add_custom_target(copy_shaders ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/shaders ${RESOURCE_DIR}/shaders
)

add_custom_target(copy_textures ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/textures ${RESOURCE_DIR}/textures
)

add_dependencies(${PROJECT_NAME} copy_shaders copy_textures)
