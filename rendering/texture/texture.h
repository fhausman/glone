#pragma once

#include <filesystem>
#include <glm/glm.hpp>

class Texture {
  public:
    Texture() = default;
    Texture(const std::string& filename);
    ~Texture();

    void bind() const;
    glm::vec2 getSize() const {
        return glm::vec2(width, height);
    }

  private:
    uint32_t id;

    int32_t width;
    int32_t height;
    int32_t channels;
};
