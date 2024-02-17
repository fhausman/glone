#include "sprite.h"

#include "sprite_renderer.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

Sprite::Sprite(const std::string& name) : texture(name) {
    size = texture.getSize();
}

glm::mat4 Sprite::getModel() const {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));

    model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-pivot.x * size.x, -pivot.y * size.y, 0.0f));

    model = glm::scale(model, glm::vec3(size, 1.0f));

    return model;
}
