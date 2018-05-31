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
#include <set>
#include <unordered_map>
#include <deque>
#include <queue>

namespace CrossEngine {
    namespace Util {
        namespace Containers {

            using String = std::string;

            template <class _Tp>
            using Vector = std::vector<_Tp, Util::Memory::Allocator<_Tp>>;


            template <class _Key, class _Comp=std::less<_Key>>
            using Set = std::set<_Key, _Comp, Util::Memory::Allocator<_Key>>;

            template <class _Key, class _Value, class _Hash=std::hash<_Key>, class _Pred=std::equal_to<_Key>>
            using UnorderedMap = std::unordered_map<_Key, _Value, _Hash, _Pred, Util::Memory::Allocator<std::pair<const _Key, _Value>>>;

            template <class _Tp>
            using DeQue = std::deque<_Tp, Util::Memory::Allocator<_Tp>>;

            template <class _Tp, class _Seq=DeQue<_Tp>>
            using Queue = std::queue<_Tp, _Seq>;

            template <class _Tp, class _Seq=DeQue<_Tp>, class _Comp=std::less<typename _Seq::value_type>>
            using PriorityQueue = std::priority_queue<_Tp, _Seq, _Comp>;

        }
    }
}


#endif //CROSSENGINE_CONTAINERS_HPP
