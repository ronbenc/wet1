#ifndef AVL_MAP_H
#define AVL_MAP_H

#include <cassert>
#include <algorithm>
#include "TreeNode.h"
#include "AVL_Tree.h"
#include "AVL_Tree_iterator.h"

template<class T, class S>
class AVL_Map : public AVL_Tree<std::pair<T,S>>
{
    public:
    explicit AVL_Map(AVL_Tree<std::pair<T,S>>* tree = nullptr) : root(tree->r) {};
    ~AVL_Map() = default;
    const S& operator[] (const T& key) const;

};

#endif //AVL_MAP_H