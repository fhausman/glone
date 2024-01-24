#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader_compiler/shader_compiler.h"

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
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
};

std::vector<uint32_t> indices = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};

int main(int argc, char* argv[])
{
    auto engineSettings = GloneSettings {
        "Glone Engine",
        640,
        360,
        "3.3"
    };

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, engineSettings.getMajorVersion());
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, engineSettings.getMinorVersion());
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(engineSettings.width, engineSettings.height, engineSettings.name.c_str(), NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    ShaderCompiler shaderCompiler;
    shaderCompiler.compileShaders(std::filesystem::path("shaders"));

    glViewport(0, 0, engineSettings.width, engineSettings.height);

    int success = 0;
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, shaderCompiler.getShader("testvs"));
    glAttachShader(shaderProgram, shaderCompiler.getShader("testfs"));
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);

        std::cout << infoLog << std::endl;
    }

    uint32_t VAO;
    glGenVertexArrays(1, &VAO);

    uint32_t VBO;
    glGenBuffers(1, &VBO);

    uint32_t EBO;
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(decltype(vertices)::value_type), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(decltype(indices)::value_type), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))
    {
        //input
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        //render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
