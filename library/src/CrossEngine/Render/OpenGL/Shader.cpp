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
                                                                    const CrossEngine::Util::CharVector &source, unsigned int type)
        : ShaderSource(name, source, type) {
    shader = glCreateShader(type);
    glShaderSource(shader, source.size(), source.data(), 0);

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
    glCheckError(CrossEngine::Logging::GetLogger("OpenGLShader"));
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
    glCheckError(CrossEngine::Logging::GetLogger("OpenGLProgram"));
}

CrossEngine::Render::OpenGL::OpenGLShaderProgram::~OpenGLShaderProgram() {
    glDeleteProgram(program);
    glCheckError(CrossEngine::Logging::GetLogger("OpenGLProgram"));
}

CrossEngine::Render::NativeShaderType CrossEngine::Render::OpenGL::OpenGLShaderProgram::Bind() {
    GLint current;
    glGetIntegerv(GL_CURRENT_PROGRAM, &current);
    glUseProgram(program);
    glCheckError(CrossEngine::Logging::GetLogger("OpenGLProgram"));
    return reinterpret_cast<NativeShaderType>(current);
}

void CrossEngine::Render::OpenGL::OpenGLShaderProgram::Unbind(CrossEngine::Render::NativeShaderType shader) {
    if (shader == nullptr) {
        glUseProgram(0);
    } else {
        GLuint current = static_cast<GLuint>(reinterpret_cast<intptr_t>(shader));
        glUseProgram(current);
    }
    glCheckError(CrossEngine::Logging::GetLogger("OpenGLProgram"));
}

GLint CrossEngine::Render::OpenGL::OpenGLShaderProgram::GetUniformLocation(const CrossEngine::Util::String &name) {
    auto it = uniformLocations.find(name);
    if (it == uniformLocations.end()) {
        GLint loc = glGetUniformLocation(program, name.c_str());
        glCheckError(CrossEngine::Logging::GetLogger("OpenGLProgram"));
        uniformLocations[name] = loc;
        return loc;
    }
    return (*it).second;
}

void CrossEngine::Render::OpenGL::OpenGLShaderProgram::Matrix4(const CrossEngine::Util::String &name,
                                                               CrossEngine::Util::Math::Matrix4 matrix4) {
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix4[0][0]);
}

void CrossEngine::Render::OpenGL::OpenGLShaderProgram::Matrix4v(const CrossEngine::Util::String &name,
                                                                CrossEngine::Util::Math::Matrix4Vector matrix4) {
    glUniformMatrix4fv(GetUniformLocation(name), matrix4.size(), GL_FALSE, &matrix4[0][0][0]);
}
