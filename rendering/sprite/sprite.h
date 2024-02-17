#pragma once

#include "texture/texture.h"

#include <glm/glm.hpp>

class Sprite {
  public:
    Sprite(const std::string& name);

    glm::mat4 getModel() const;

    const glm::vec4& getColor() const {
        return color;
    }
    const glm::vec2& getPosition() const {
        return position;
    }
    const glm::vec2& getSize() const {
        return size;
    }
    float getRotation() const {
        return rotation;
    }
    void bindTexture() const {
        texture.bind();
    }

  private:
    Texture texture;
    glm::vec4 color = glm::vec4(1.0, 1.0f, 1.0f, 1.0f);

    glm::vec2 position = glm::vec2(0.0f, 0.0f);
    glm::vec2 size = glm::vec2(0.0f, 0.0f);
    glm::vec2 pivot = glm::vec2(0.5f, 0.5f);
    float rotation = 0.0f;
};
