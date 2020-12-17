//********************************Generic Map + Iterators***************************************

// The data structure is an implementation of a genereic Map in which T is key's type, S is value's type.
//The structure also provides iterator and const_iterator as detailed below.

//***********Assumptions on T and S*************
// The following operators should be available for both T and S
// operator<, operator>, operator<=, operator >= operator==, operator!=, operator= between two objects from the same type
// operator<<(ostream&, T), operator<<(ostream&, S)

//***********Functionality*************
// The following data structure supports the follwing operations:

// Constructor of a map, returns an empty map
// Map<T,S>::Map();

//If the given key does not show in the map, insert the given key and it's value into the map
// void Map<T,S>::insert(const T& key, const S& val);

//Remove a given key and it's value from the map
// void Map<T,S>::remove(const T& key);

//The function returns true if map has at least one value for a given key
// bool Map<T,S>::contains(const T& key) const;

//The function returns the minimal value of a given key, only for accessing purposes (not for changing the map)
// const S& Map<T,S>::operator[] (const T& key) const;

//The function returns iterator to the minimal object in the tree
// iterator begin() const;
// const_iterator cbegin() const;

//The function returns iterator to the successor of maximal element in tree
// iterator end() const; 
// const_iterator cend() const; 

//Dereference to the element of type pair
// pair<T,S>& Map<T,S>::iterator::operator*() const;
// const pair<T,S>& Map<T,S>::const_iterator::operator*() const;

//Increment the iterator (prefix)
// iterator& Map<T,S>::iterator::operator++();
// const_iterator& Map<T,S>::const_iterator::operator++();

//Increment the iterator (suffix)
// iterator Map<T,S>::iterator::operator++(int);
// const_iterator Map<T,S>::const_iterator::operator++(int);    

//Equal operator - returns true if both iterators contain the same element from the same tree, false otherwise
// bool Map<T,S>::iterator::operator==(const iterator& it) const;
// bool Map<T,S>::const_iterator::operator==(const const_iterator& it) const;

//Inequal operator - returns true if iterators don't contain the same tree or the same element, false otherwise
// bool Map<T,S>::iterator::operator!=(const iterator& it) const;
// bool Map<T,S>::const_iterator::operator!=(const const_iterator& it) const;

//Copy c'tor
// Map<T,S>::iterator::iterator(const iterator&);
// Map<T,S>::const_iterator::const_iterator(const const_iterator&);

//Assignment operator
// iterator& Map<T,S>::iterator::operator=(const iterator&);
// const_iterator& Map<T,S>::const_iterator::operator=(const const_iterator&);

//Printing operator:
// std::ostream& operator<<(std::ostream& os, const Map<T,S>*& map)

//****************Example of Use****************
// int main()
// {
//     Map<int, int> map;
//     map.insert(10, 40);
//     map.insert(10, 38);
//     map.insert(11, 21);
//     map.insert(9, 24);
//     map.remove(9);
//     map.remove(10);
//     std::cout << "value of 6 is: " << map[6] << std::endl;
//     Map<int, int>::const_iterator beg = map.cbegin();    
//     Pair<int, int> tmp;
//     while(beg != map.cend())
//     {
//         tmp = *beg;
//         ++beg;
//     }
//     std::cout << map << std::endl;
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
#include "Pair.h"
#include "Exceptions.h"

template<class T, class S>
class Map
{
    AVL_Tree<Pair<T, S>> tree;
    TreeNode<Pair<T,S>>* findVal(const T& key) const;
    S& operator[] (const T& key); 
    AVL_Tree<Pair<T, S>>* getTree()
    {
        return &this->tree;
    }       
    
            
    public:     
    
    Map() = default;
    ~Map() = default;
    void insert(const T& key, const S& val);
    void remove(const T& key);
    bool contains(const T& key) const;
    const S& operator[] (const T& key) const;

    class iterator;
    iterator begin() const;
    iterator end() const; 
    class const_iterator;
    const_iterator cbegin() const;
    const_iterator cend() const; 
};

//Printing operator for a map
template<class T, class S>
std::ostream& operator<<(std::ostream& os, const Map<T,S>& map)
{
    typename Map<T,S>::iterator it = map.begin();
    while(it != map.end())
    {
        os << (*it) << std::endl;
        it++;
    }
    return os;
}

template<class T, class S>
void Map<T,S>::insert(const T& key, const S& val)
{
    if(!this->contains(key))
    {
        tree.insertNode(Pair<T,S>(key, val));
    }        
}

template<class T, class S>
void Map<T,S>::remove(const T& key)
{
    TreeNode<Pair<T,S>>* node = this->findVal(key);
    if(!node) {return;}    
    tree.removeNode(node->getData());
}

template<class T, class S>
bool Map<T,S>::contains(const T& key) const
{
    return (this->findVal(key));
}

template<class T, class S>
TreeNode<Pair<T,S>>* Map<T,S>::findVal(const T& key) const
{
    TreeNode<Pair<T,S>>* node = tree.getRoot();
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
        throw IllegalArgument_Map();
    }
    const TreeNode<Pair<T,S>>* tmp = this->findVal(key);
    return tmp->getData().second;
}

template<class T, class S>
S& Map<T,S>::operator[] (const T& key)
{
    if(!this->contains(key))
    {
        throw IllegalArgument_Map();
    }
    TreeNode<Pair<T,S>>* tmp = this->findVal(key);    
    return tmp->getData().second;
}

//*********************iterator************************************
template<class T, class S>
class Map<T,S>::iterator
{
    friend class Map<T,S>;
    typename AVL_Tree<Pair<T,S>>::iterator tree_it;
    explicit iterator(const Map<T,S>* map, int index = 0);
    iterator() : tree_it(AVL_Tree<Pair<T,S>>::iterator()) {};

    public:    
    Pair<T,S>& operator*() const;
    iterator& operator++();
    iterator operator++(int);    
    bool operator==(const iterator& it) const;
    bool operator!=(const iterator& it) const;
    iterator(const iterator&) = default;    
    iterator& operator=(const iterator&) = default;
    ~iterator() = default;
};

template<class T, class S>
Map<T,S>::iterator::iterator(const Map<T,S>* map, int index)
{
    if(!map)
    {
        throw IllegalArgument_Map();
    }
    if(index == map->tree.getSize())
    {
        tree_it = map->tree.end();
    }
    else
    {
        assert(index == 0);
        tree_it = map->tree.begin();
    }
}

template<class T, class S>
typename Map<T,S>::iterator Map<T,S>::begin() const
{
    return iterator(this, 0);
}

template<class T, class S>
typename Map<T,S>::iterator Map<T,S>::end() const
{
    return iterator(this, this->tree.getSize());
}

template<class T, class S>
Pair<T,S>& Map<T,S>::iterator::operator*() const
{
    return *tree_it;
}

//prefix
template<class T, class S>
typename Map<T,S>::iterator& Map<T,S>::iterator::operator++()
{
    this->tree_it++;
    return *this;
}

//suffix
template<class T, class S>
typename Map<T,S>::iterator Map<T,S>::iterator::operator++(int) 
{
    iterator result = *this;
    ++(*this);
    return result;
}

template<class T, class S>
bool Map<T,S>::iterator::operator== (const Map<T,S>::iterator& a) const
{
    return (this->tree_it == a.tree_it);
}

template<class T, class S>
bool Map<T,S>::iterator::operator!= (const Map<T,S>::iterator& a) const
{
    return !(*this == a);
}

//*********************const_iterator************************************

template<class T, class S>
class Map<T,S>::const_iterator
{
    friend class Map<T,S>;
    typename AVL_Tree<Pair<T,S>>::const_iterator tree_it;
    explicit const_iterator(const Map<T,S>* map, int index = 0);
    const_iterator() : tree_it(AVL_Tree<Pair<T,S>>::const_iterator()) {};

    public:        
    const Pair<T,S>& operator*() const;
    const_iterator& operator++();
    const_iterator operator++(int);    
    bool operator==(const const_iterator& it) const;
    bool operator!=(const const_iterator& it) const;
    const_iterator(const const_iterator&) = default;    
    const_iterator& operator=(const const_iterator&) = default;
    ~const_iterator() = default;
};

template<class T, class S>
Map<T,S>::const_iterator::const_iterator(const Map<T,S>* map, int index)
{
    if(!map)
    {
        throw IllegalArgument_Map();
    }
    if(index == map->tree.getSize())
    {
        tree_it = map->tree.cend();
    }
    else
    {
        assert(index == 0);
        tree_it = map->tree.cbegin();
    }
}

template<class T, class S>
typename Map<T,S>::const_iterator Map<T,S>::cbegin() const
{
    return const_iterator(this, 0);
}

template<class T, class S>
typename Map<T,S>::const_iterator Map<T,S>::cend() const
{
    return const_iterator(this, this->tree.getSize());    
}

template<class T, class S>
const Pair<T,S>& Map<T,S>::const_iterator::operator*() const
{
    return *tree_it;
}

//prefix
template<class T, class S>
typename Map<T,S>::const_iterator& Map<T,S>::const_iterator::operator++()
{
    this->tree_it++;
    return *this;
}

//suffix
template<class T, class S>
typename Map<T,S>::const_iterator Map<T,S>::const_iterator::operator++(int) 
{
    iterator result = *this;
    ++(*this);
    return result;
}

template<class T, class S>
bool Map<T,S>::const_iterator::operator== (const Map<T,S>::const_iterator& a) const
{
    return (this->tree_it == a.tree_it);
}

template<class T, class S>
bool Map<T,S>::const_iterator::operator!= (const Map<T,S>::const_iterator& a) const
{
    return !(*this == a);
}

#endif //WET1_MAP_H