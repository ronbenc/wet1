//********************************Generic AVL Tree iterator & const_iterator IN ORDER scan:***************************************

// The data structure is an implementation of a genereic AVL Tree iterator & const_iterator scanning tree in-order, in which T is the generic type.

//***********Assumptions*************
// The following operators should be available: 
// No additional assumptions assumed, other than the assumptions in AVL Tree

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
    iterator(const AVL_Tree<T>* tree, int index);
    friend class AVL_Tree<T>;

    public:
    const AVL_Tree<T>* tree; //used to be private
    int index; //used to be private
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
AVL_Tree<T>::iterator::iterator(const AVL_Tree<T>* tree, int index) : tree(tree), index(index) {}

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
    if(index >= this->tree->size)
    {
        //throw exception
    }
    TreeNode<T>* tmp = this->tree->findMin();
    for(int i = 0 ; i < index ; i++)
    {
        tmp = this->tree->findNextPtr(tmp);
    }
    return tmp->getData();
}

template<class T>
typename AVL_Tree<T>::iterator& AVL_Tree<T>::iterator::operator++ () 
{
    ++index;
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
    const_iterator(const AVL_Tree<T>* const tree, int index);
    friend class AVL_Tree<T>;

    public:
    // Assumptions: non for all iterator's methods    
    const AVL_Tree<T>* const tree; //used to be private
    int index; //used to be private
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
AVL_Tree<T>::const_iterator::const_iterator(const AVL_Tree<T>* const tree, int index) : tree(tree), index(index) {}

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
        std::cout << "illegal access to undefined node" << std::endl;
    }
    TreeNode<T>* tmp = this->tree->findMin();
    for(int i = 0 ; i < index ; i++)
    {
        tmp = this->tree->findNextPtr(tmp);
    }
    return tmp->getData();
}

template<class T>
typename AVL_Tree<T>::const_iterator& AVL_Tree<T>::const_iterator::operator++ () 
{
    ++index;
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