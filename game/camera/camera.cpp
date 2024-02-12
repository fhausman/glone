#include "camera.h"

#include "glm/ext/matrix_clip_space.hpp"

void Camera::setPosition(float x, float y) {
    pos_x = x;
    pos_y = y;
}

void Camera::setSize(float width, float height) {
    this->width = width;
    this->height = height;
}

glm::mat4 Camera::projection() {
    return glm::ortho(pos_x - width / 2.0f, pos_x + width / 2.0f, pos_y - height / 2.0f, pos_y + height / 2.0f, -1.0f, 1.0f);
}
