#ifndef WET1_MAP_H
#define WET1_MAP_H

#include <cassert>
#include <utility>
#include <algorithm>
#include "TreeNode.h"
#include "AVL_Tree.h"
#include "AVL_Tree_iterator.h"

template<class T, class S>
class Map
{
    AVL_Tree<std::pair<T,S>>* tree;
    const TreeNode<std::pair<T,S>>* findVal(const T& key) const;
        
    public:
    Map(AVL_Tree<std::pair<T,S>>* tree = nullptr) : tree(tree) {}
    ~Map() = default;
    void insert(const T& key, const S& val);
    void remove(const T& key);
    bool contains(const T& key) const;
    const S& operator[] (const T& key) const;
};

//Insert a given key and a given value into map
template<class T, class S>
void Map<T,S>::insert(const T& key, const S& val)
{
    std::pair<T,S> tmp(key, val);
    this->tree->insertNode(tmp);
}

//The function removes only the minimal node with a given key
template<class T, class S>
void Map<T,S>::remove(const T& key)
{
    typename AVL_Tree<std::pair<T,S>>::iterator it = tree->begin();    
    while((it != tree->end()) && ((*it).first <= key))
    {
        if((*it).first == key)
        {
            std::pair<T,S> tmp(*it);
            this->tree->removeNode(tmp);
            break;
        }
        it++;
    }    
}

//The function returns true if map has an element with a given key
template<class T, class S>
bool Map<T,S>::contains(const T& key) const
{
    return (this->findVal(key));
}

template<class T, class S>
const TreeNode<std::pair<T,S>>* Map<T,S>::findVal(const T& key) const
{
    for(typename AVL_Tree<std::pair<T,S>>::const_iterator it = tree->cbegin() ; it != tree->cend() ; it++)
    {
        if((*it).first == key)
        {
            return it.node;
        }
    }
    return nullptr;
}

template<class T, class S>
const S& Map<T,S>::operator[] (const T& key) const
{
    if(!this->contains(key))
    {
        //throw excpetion
    }
    const TreeNode<std::pair<T,S>>* tmp = this->findVal(key);
    return tmp->getData().second;
}

#endif //WET1_MAP_H