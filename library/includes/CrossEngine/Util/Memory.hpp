/**************************************************************
 * Program Title: CrossEngine
 * Filename: Memory.hpp
 * Author: Blake Rogan
 * Last modified: 27/05/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#ifndef CROSSENGINE_MEMORY_HPP
#define CROSSENGINE_MEMORY_HPP

#include <memory>

namespace CrossEngine {
    namespace Util {
        namespace Memory {

            template <class _Tp>
            using Allocator = std::allocator<_Tp>;

            template <class _Tp>
            using Shared = std::shared_ptr<_Tp>;

            template <class _Tp, class ..._Args>
            inline Shared<_Tp> Allocate(_Args...__args) {
                typedef typename std::remove_const<_Tp>::type _Tp_nc;
                return std::allocate_shared<_Tp>(Allocator<_Tp_nc>(), std::forward<_Args>(__args)...);
            }
        }
    }
}


#endif //CROSSENGINE_MEMORY_HPP
