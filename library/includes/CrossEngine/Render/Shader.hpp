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

        typedef void* NativeShaderType;

        /**
         *
         */
        class ShaderSource {
        protected:
            Util::String name; /** */
            Util::CharVector source; /** */
            unsigned int type; /** */

        public:
            /**
             *
             * \param name
             * \param source
             * \param type
             */
            CrossEngineAPI ShaderSource(const Util::String &name, const Util::CharVector &source, unsigned int type);

            /**
             *
             */
            CrossEngineAPI ~ShaderSource();
        };

        /**
         *
         */
        typedef Util::Memory::Shared <ShaderSource> SharedShaderSource;

        /**
         *
         */
        typedef Util::Containers::Vector <SharedShaderSource> ShaderSourceVector;

        /**
         *
         */
        typedef Util::Containers::UnorderedMap <Util::String, SharedShaderSource> ShaderSourceMap;

        /**
         *
         */
        class ShaderProgram {
        public:
            /**
             *
             * \param sources
             */
            CrossEngineAPI explicit ShaderProgram(const ShaderSourceVector &sources);

            /**
             *
             */
            CrossEngineAPI ~ShaderProgram();

            CrossEngineAPI virtual NativeShaderType Bind() = 0;

            CrossEngineAPI virtual void Unbind(NativeShaderType shader) = 0;

            CrossEngineAPI virtual void Matrix4(const Util::String& name, Util::Math::Matrix4 matrix4) = 0;

            CrossEngineAPI virtual void Matrix4v(const Util::String& name, Util::Math::Matrix4Vector matrix4) = 0;

        };

        /**
         *
         */
        typedef Util::Memory::Shared <ShaderProgram> SharedShaderProgram;

        /**
         *
         */
        typedef Util::Containers::UnorderedMap <Util::String, SharedShaderProgram> ShaderProgramMap;
    }
}


#endif //CROSSENGINE_SHADER_HPP
