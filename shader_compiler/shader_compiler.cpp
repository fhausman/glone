#include "shader_compiler.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <glad/glad.h>

void ShaderCompiler::compileShaders(std::filesystem::path& root)
{
    std::cout << "COMPILING SHADERS" << std::endl;
    std::cout << (std::filesystem::current_path() / root).string() << std::endl << std::endl;

    char logBuffer[512];
    for (const auto& entry : std::filesystem::recursive_directory_iterator(root))
    {
        if (entry.is_directory())
            continue;

        const auto& shaderPath = entry.path();
        const auto& filename = shaderPath.stem().string();
        assert(compiledShaders.find(filename) == compiledShaders.end() && "Shader name collision!");

        std::cout << shaderPath.string() << std::endl;
        std::ifstream shaderFile(shaderPath);
        std::string shaderSourceString((std::istreambuf_iterator<char>(shaderFile)), std::istreambuf_iterator<char>());

        const auto shaderType = getShaderType(shaderPath.extension().string());
        uint32_t shader = glCreateShader(shaderType);

        const char* shaderSource = shaderSourceString.c_str();
        glShaderSource(shader, 1, &shaderSource, NULL);
        glCompileShader(shader);
        
        int success = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 512, NULL, logBuffer);
            std::cout << logBuffer << std::endl;
            glDeleteShader(shader);
            continue;
        }
        else
        {
            std::cout << "SUCCESS" << std::endl;
        }

        compiledShaders[filename] = shader;

        std::cout << std::endl;
    }
}

uint32_t ShaderCompiler::getShader(const std::string& name) const
{
    if (compiledShaders.find(name) != compiledShaders.end())
    {
        return compiledShaders.at(name);
    }

    return INVALID_SHADER;
}

ShaderCompiler::~ShaderCompiler()
{
    for (auto& [name, shader] : compiledShaders)
    {
        glDeleteShader(shader);
    }
}

uint32_t ShaderCompiler::getShaderType(const std::string& extension) const
{
    if (extension.find("vs") != std::string::npos)
        return GL_VERTEX_SHADER;
    if (extension.find("fs") != std::string::npos)
        return GL_FRAGMENT_SHADER;

    return INVALID_SHADER;
}
