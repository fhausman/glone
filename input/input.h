#pragma once

#include <glm/glm.hpp>

struct GLFWwindow;

using GloneWindow = GLFWwindow;

class Input {

  public:
    static Input* get() {
        static Input instance;
        return &instance;
    }

    void setWindow(GloneWindow* inWindow) {
        window = inWindow;
    }

    const glm::vec2& getDirection() {
        return inputMembers.direction;
    }

    void pollInputEvents();

    bool exitRequested() const;

  private:
    Input() = default;

    GloneWindow* window;

    struct InputMembers {
        glm::vec2 direction;
        bool shouldExit;
    };
    InputMembers inputMembers;
};
