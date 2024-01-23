#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Windows.h>

struct GloneSettings {
    std::string name;
    uint32_t width;
    uint32_t height;
};

int main(int argc, char* argv[])
{
    std::cout << "Hemllo" << std::endl;
    auto engineSettings = GloneSettings {
        "Glone Engine",
        640,
        360
    };

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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

    auto console = GetConsoleWindow();
    ShowWindow(console, SW_HIDE);

    glViewport(0, 0, engineSettings.width, engineSettings.height);
    while (!glfwWindowShouldClose(window))
    {
        //input
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        //render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
