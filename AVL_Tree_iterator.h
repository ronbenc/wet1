//********************************Generic AVL Tree iterator & const_iterator IN ORDER scan:***************************************

// The data structure is an implementation of a genereic AVL Tree iterator & const_iterator scanning tree in-order, in which T is the generic type.

//***********Assumptions*************
// No additional assumptions assumed, other than the assumptions on T as required in AVL Tree

//***********Functionality*************

//Dereference to the element
// T& operator*() const;
// const T& operator*() const;

//Increment the iterator (prefix and suffix)
// iterator& operator++();
// const_iterator& operator++();

//Decrement the iterator (prefix and suffix)
// iterator operator++(int);
// const_iterator operator++(int);

//Equality operator - returns true if and only if both iterators have the same tree and same index
// bool operator==(const iterator& it) const;
// bool operator==(const const_iterator& it) const;

//Inequality operator - returns true if iterators don't have the same tree, or have a different index
// bool operator!=(const iterator& it) const;
// bool operator!=(const const_iterator& it) const;

//Copy C'tor
// iterator(const iterator&);
// const_iterator(const const_iterator&);

//Assignment Operator
// iterator& operator=(const iterator&) = default;
// const_iterator& operator=(const const_iterator&) = default;


//***********Example of Use*************

// int main()
// {    
//     for(AVL_Tree<int>::const_iterator begin = tree.cbegin() ; begin != tree.cend() ; ++begin)
//     {
//         std::cout << (*begin) << " ";
//     }
//     return 0;
// }


#ifndef WET1_AVL_TREE_ITERATOR_H
#define WET1_AVL_TREE_ITERATOR_H

#include <cassert>
#include <algorithm>
#include "TreeNode.h"
#include "AVL_Tree.h"

//*****************Iterator**********************
template<class T>
class AVL_Tree<T>::iterator
{
    explicit iterator(const AVL_Tree<T>* tree, int index = 0);
    friend class AVL_Tree<T>;    

    public:
    iterator() : tree(nullptr), index(0) {};    
    const AVL_Tree<T>* tree;
    int index;
    TreeNode<T>* node;
    T& operator*() const;
    iterator& operator++();
    iterator operator++(int);
    bool operator==(const iterator& it) const;
    bool operator!=(const iterator& it) const;
    iterator(const iterator&) = default;
    iterator& operator=(const iterator&) = default;
    ~iterator() = default;
};

template<class T>
AVL_Tree<T>::iterator::iterator(const AVL_Tree<T>* tree, int index) : tree(tree), index(index), node (tree->min) {}

template<class T>
typename AVL_Tree<T>::iterator AVL_Tree<T>::begin() const
{
    return iterator(this, 0);
}

template<class T>
typename AVL_Tree<T>::iterator AVL_Tree<T>::end() const
{
    return iterator(this, this->size);
}

template<class T>
T& AVL_Tree<T>::iterator::operator*() const
{
    if(!this || index >= this->tree->size)
    {
        throw IllegalArgument_AVL_Tree();
    }
    return this->node->getData();
}

template<class T>
typename AVL_Tree<T>::iterator& AVL_Tree<T>::iterator::operator++ () 
{
    ++index;
    node = this->tree->findNextPtr(node);
    return *this;
}

template<class T>
typename AVL_Tree<T>::iterator AVL_Tree<T>::iterator::operator++ (int) 
{
    iterator result = *this;
    ++*this;
    return result;
}

template<class T>
bool AVL_Tree<T>::iterator::operator== (const AVL_Tree<T>::iterator& a) const
{
    return ((this->tree == a.tree) && (this->index == a.index));
}

template<class T>
bool AVL_Tree<T>::iterator::operator!= (const AVL_Tree<T>::iterator& a) const
{
    return !(*this == a);
}

//*****************const_iterator**********************
template<class T>
class AVL_Tree<T>::const_iterator
{
    explicit const_iterator(const AVL_Tree<T>* const tree, int index = 0);
    friend class AVL_Tree<T>;

    public:
    const_iterator() : tree(nullptr), index(0) {};
    const AVL_Tree<T>* tree;
    int index;
    const TreeNode<T>* node;
    const T& operator*() const;
    const_iterator& operator++();
    const_iterator operator++(int);
    bool operator==(const const_iterator& it) const;
    bool operator!=(const const_iterator& it) const;
    const_iterator(const const_iterator&) = default;
    const_iterator& operator=(const const_iterator&) = default;
    ~const_iterator() = default;
};

template<class T>
AVL_Tree<T>::const_iterator::const_iterator(const AVL_Tree<T>* const tree, int index) : tree(tree), index(index), node(tree->min) {}

template<class T>
typename AVL_Tree<T>::const_iterator AVL_Tree<T>::cbegin() const
{
    return const_iterator(this, 0);
}

template<class T>
typename AVL_Tree<T>::const_iterator AVL_Tree<T>::cend() const
{
    return const_iterator(this, this->size);
}

template<class T>
const T& AVL_Tree<T>::const_iterator::operator*() const
{
    if(index >= this->tree->size)
    {
        //throw exception
    }
    return this->node->getData();
}

template<class T>
typename AVL_Tree<T>::const_iterator& AVL_Tree<T>::const_iterator::operator++ () 
{
    ++index;
    
    node = tree->constFindNextPtr(node);
    return *this;
}

template<class T>
typename AVL_Tree<T>::const_iterator AVL_Tree<T>::const_iterator::operator++ (int) 
{
    const_iterator result = *this;
    ++*this;
    return result;
}

template<class T>
bool AVL_Tree<T>::const_iterator::operator== (const AVL_Tree<T>::const_iterator& a) const
{
    return ((this->tree == a.tree) && (this->index == a.index));
}

template<class T>
bool AVL_Tree<T>::const_iterator::operator!= (const AVL_Tree<T>::const_iterator& a) const
{
    return !(*this == a);
}

#endif //WET1_AVL_TREE_ITERATOR_H