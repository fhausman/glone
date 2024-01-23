#pragma once

#include <unordered_map>
#include <string>
#include <filesystem>

class ShaderCompiler
{
public:
    void compileShaders(std::filesystem::path& root);
    uint32_t getShader(const std::string& name) const;

    ShaderCompiler() = default;
    ~ShaderCompiler();
private:
    static constexpr uint32_t INVALID_SHADER = 0xFFFFFFFF;
    std::unordered_map<std::string, uint32_t> compiledShaders;

    uint32_t getShaderType(const std::string& extension) const;
};
