#include "shader_program.h"

#include <glad/glad.h>
#include <iostream>

ShaderProgram::ShaderProgram(uint32_t vertexShader, uint32_t fragmentShader) {
    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    int32_t success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, NULL, infoLog);

        std::cout << infoLog << std::endl;
    }
}

void ShaderProgram::useProgram() {
    glUseProgram(program);
}
