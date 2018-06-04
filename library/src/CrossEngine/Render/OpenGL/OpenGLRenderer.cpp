/**************************************************************
 * Program Title: CrossEngine
 * Filename: OpenGLRenderer.cpp
 * Author: Blake Rogan
 * Last modified: 31/05/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#include <CrossEngine/Render/OpenGL/OpenGLRenderer.hpp>
#include <CrossEngine/Window/Window.hpp>



CrossEngine::Render::OpenGLRenderer::OpenGLRenderer(): CrossEngine::Render::Renderer() {

}

CrossEngine::Render::OpenGLRenderer::~OpenGLRenderer() {

}

bool CrossEngine::Render::OpenGLRenderer::Setup(Window::Window *window) {
    Renderer::Setup(window);

    if (glfwGetCurrentContext() != window->GetWindow()) {
        glfwMakeContextCurrent(window->GetWindow());
    }

    if (gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)) == GL_TRUE) {
        log->info("OpenGL Version: {}.{}", GLVersion.major, GLVersion.minor);
    }
    return true;
}

bool CrossEngine::Render::OpenGLRenderer::Render(Window::Window *window, const Util::DeltaTime& delta) {
    if (glfwGetCurrentContext() != window->GetWindow()) {
        glfwMakeContextCurrent(window->GetWindow());
    }
    Renderer::Render(window, delta);
    glfwSwapBuffers(window->GetWindow());
    return true;
}

bool CrossEngine::Render::OpenGLRenderer::Teardown(Window::Window *window) {
    return Renderer::Teardown(window);
}

CrossEngine::Render::SharedShaderSource
CrossEngine::Render::OpenGLRenderer::LoadShaderSource(const CrossEngine::Util::String &name,
                                                      const CrossEngine::Util::String &source, GLenum type) {
    return CrossEngine::Util::Memory::Allocate<CrossEngine::Render::OpenGL::OpenGLShaderSource>(name, source, type);
}

CrossEngine::Render::SharedShaderProgram
CrossEngine::Render::OpenGLRenderer::LoadShaderProgram(const CrossEngine::Render::ShaderSourceVector &sources) {
    return CrossEngine::Util::Memory::Allocate<CrossEngine::Render::OpenGL::OpenGLShaderProgram>(sources);
}
