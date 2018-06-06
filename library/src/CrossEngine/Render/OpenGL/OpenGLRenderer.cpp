/**************************************************************
 * Program Title: CrossEngine
 * Filename: OpenGLRenderer.cpp
 * Author: Blake Rogan
 * Last modified: 31/05/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#include <CrossEngine/Render/OpenGL/OpenGLRenderer.hpp>


CrossEngine::Render::OpenGLRenderer::OpenGLRenderer() : CrossEngine::Render::Renderer() {

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

bool CrossEngine::Render::OpenGLRenderer::Render(Window::Window *window, const Util::DeltaTime &delta) {
    glfwMakeContextCurrent(window->GetWindow());
    Renderer::Render(window, delta);
    glfwSwapBuffers(window->GetWindow());
    return true;
}

bool CrossEngine::Render::OpenGLRenderer::Teardown(Window::Window *window) {
    return Renderer::Teardown(window);
}

CrossEngine::Render::SharedShaderSource
CrossEngine::Render::OpenGLRenderer::LoadShaderSource(const CrossEngine::Util::String &name,
                                                      const CrossEngine::Util::CharVector &source, GLenum type) {
    return CrossEngine::Util::Memory::Allocate<CrossEngine::Render::OpenGL::OpenGLShaderSource>(name, source, type);
}

CrossEngine::Render::SharedShaderProgram
CrossEngine::Render::OpenGLRenderer::LoadShaderProgram(const CrossEngine::Render::ShaderSourceVector &sources) {
    return CrossEngine::Util::Memory::Allocate<CrossEngine::Render::OpenGL::OpenGLShaderProgram>(sources);
}

CrossEngine::Render::Model *
CrossEngine::Render::OpenGLRenderer::CompileRenderObject(CrossEngine::Render::RenderObject **object) {
    auto model = new CrossEngine::Render::OpenGLModel((*object)->Compile([this](CrossEngine::Render::Mesh *mesh) {
        auto render = new CrossEngine::Render::OpenGLRenderType();
        render->vao = 0;

        glGenBuffers(2, &render->buffers[0]);
        glBindBuffer(GL_ARRAY_BUFFER, render->buffers[0]);
        glBufferData(GL_ARRAY_BUFFER, mesh->vertices.size() * sizeof(float), &mesh->vertices[0], GL_STATIC_DRAW);
        if (mesh->indices.empty()) {
            render->indexed = false;
            render->count = static_cast<GLsizei>(mesh->vertices.size());;
        } else {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, render->buffers[1]);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indices.size() * sizeof(unsigned int), &mesh->indices[0], GL_STATIC_DRAW);

            render->indexed = true;
            render->count = static_cast<GLsizei>(mesh->indices.size());
        }
        glCheckError(log);

        return render;
    }));
    delete *object;
    *object = nullptr;
    return model;
}
