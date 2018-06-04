/**************************************************************
 * Program Title: CrossEngine
 * Filename: Shader.cpp
 * Author: Blake Rogan
 * Last modified: 1/06/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#include <CrossEngine/Render/OpenGL/Shader.hpp>
#include <CrossEngine/Logging/Logging.hpp>

CrossEngine::Render::OpenGL::OpenGLShaderSource::OpenGLShaderSource(const CrossEngine::Util::String &name,
                                                                    const CrossEngine::Util::String &source, unsigned int type)
        : ShaderSource(name, source, type) {
    shader = glCreateShader(type);
    auto size = static_cast<GLint>(source.size());
    const char* sourceCode = source.c_str();
    glShaderSource(shader, 1, &sourceCode,  &size);

    glCompileShader(shader);

    GLint result;
    int logLength;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
        std::vector<char> log(static_cast<size_t>(logLength + 1));
        glGetShaderInfoLog(shader, logLength, nullptr, &log[0]);
        CrossEngine::Logging::GetLogger("OpenGLShader")->error("Failed to compile '{}': {}", name, &log[0]);
    }
}

CrossEngine::Render::OpenGL::OpenGLShaderSource::~OpenGLShaderSource() {
    glDeleteShader(shader);
}

GLuint CrossEngine::Render::OpenGL::OpenGLShaderSource::GetShader() const {
    return shader;
}

CrossEngine::Render::OpenGL::OpenGLShaderProgram::OpenGLShaderProgram(
        const CrossEngine::Render::ShaderSourceVector &sources) : ShaderProgram(sources) {
    program = glCreateProgram();
    for (const auto &source : sources) {
        glAttachShader(program, std::static_pointer_cast<CrossEngine::Render::OpenGL::OpenGLShaderSource>(source)->GetShader());
    }
    glLinkProgram(program);

    GLint result;
    int logLength;
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    if (result == GL_FALSE) {
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
        std::vector<char> log(static_cast<size_t>(logLength + 1));
        glGetProgramInfoLog(program, logLength, nullptr, &log[0]);
        CrossEngine::Logging::GetLogger("OpenGLProgram")->error("Failed to link program: {}", &log[0]);
    }


    for (const auto &source : sources) {
        glDetachShader(program, std::static_pointer_cast<CrossEngine::Render::OpenGL::OpenGLShaderSource>(source)->GetShader());
    }
}

CrossEngine::Render::OpenGL::OpenGLShaderProgram::~OpenGLShaderProgram() {
    glDeleteProgram(program);
}
