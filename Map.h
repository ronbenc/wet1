//********************************Generic Map***************************************

// The data structure is an implementation of a genereic Map in which T is key's type, S is value's type

//***********Assumptions on T and S*************
// The following operators should be available for both T and S
// operator<, operator>, operator<=, operator >= operator==, operator!=, operator= between two objects from the same type
// operator<<(ostream&, T)

//***********Functionality*************
// The following data structure supports the follwing operations:

// Constructor of a map, returns the map by value, default tree is nullptr
// Map(AVL_Tree<std::pair<T,S>>* tree = nullptr);

//Insert a given key and it's value into the map
// void insert(const T& key, const S& val);

//Remove a given key and it's minimal value from the map
// void remove(const T& key);

//The function returns true if map has at least one value for a given key
// bool contains(const T& key) const;

//The function returns the minimal value of a given key
// const S& operator[] (const T& key) const;

//****************Example of Use****************
// int main()
// {
//     AVL_Tree<std::pair<int, int>> tree = AVL_Tree<std::pair<int, int>>();    
//     Map<int, int> map(&tree);
//     map.insert(10, 40);
//     map.insert(10, 38);
//     map.insert(11, 21);
//     map.insert(9, 24);
//     map.remove(9);
//     map.remove(10);
//     std::cout << "value of 6 is: " << map[6] << std::endl;
//     return 0;
// }



#ifndef WET1_MAP_H
#define WET1_MAP_H

#include <cassert>
#include <utility>
#include <iostream>
#include <algorithm>
#include "TreeNode.h"
#include "AVL_Tree.h"
#include "AVL_Tree_iterator.h"

template<class T, class S>
class Map
{
    AVL_Tree<std::pair<T,S>>* tree;
    TreeNode<std::pair<T,S>>* findVal(const T& key) const;
            
    public:
    // AVL_Tree<std::pair<T,S>>* tree;
    Map(AVL_Tree<std::pair<T,S>>* tree = nullptr) : tree(tree) {}
    ~Map() = default;
    void insert(const T& key, const S& val);
    void remove(const T& key);
    bool contains(const T& key) const;
    const S& operator[] (const T& key) const;
    const AVL_Tree<std::pair<T,S>>* getTree() const;
    AVL_Tree<std::pair<T,S>>* getTree();

    class iterator;
    iterator begin() const;
    iterator end() const; 
    class const_iterator;
    const_iterator cbegin() const;
    const_iterator cend() const; 
};

// template<class T, class S>
// std::ostream& operator<<(std::ostream& os, Map<T,S> map)
// {
//      all with iterators
// }

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
    TreeNode<std::pair<T,S>>* node = this->findVal(key);
    tree->removeNode(node->getData()); 
}

//The function returns true if map has an element with a given key
template<class T, class S>
bool Map<T,S>::contains(const T& key) const
{
    return (this->findVal(key));
}


template<class T, class S>
TreeNode<std::pair<T,S>>* Map<T,S>::findVal(const T& key) const
{
    TreeNode<std::pair<T,S>>* node = tree->getRoot();
    while(node)
    {
        if(key == node->getData().first)
        {
            return node;
        }
        else if(key < node->getData().first)
        {
            node = node->getLeft();
        }
        else
        {
            node = node->getRight();
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

template<class T, class S>
const AVL_Tree<std::pair<T,S>>* Map<T,S>::getTree() const
{
    return this->tree;
}

template<class T, class S>
AVL_Tree<std::pair<T,S>>* Map<T,S>::getTree()
{
    return this->tree;
}

//*********************iterator************************************
//Dereference - both key and value
//increment (prefix and suffix)
//equal operator - returns true if both iterators are in the same tree, 
//and keys and values are identical between tro iterators, else otherwise
//inequal operator - returns true if iterators differ in at least one of the following: 
//tree, key or value
template<class T, class S>
class Map<T,S>::iterator
{
    friend class Map<T,S>;
    typename AVL_Tree<std::pair<T,S>>::iterator* it;
       
    public:    
    iterator(const AVL_Tree<std::pair<T,S>>*);
    // const std::pair<T,S>& operator*() const;
    // iterator& operator++();
    // iterator operator++(int);    
    // bool operator==(const iterator& it) const;
    // bool operator!=(const iterator& it) const;
    // iterator(const iterator&) = default;    
    // iterator& operator=(const iterator&) = default;
    // ~iterator() = default;
};

template<class T, class S>
Map<T,S>::iterator::iterator(const AVL_Tree<std::pair<T,S>>* tree_ptr)
{
    *it = typename AVL_Tree<std::pair<T,S>>::iterator(tree_ptr, 0);
}

// typename Map<T,S>::iterator Map<T,S>::begin() const
// {
    
// }



//  : tree(map->tree), node(map.findVal(key)) {}

// template<class T, class S>
// typename Map<T,S>::iterator Map<T,S>::begin() const
// {
//     return iterator(this, tree->min);
// }

// template<class T, class S>
// typename Map<T,S>::iterator Map<T,S>::end() const
// {
//     return nullptr;
//     // return iterator(this, this->size);
// }

// template<class T, class S>
// const std::pair<T,S>& Map<T,S>::iterator::operator*() const
// {
//     if(index >= this->tree->size)
//     {
//         //throw exception
//     }
//     return this->node->getData();
// }

// template<class T, class S>
// typename Map<T,S>::iterator& Map<T,S>::iterator::operator++ () 
// {
//     ++index;
//     node = this->tree->findNextPtr(node);
//     return *this;
// }

// template<class T, class S>
// typename Map<T,S>::iterator Map<T,S>::iterator::operator++ (int) 
// {
//     iterator result = *this;
//     ++*this;
//     return result;
// }

// template<class T, class S>
// bool Map<T,S>::iterator::operator== (const Map<T,S>::iterator& a) const
// {
//     return ((this->tree == a.tree) && (this->index == a.index));
// }

// template<class T, class S>
// bool Map<T,S>::iterator::operator!= (const Map<T,S>::iterator& a) const
// {
//     return !(*this == a);
// }

#endif //WET1_MAP_H