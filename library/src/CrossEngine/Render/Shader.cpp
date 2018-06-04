/**************************************************************
 * Program Title: CrossEngine
 * Filename: Shader.cpp
 * Author: Blake Rogan
 * Last modified: 1/06/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#include <CrossEngine/Render/Shader.hpp>

CrossEngine::Render::ShaderSource::ShaderSource(const CrossEngine::Util::String &name,
                                                const CrossEngine::Util::String &source, unsigned int type) {
    this->name = name;
    this->source = source;
    this->type = type;
}

CrossEngine::Render::ShaderSource::~ShaderSource() {

}

CrossEngine::Render::ShaderProgram::ShaderProgram(const CrossEngine::Render::ShaderSourceVector &sources) {

}

CrossEngine::Render::ShaderProgram::~ShaderProgram() {

}
