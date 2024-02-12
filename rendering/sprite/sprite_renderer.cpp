#include "sprite_renderer.h"

#include <vector>
#include <glad/glad.h>
#include "glm/gtc/type_ptr.hpp"
#include "camera/camera.h"

// clang-format off
const std::vector quad = { 
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 
    
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };
// clang-format on

void SpriteRenderer::initRenderData() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, quad.size(), quad.data(), GL_STATIC_DRAW);

    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void SpriteRenderer::render(const Sprite& sprite) {
    shader.useProgram();

    glUniform1i(glGetUniformLocation(shader.id(), "image"), 0);
    glUniformMatrix4fv(glGetUniformLocation(shader.id(), "projection"), 1, false, glm::value_ptr(Camera::get()->projection()));

    auto model = sprite.getModel();
    glUniformMatrix4fv(glGetUniformLocation(shader.id(), "model"), 1, false, glm::value_ptr(model));
    glUniform3f(glGetUniformLocation(shader.id(), "color"), 1.0f, 1.0f, 1.0f);

    glActiveTexture(GL_TEXTURE0);
    sprite.bindTexture();

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
