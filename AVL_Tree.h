//**************Generic AVL Tree:******************

// The data structure is an implementation of a genereic
// AVL Tree, which supports the follwing operations:

// Constructor of an AVL Tree, returns the tree by value, default root is null
//     AVL_Tree(TreeNode<T>* r = nullptr);

// Constructor of an AVL Tree, destroys the tree recursively
//     ~AVL_Tree();    

//Insert given data to the tree
// void insertNode(T data);

//Remove given data from the tree
// void removeNode (T data);

//Print to os a given AVL Tree, supports concatenations
// std::ostream& operator<<(std::ostream& os, const AVL_Tree<T>& tree);

// An example of using the data structure:

// int main()
// {    
//     AVL_Tree<int> tree = AVL_Tree<int>();
//     tree.insertNode(0);
//     tree.insertNode(1);
//     tree.insertNode(2);
//     tree.insertNode(-1);
//     tree.insertNode(-2);
//     std::cout << tree;
//     return 0;
// }


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
    TreeNode<T>* min;
    int size;

    void singleBalanceCheck(TreeNode<T>* leaf);
    TreeNode<T>* llrotation(TreeNode<T>* vertex);
    TreeNode<T>* rrrotation(TreeNode<T>* vertex);
    TreeNode<T>* lrrotation(TreeNode<T>* vertex);
    TreeNode<T>* rlrotation(TreeNode<T>* vertex);
    void insert(T data, TreeNode<T>* = nullptr);
    static void heightUpdate(TreeNode<T>* node);
    TreeNode<T>* searchNode(T data);
    

    public:    
    AVL_Tree(TreeNode<T>* r = nullptr);
    ~AVL_Tree();    
    TreeNode<T>* getRoot();
    TreeNode<T>* getRoot() const;
    TreeNode<T>* findMin();
    TreeNode<T>* findMax();    
    void insertNode(T data);
    void removeNode(T data);
};

template<class T>
std::ostream& operator<<(std::ostream& os, const AVL_Tree<T>& tree)
{
    TreeNode<int>::print2D(os, (&tree)->getRoot());
    return os;
}

template<class T>
AVL_Tree<T>::AVL_Tree(TreeNode<T>* r)
{
    if(!r) 
    {
        root = nullptr;
        min = nullptr;
        size = 0;        
    }
    else 
    {
        root = r;
        min = root;
        size = 1;
    }
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
TreeNode<T>* AVL_Tree<T>::getRoot() const
{
    return this->root;
}

template<class T>
TreeNode<T>* AVL_Tree<T>::llrotation(TreeNode<T>* vertex)
{
    TreeNode<T>* new_root = vertex->getLeft();
    TreeNode<T>* prev_root = vertex;
    TreeNode<T>* prev_parent = vertex->getParent();
    prev_root->setLeft(new_root->getRight());
    new_root->setRight(prev_root);
    if(prev_parent)
    {
        prev_parent->setLeft(new_root);
    }
    else
    {
        this->root = new_root;
        new_root->setParent(nullptr);
    }    
    return new_root;
}

template <class T>
TreeNode<T>* AVL_Tree<T>::rrrotation(TreeNode<T>* vertex)
{
    TreeNode<T>* new_root = vertex->getRight();
    TreeNode<T>* prev_root = vertex;
    TreeNode<T>* prev_parent = vertex->getParent();
    prev_root->setRight(new_root->getLeft());
    new_root->setLeft(prev_root);
    if(prev_parent)
    {
        prev_parent->setRight(new_root);
    }
    else
    {
        this->root = new_root;
        new_root->setParent(nullptr);
    }
    return new_root;
}

template<class T>
TreeNode<T>* AVL_Tree<T>:: lrrotation(TreeNode<T>* vertex)
{
    TreeNode<T>* new_root = vertex->getLeft()->getRight();
    TreeNode<T>* prev_root = vertex;
    TreeNode<T>* prev_parent = vertex->getParent();
    prev_root->getLeft()->setRight(new_root->getLeft());
    new_root->setLeft(prev_root->getLeft());
    prev_root->setLeft(new_root->getRight());
    new_root->setRight(prev_root);
    if(prev_parent)
    {
        prev_parent->setLeft(new_root);
    }
    else
    {
        this->root = new_root;
        new_root->setParent(nullptr);
    }
    return new_root;
}

template<class T>
TreeNode<T>* AVL_Tree<T>::rlrotation(TreeNode<T>* vertex)
{
    TreeNode<T>* new_root = vertex->getRight()->getLeft();
    TreeNode<T>* prev_root = vertex;
    TreeNode<T>* prev_parent = vertex->getParent();
    prev_root->getRight()->setLeft(new_root->getRight());
    new_root->setRight(prev_root->getRight());
    prev_root->setRight(new_root->getLeft());
    new_root->setLeft(prev_root);
    if(prev_parent)
    {
        prev_parent->setRight(new_root);
    }
    else
    {
        this->root = new_root;
        new_root->setParent(nullptr);
    }
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

template<class T>
void AVL_Tree<T>::insert(T data, TreeNode<T>* vertex)
{
	if(data == vertex->getData())
    {
        return;
    }
    else if(data < vertex->getData())
    {
		if(vertex->getLeft())
        {
			insert(data, vertex->getLeft());
		}
        else
        {
			vertex->setLeft(new TreeNode<T>(data));
            this->min = vertex;
        }
	}
    else if(data > vertex->getData())
    {
		if(vertex->getRight())
        {
			insert(data, vertex->getRight());
		}
        else
        {
			vertex->setRight(new TreeNode<T>(data));
		}
	}
}

template<class T>
void AVL_Tree<T>::insertNode(T data)
{
    if(root) 
    {
        this->insert(data, root);
    }
    else
    {
		this->root = new TreeNode<T>(data);
        this->min = root;
    }
    this->size++;
    TreeNode<T> *vertex = this->searchNode(data);
    assert(vertex);
    this->singleBalanceCheck(vertex);
}

template <class T>
void AVL_Tree<T>::singleBalanceCheck(TreeNode<T>* leaf)
{
    TreeNode<T>* vertex = leaf;
    TreeNode<T>* new_root = nullptr;
    TreeNode<T>* parent = nullptr;
    bool is_rotated = false;
    while(vertex)
    {
        parent = vertex->getParent();
        if(vertex->getBF() == 2)
        {
            if(vertex->getLeft()->getBF() >= 0)
            {
                TreeNode<T>* rot_result = this->llrotation(vertex);
                break;//single rotation
            }
            else if(vertex->getLeft()->getBF() == -1)
            {
                new_root = this->lrrotation(vertex);
                break;//single rotation
            }
        }
        else if(vertex->getBF() == -2)
        {
            if(vertex->getRight()->getBF() <= 0)
            {
                TreeNode<T>* rot_result = this->rrrotation(vertex);
                break;//single rotation
            }
            else if(vertex->getRight()->getBF() == 1)
            {
                new_root = this->rlrotation(vertex);
                break;//single rotation
            }
        }
        this->heightUpdate(leaf);
        vertex = vertex->getParent();
    }    
}

template <class T>
void AVL_Tree<T>::heightUpdate(TreeNode<T>* node)
{
    TreeNode<T>* tmp = node;
    while(tmp)
    {
        tmp->heightCalc();
        tmp = tmp->getParent();        
    }
}

template <class T>
TreeNode<T>* AVL_Tree<T>::searchNode(T data)
{
    TreeNode<T>* node_ptr = this->getRoot();
    while (node_ptr)
    {
        if (data == node_ptr->getData())
        {
            return node_ptr;
        }    
        else if (data < node_ptr->getData())
        {   
            node_ptr = node_ptr->getLeft();
        }            
        else
        {   
            node_ptr = node_ptr->getRight();
        }            
    }
    return nullptr; //not found in tree
}

#endif //WET1_AVL_TREE_H