#pragma once
#include <cstdint>

struct ShaderProgram {
    ShaderProgram(uint32_t vs, uint32_t fs);

    void useProgram();

  private:
    uint32_t program;
};
