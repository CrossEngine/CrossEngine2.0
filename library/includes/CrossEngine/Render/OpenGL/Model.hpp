/**************************************************************
 * Program Title: CrossEngine
 * Filename: Model.hpp
 * Author: Blake Rogan
 * Last modified: 1/06/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#ifndef CROSSENGINE_MODEL_HPP
#define CROSSENGINE_MODEL_HPP
#include <CrossEngine/config.h>
#include <CrossEngine/Util/Util.hpp>
#include <CrossEngine/Render/RenderObject.hpp>
#include <CrossEngine/Render/OpenGL/OpenGL.hpp>

namespace CrossEngine {
    namespace Render {

        typedef struct OpenGLRenderType {
            GLuint vao;
            GLuint buffers[2];
            GLsizei count;
            bool indexed;
        } OpenGLRenderType;

        class OpenGLModel: public Model {
        private:
            Util::Containers::Vector<OpenGLRenderType*> meshes;

        public:
            CrossEngineAPI explicit OpenGLModel(const MeshCompileVector &meshes);

            CrossEngineAPI ~OpenGLModel();

            CrossEngineAPI void Render() override;

        };
    }
}


#endif //CROSSENGINE_MODEL_HPP
