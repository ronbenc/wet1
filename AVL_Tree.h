#ifndef WET1_AVL_TREE_H
#define WET1_AVL_TREE_H

#include <cassert>
#include <algorithm>
#include "TreeNode.h"

template<class T>
class AVL_Tree
{
    public:
    TreeNode<T> root;

    //******************constructors & destructors*****************
    AVL_Tree(const TreeNode<T>& r = TreeNode<T>());
    ~AVL_Tree();
    
    //************class member functions' declarations***********
    TreeNode<T>* getRoot();

};

//************non-class member functions' declarations***********


//************class member functions' implementations***********
template<class T>
AVL_Tree<T>::AVL_Tree(const TreeNode<T>& r)
{
    TreeNode<T> r1 = r;
    root = r1;
}

template<class T>
AVL_Tree<T>::~AVL_Tree()
{    
    if(!this->getRoot()->getLeft() && !this->getRoot()->getRight())
    {
        delete this->getRoot();
    }
    else if(!this->getRoot()->getLeft())
    {
        AVL_Tree toDelete(*this->getRoot()->getLeft());
        delete this->getRoot();
        delete &toDelete;
    }
    else if(!this->getRoot()->getRight())
    {
        AVL_Tree toDelete(*this->getRoot()->getRight());
        delete this->getRoot();
        delete &toDelete;        
    }
    else
    {
        AVL_Tree rightDelete(*this->getRoot()->getLeft());
        AVL_Tree leftDelete(*this->getRoot()->getRight());
        delete this->getRoot();
        delete &leftDelete;
        delete &rightDelete;        
    }    
}

template <class T>
TreeNode<T>* AVL_Tree<T>::getRoot()
{
    return &this->root;
}

//************non-class member functions' implementations***********






#endif //WET1_AVL_TREE_H