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

#include <CrossEngine/config.h>
#include <CrossEngine/Render/Shader.hpp>
#include <CrossEngine/Render/OpenGL/OpenGL.hpp>

namespace CrossEngine {
    namespace Render {
        namespace OpenGL {
            /**
             *
             */
            class OpenGLShaderSource: public ShaderSource {
            private:
                GLuint shader; /** */

            public:
                /**
                 *
                 * \param name
                 * \param source
                 * \param type
                 */
                CrossEngineAPI OpenGLShaderSource(const Util::String &name, const Util::CharVector &source, unsigned int type);

                /**
                 *
                 */
                CrossEngineAPI ~OpenGLShaderSource();

                /**
                 *
                 * \return
                 */
                CrossEngineAPI GLuint GetShader() const;

            };

            /**
             *
             */
            class OpenGLShaderProgram: public ShaderProgram {
            private:
                GLuint program; /** */

                Util::Containers::UnorderedMap<Util::String, GLint> uniformLocations;
            public:
                /**
                 *
                 * \param sources
                 */
                CrossEngineAPI explicit OpenGLShaderProgram(const ShaderSourceVector &sources);

                /**
                 *
                 */
                CrossEngineAPI ~OpenGLShaderProgram();

                CrossEngineAPI NativeShaderType Bind() override;

                CrossEngineAPI void Unbind(NativeShaderType shader) override;

                CrossEngineAPI GLint GetUniformLocation(const Util::String& name);

                CrossEngineAPI void Matrix4(const Util::String& name, Util::Math::Matrix4 matrix4) override;

                CrossEngineAPI void Matrix4v(const Util::String& name, Util::Math::Matrix4Vector matrix4) override;

            };
        }
    }
}


#endif //CROSSENGINE_OPENGL_SHADER_HPP
