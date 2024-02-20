#include "input.h"

#include "GLFW/glfw3.h"

void Input::pollInputEvents() {
    inputMembers = {};

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        inputMembers.shouldExit = true;

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        inputMembers.direction.x = -1.0f;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        inputMembers.direction.x = 1.0f;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        inputMembers.direction.y = 1.0f;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        inputMembers.direction.y = -1.0f;
}

bool Input::exitRequested() const {
    return inputMembers.shouldExit;
}
