/**************************************************************
 * Program Title: CrossEngine
 * Filename: OpenGLRenderer.cpp
 * Author: Blake Rogan
 * Last modified: 31/05/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#include <CrossEngine/Render/OpenGLRenderer.hpp>

#include "CrossEngine/Render/OpenGLRenderer.hpp"

bool CrossEngine::Render::OpenGLRenderer::Setup(GLFWwindow *window) {
    Renderer::Setup(window);

    if (glfwGetCurrentContext() != window) {
        glfwMakeContextCurrent(window);
    }

    if (gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)) == GL_TRUE) {
        log->info("OpenGL Version: {}.{}", GLVersion.major, GLVersion.minor);
    }
    return true;
}

bool CrossEngine::Render::OpenGLRenderer::Render(GLFWwindow *window) {
    if (glfwGetCurrentContext() != window) {
        glfwMakeContextCurrent(window);
    }
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1, 0, 0, 1);
    glViewport(0, 0, 800, 600);

    glFlush();
    glfwSwapBuffers(window);
    return Renderer::Render(window);
}

bool CrossEngine::Render::OpenGLRenderer::Teardown(GLFWwindow *window) {
    return Renderer::Teardown(window);
}
