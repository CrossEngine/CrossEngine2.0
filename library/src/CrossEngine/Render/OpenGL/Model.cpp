/**************************************************************
 * Program Title: CrossEngine
 * Filename: Model.cpp
 * Author: Blake Rogan
 * Last modified: 1/06/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/

#include <CrossEngine/Render/OpenGL/Model.hpp>

CrossEngine::Render::OpenGLModel::OpenGLModel(const std::vector<CompiledMesh> &meshes) : Model(meshes) {
    for (CompiledMesh mesh : meshes) {
        auto m = (CrossEngine::Render::OpenGLRenderType*)mesh;
        this->meshes.push_back(m);
    }
}

CrossEngine::Render::OpenGLModel::~OpenGLModel() {
    for (const auto &mesh : meshes) {
        delete mesh;
    }
    meshes.clear();
}

void CrossEngine::Render::OpenGLModel::Render() {
    auto modelLogger = CrossEngine::Logging::GetLogger("OpenGLModel");
    for (const auto &mesh : meshes) {
        if (mesh->vao == 0) {
            glGenVertexArrays(1, &mesh->vao);
            glCheckError(modelLogger);
        }
        glBindVertexArray(mesh->vao);
        glCheckError(modelLogger);
        glEnableVertexAttribArray(0);
        glCheckError(modelLogger);
        glBindBuffer(GL_ARRAY_BUFFER, mesh->buffers[0]);
        glCheckError(modelLogger);
        glVertexAttribPointer(
                0,
                3,
                GL_FLOAT,
                GL_FALSE,
                0,
                (void *) 0
        );
        glCheckError(modelLogger);
        if (mesh->indexed) {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->buffers[1]);
            glCheckError(modelLogger);
            glDrawElements(GL_TRIANGLES, mesh->count, GL_UNSIGNED_INT, (void *) 0);
            glCheckError(modelLogger);
        } else {
            glDrawArrays(GL_TRIANGLES, 0, mesh->count);
            glCheckError(modelLogger);
        }
        glDisableVertexAttribArray(0);
        glCheckError(modelLogger);
    }
}
