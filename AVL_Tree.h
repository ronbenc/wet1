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
    TreeNode<T>* small;
    int size;


    public:
    
    AVL_Tree(TreeNode<T>* r = nullptr);
    ~AVL_Tree();    
    TreeNode<T>* getRoot();

    //should be private
    TreeNode<T>* llrotation();
    TreeNode<T>* rrrotation();
    TreeNode<T>* lrrotation();
    TreeNode<T>* rlrotation();
    TreeNode<T>* findMin();
    TreeNode<T>* findMax();
};


template<class T>
AVL_Tree<T>::AVL_Tree(TreeNode<T>* r)
{
    if(!r) {root = new TreeNode<T>();}
    else {root = r;}
    small = this->findMin();
}

template<class T>
AVL_Tree<T>::~AVL_Tree()
{    
    if(!this) {return;}
    delete this->getRoot()->getLeft();
    delete this->getRoot()->getRight();
    delete this->getRoot();
}

template <class T>
TreeNode<T>* AVL_Tree<T>::getRoot()
{
    return this->root;
}

template <class T>
TreeNode<T>* AVL_Tree<T>::findMin()
{
    TreeNode<T>* node = this->getRoot();
    while(node->getLeft())
    {        
        node = node->getLeft();
    }
    return node;
}

template <class T>
TreeNode<T>* AVL_Tree<T>::findMax()
{
    TreeNode<T>* node = this->getRoot();
    while(node->getRight())
    {        
        node = node->getRight();
    }
    return node;
}

template<class T>
TreeNode<T>* AVL_Tree<T>::llrotation()
{
    TreeNode<T>* new_root = this->getRoot()->getLeft();
    TreeNode<T>* prev_root = this->getRoot();
    prev_root->setLeft(new_root->getRight());
    new_root->setRight(prev_root);
    return new_root;
}

template <class T>
TreeNode<T>* AVL_Tree<T>::rrrotation()
{
    TreeNode<T>* new_root = this->getRoot()->getRight();
    TreeNode<T>* prev_root = this->getRoot();
    prev_root->setRight(new_root->getLeft());
    new_root->setLeft(prev_root);
    return new_root;
}

template<class T>
TreeNode<T>* AVL_Tree<T>:: lrrotation()
{
    TreeNode<T>* new_root = this->getRoot()->getLeft()->getRight();
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
    TreeNode<T>* new_root = this->getRoot()->getRight()->getLeft();
    TreeNode<T>* prev_root = this->getRoot();
    prev_root->getRight()->setLeft(new_root->getRight());
    new_root->setRight(prev_root->getRight());
    prev_root->setRight(new_root->getLeft());
    new_root->setLeft(prev_root);
    return new_root;
}

#endif //WET1_AVL_TREE_H


// template<class T>
// AVL_Tree<T>::AVL_Tree(const TreeNode<T>* r)
// {
//     TreeNode<T> tmp();
//     if(r)
//     {
//         root = &tmp;
//     }    
//     else
//     {
//         root = nullptr;
//     }    
// }

// template<class T>
// AVL_Tree<T>::~AVL_Tree()
// {    
    
//     delete this->getRoot();
//     // if(!this->getRoot()->getLeft() && !this->getRoot()->getRight())
//     // {
//     //     delete this->getRoot();
//     // }
//     // else if(!this->getRoot()->getLeft())
//     // {
//     //     // AVL_Tree toDelete(this->getRoot()->getRight());
//     //     // delete &toDelete;
//     //     delete this->getRoot()->getRight();
//     //     delete this->getRoot();
//     // }
//     // else if(!this->getRoot()->getRight())
//     // {
//     //     // AVL_Tree toDelete(this->getRoot()->getLeft());
//     //     // delete &toDelete;
//     //     delete this->getRoot()->getLeft();
//     //     delete this->getRoot();
//     // }
//     // else
//     // {
//     //     // AVL_Tree leftDelete(this->getRoot()->getLeft());
//     //     // delete &leftDelete;
//     //     // AVL_Tree rightDelete(this->getRoot()->getRight());
//     //     // delete &rightDelete;

//     //     delete this->getRoot()->getLeft();
//     //     delete this->getRoot()->getRight();
                
//     //     delete this->getRoot();
//     // }    
// }
