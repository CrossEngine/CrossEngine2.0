/**************************************************************
 * Program Title: CrossEngine
 * Filename: OpenGL.hpp
 * Author: Blake Rogan
 * Last modified: 5/06/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#ifndef CROSSENGINE_OPENGL_HPP
#define CROSSENGINE_OPENGL_HPP

#include <CrossEngine/config.h>
#include <CrossEngine/Logging/Logging.hpp>

#ifdef __glad_h_
#error "Glad alread included"
#endif

#ifdef __gl_h_
#error "GL alread included"
#endif

#include <glad/glad.h>

namespace CrossEngine {
    namespace Render {
        namespace OpenGL {

            static inline const char *EnumToString(GLenum value) {
                switch (value) {
                    default:
                        return "Unknown GLenum: " + value;
                    case GL_NO_ERROR:
                        return "No Error";
                    case GL_INVALID_ENUM:
                        return "GL_INVALID_ENUM";
                    case GL_INVALID_VALUE:
                        return "GL_INVALID_VALUE";
                    case GL_INVALID_OPERATION:
                        return "GL_INVALID_OPERATION";
                    case GL_OUT_OF_MEMORY:
                        return "GL_OUT_OF_MEMORY";
                }
            }

            static inline bool CheckError(const char *file, int line, const Logging::SharedLogger &log) {
                GLenum value = glGetError();
                if (value == GL_NO_ERROR) {
                    return true;
                }
                log->info("OpenGL Error [{}:{}]: {}", file, line, EnumToString(value));
                return false;
            }
        }
    }
}

#define glCheckError(logger) CrossEngine::Render::OpenGL::CheckError(__FILE__, __LINE__, logger);

#endif //CROSSENGINE_OPENGL_HPP
