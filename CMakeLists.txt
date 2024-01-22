cmake_minimum_required (VERSION 3.13 FATAL_ERROR)

project ("glone")

add_executable(
    ${PROJECT_NAME}
    main.cpp
)

add_subdirectory(glfw)

target_include_directories(${PROJECT_NAME} PRIVATE "glfw/include")
target_link_libraries(${PROJECT_NAME} glfw)
