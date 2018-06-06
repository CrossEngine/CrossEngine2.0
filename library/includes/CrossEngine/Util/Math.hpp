/**************************************************************
 * Program Title: CrossEngine
 * Filename: Math.hpp
 * Author: Blake Rogan
 * Last modified: 6/06/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#ifndef CROSSENGINE_MATH_HPP
#define CROSSENGINE_MATH_HPP

#include <CrossEngine/Util/Containers.hpp>

#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace CrossEngine {
    namespace Util {
        namespace Math {
            typedef glm::mat4 Matrix4;
            typedef glm::mat3 Matrix3;
            typedef glm::mat2 Matrix2;

            typedef glm::vec4 Vector4;
            typedef glm::vec3 Vector3;
            typedef glm::vec2 Vector2;
            typedef glm::vec1 Vector1;

            typedef glm::quat Quaternion;



            typedef Containers::Vector<Matrix4> Matrix4Vector;

        }
    }
}

//static inline CrossEngine::Util::Math::Matrix4 operator* (CrossEngine::Util::Math::Matrix4 lhs, CrossEngine::Util::Math::Matrix4 rhs) {
//    return lhs * rhs;
//}


#endif //CROSSENGINE_MATH_HPP
