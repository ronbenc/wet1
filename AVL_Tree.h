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
    TreeNode<T>* insert(T, TreeNode<T>*);
    void BTSearchParent(TreeNode<T>* toInsert, TreeNode<T>* parent);

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

// template <class T>
// TreeNode<T>* AVL_Tree<T>::insert(T data, TreeNode<T>* toInsert)
// {
//     if(!toInsert)
//     {
//         toInsert = new TreeNode<T>(data);
//     }
//     TreeNode<T>* new_parent = nullptr;
//     BTSearchParent(toInsert, new_parent)
//     TreeNode<T>* tmp_root = this->getRoot();    
//     //go all the way up nd heightCalc, balance, rotations
    
// }

//helper function that assigns by reference into 'parent' variable,
//the parent of a node which is to be inserted into binary tree
template<class T>
void AVL_Tree<T>::BTSearchParent(TreeNode<T>* toInsert, TreeNode<T>* parent)
{
    TreeNode<T>* tmp_root = this->getRoot();
    if(toInsert == tmp_root)     //case 1: we found the data we wanted to insert
    {
        parent = tmp_root;
    }
    else if(toInsert < tmp_root) //case 2: our data is smaller than current data
    {
        if(!tmp_root->getLeft())
        {
            AVL_Tree<T> subTree(tmp_root->getLeft());
            subTree.BTSearchParent(toInsert, parent);
        }
        else
        {
            parent = tmp_root;
        }        
    }
    else if (toInsert > tmp_root) //case 3: our data is larger than current data
    {
        if(!tmp_root->getRight())
        {
            AVL_Tree<T> subTree(tmp_root->getRight());
            subTree.BTSearchParent(toInsert, parent);
        }
        else
        {
            parent = tmp_root;
        }
    }
}


#endif //WET1_AVL_TREE_H

//  while(1)
//     {
//         if(toInsert == tmp_root)
//         {
//             return tmp_root;
//         }
//         if(toInsert < tmp_root)
//         {
//             if(!tmp_root->getLeft())
//             {
//                 toInsert->setParent(tmp_root);                
//                 break;
//             }
//             else
//             {
//                 tmp_root = tmp_root->getLeft();
//             }            
//         }
//         else if(toInsert > tmp_root)
//         {
//             if(!tmp_root->getRight())
//             {
//                 toInsert->setParent(tmp_root);                
//                 break;
//             }
//             else
//             {
//                 tmp_root = tmp_root->getRight();
//             }
//         }
//     }