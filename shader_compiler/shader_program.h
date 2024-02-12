#pragma once

#include <cstdint>

struct ShaderProgram {
    ShaderProgram(uint32_t vs, uint32_t fs);
    ShaderProgram(const ShaderProgram&) = default;

    void useProgram();
    uint32_t id() {
        return program;
    };

  private:
    uint32_t program;
};
