/**************************************************************
 * Program Title: CrossEngine
 * Filename: Shader.hpp
 * Author: Blake Rogan
 * Last modified: 1/06/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#ifndef CROSSENGINE_OPENGL_SHADER_HPP
#define CROSSENGINE_OPENGL_SHADER_HPP

#include <glad/glad.h>

#include <CrossEngine/config.h>
#include <CrossEngine/Render/Shader.hpp>

namespace CrossEngine {
    namespace Render {

        namespace OpenGL {
            class OpenGLShaderSource: public ShaderSource {
            private:
                GLuint shader;

            public:
                OpenGLShaderSource(const Util::String &name, const Util::String &source, unsigned int type);

                ~OpenGLShaderSource();

                GLuint GetShader() const;

            };

            class OpenGLShaderProgram: public ShaderProgram {
            private:
                GLuint program;
            public:
                OpenGLShaderProgram(const ShaderSourceVector &sources);

                ~OpenGLShaderProgram();

            };
        }
    }
}


#endif //CROSSENGINE_OPENGL_SHADER_HPP
