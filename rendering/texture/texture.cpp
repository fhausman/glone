#include "texture.h"

#include "stb_image.h"
#include <glad/glad.h>

const std::filesystem::path textureFolder = "textures";

Texture::Texture(const std::string& filename) {
    auto path = textureFolder / filename;

    stbi_set_flip_vertically_on_load(true);
    auto data = stbi_load(path.string().c_str(), &width, &height, &channels, 0);
    if (data) {
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);

        int32_t format;
        if (channels == 4) {
            format = GL_RGBA;
        } else {
            format = GL_RGB;
        }

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    }
    stbi_image_free(data);
}

Texture::~Texture() {
}

void Texture::bind() const {
    glBindTexture(GL_TEXTURE_2D, id);
}
