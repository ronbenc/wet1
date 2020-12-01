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


};

//************non-class member functions' declarations***********


//************class member functions' implementations***********
template<class T>
AVL_Tree<T>::AVL_Tree(const TreeNode<T>& r)
{
    root = r;
}

template<class T>
AVL_Tree<T>::~AVL_Tree()
{
    if(!this->getLeft() && !this->getRight())
    {
        return;
    }
    if(!this->getLeft())
    {
        //AVL
    }

    delete this->root->getLeft();
    delete this->root->getRight();
}

//************non-class member functions' implementations***********






#endif //WET1_AVL_TREE_H