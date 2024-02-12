#pragma once

#include "shader_program.h"
#include "sprite.h"

class SpriteRenderer {

  public:
    SpriteRenderer(const ShaderProgram& shaderProgram) : shader(shaderProgram) {
    }

    void initRenderData();
    void render(const Sprite& sprite);

  private:
    ShaderProgram shader;

    uint32_t VAO;
    uint32_t VBO;
};
