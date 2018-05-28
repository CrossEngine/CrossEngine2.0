/**************************************************************
 * Program Title: CrossEngine
 * Filename: Containers.hpp
 * Author: Blake Rogan
 * Last modified: 27/05/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#ifndef CROSSENGINE_CONTAINERS_HPP
#define CROSSENGINE_CONTAINERS_HPP

#include <CrossEngine/Util/Memory.hpp>
#include <vector>

namespace CrossEngine {
    namespace Util {
        namespace Containers {

            using String = std::string;

            template <class _Tp>
            using Vector = std::vector<_Tp, Util::Memory::Allocator<_Tp>>;

        }
    }
}


#endif //CROSSENGINE_CONTAINERS_HPP
