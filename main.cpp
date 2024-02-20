#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "input/input.h"
#include "camera/camera.h"
#include "sprite/sprite.h"
#include "sprite/sprite_renderer.h"
#include "texture/texture.h"
#include "shader_compiler/shader_compiler.h"
#include "shader_compiler/shader_program.h"

struct GloneSettings {
    std::string name;
    uint32_t width;
    uint32_t height;
    std::string version;

    int32_t getMajorVersion() {
        auto dotPos = version.find('.');
        auto majorVer = std::stoi(version.substr(0, dotPos));
        return majorVer;
    }

    int32_t getMinorVersion() {
        auto dotPos = version.find('.');
        auto minorVer = std::stoi(version.substr(dotPos + 1));
        return minorVer;
    }
};

std::vector<float> vertices = {
    // positions        // colors
    0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
    0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f  // top
};

std::vector<uint32_t> indices = {
    // note that we start from 0!
    0, 1, 3, // first triangle
    // 1, 2, 3  // second triangle
};

// std::vector<float> spriteIndices = {
//     //position  //UVs
//     0.0f, 0.0f, 0.0f, 1.0f,
//     0.0f, 1.0f, 0.0f, 0.0f,
// };

float pixelsPerUnit = 32.0f;

int main(int argc, char* argv[]) {
    auto engineSettings = GloneSettings{ "Glone Engine", 1920, 1080, "3.3" };

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, engineSettings.getMajorVersion());
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, engineSettings.getMinorVersion());
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(engineSettings.width, engineSettings.height, engineSettings.name.c_str(), NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Input& input = *Input::get();
    input.setWindow(window);

    ShaderCompiler shaderCompiler;
    shaderCompiler.compileShaders(std::filesystem::path("shaders"));

    Camera& camera = *Camera::get();
    camera.setSize(engineSettings.width, engineSettings.height);

    Sprite sprite("awesomeface.png");

    glViewport(0, 0, engineSettings.width, engineSettings.height);

    SpriteRenderer spriteRenderer(ShaderProgram(shaderCompiler.getShader("default_spritevs"), shaderCompiler.getShader("default_spritefs")));
    spriteRenderer.initRenderData();

    while (!glfwWindowShouldClose(window)) {
        // input
        input.pollInputEvents();
        if (input.exitRequested())
            glfwSetWindowShouldClose(window, true);

        auto& direction = input.getDirection();
        camera.addOffset(direction.x, direction.y);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        spriteRenderer.render(sprite);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
