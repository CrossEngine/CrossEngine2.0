/**************************************************************
 * Program Title: CrossEngine
 * Filename: Shader.hpp
 * Author: Blake Rogan
 * Last modified: 1/06/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#ifndef CROSSENGINE_SHADER_HPP
#define CROSSENGINE_SHADER_HPP

#include <CrossEngine/config.h>
#include <CrossEngine/Util/Util.hpp>

namespace CrossEngine {
    namespace Render {

        class ShaderSource {
        protected:
            Util::String name;
            Util::String source;
            unsigned int type;

        public:
            ShaderSource(const Util::String& name, const Util::String& source, unsigned int type);

            ~ShaderSource();
        };

        typedef Util::Memory::Shared<ShaderSource> SharedShaderSource;

        typedef Util::Containers::Vector<SharedShaderSource> ShaderSourceVector;

        typedef Util::Containers::UnorderedMap<Util::String, SharedShaderSource> ShaderSourceMap;

        class ShaderProgram {
        public:
            ShaderProgram(const ShaderSourceVector& sources);

            ~ShaderProgram();

        };

        typedef Util::Memory::Shared<ShaderProgram> SharedShaderProgram;

        typedef Util::Containers::UnorderedMap<Util::String, SharedShaderProgram> ShaderProgramMap;
    }
}


#endif //CROSSENGINE_SHADER_HPP
