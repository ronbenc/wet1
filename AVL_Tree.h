#ifndef WET1_AVL_TREE_H
#define WET1_AVL_TREE_H

#include <cassert>
#include <algorithm>
#include "TreeNode.h"

template<class T>
class AVL_Tree
{
    private:
    TreeNode<T>* root;
    TreeNode<T>* llrotation();
    TreeNode<T>* rrrotation();
    TreeNode<T>* lrrotation();
    TreeNode<T>* rlrotation();

    public:
    
    AVL_Tree(const TreeNode<T>& r = TreeNode<T>());
    ~AVL_Tree();    
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

template<class T>
TreeNode<T>* AVL_Tree<T>::llrotation()
{
    TreeNode<T>* new_root = this->getRoot()->getLeft();
    TreeNode<T>* prev_root = this->getRoot();
    prev_root->setLeft(new_root->getRight())
    new_root->setRight(prev_root);
    return new_root;
}

template <class T>
TreeNode<T>* AVL_Tree<T>::rrrotation()
{
    TreeNode<T>* new_root = this->getRoot()->getRight();
    TreeNode<T>* prev_root = this->getRoot();
    prev_root->setRight(new_root->getLeft())
    new_root->setLeft(prev_root);
    return new_root;
}

template<class T>
TreeNode<T>* AVL_Tree<T>:: lrrotation()
{
    TreeNode<T>* new_root = this->getLeft()->getRight();
    TreeNode<T>* prev_root = this->getRoot();
    prev_root->getLeft()->setRight(new_root->getLeft());
    new_root->setLeft(prev_root->getLeft());
    prev_root->setLeft(new_root->getRight());
    new_root->setRight(prev_root);
    return new_root;
}

template<class T>
TreeNode<T>* AVL_Tree<T>::rlrotation()
{
    TreeNode<T>* new_root = this->getRight()->getLeft();
    TreeNode<T>* prev_root = this->getRoot();
    prev_root->getRight()->setLeft(new_root->getRight());
    new_root->setRight(prev_root->getRight());
    prev_root->setRight(new_root->getLeft());
    new_root->setLeft(prev_root);
    return new_root;
}








#endif //WET1_AVL_TREE_H