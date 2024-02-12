#pragma once

#include <glm/glm.hpp>

class Camera {
  public:
    static Camera* get() {
        static Camera instance;
        return &instance;
    }

    void setPosition(float x, float y);
    void setSize(float width, float height);

    glm::mat4 projection();

  private:
    Camera() = default;

    float pos_x = 0.0f;
    float pos_y = 0.0f;

    float width = 0.0f;
    float height = 0.0f;
};
