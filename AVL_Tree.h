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

    public:    
    explicit AVL_Tree(TreeNode<T>* r = nullptr);
    ~AVL_Tree();    
    TreeNode<T>* getRoot();

    //should be private
    static TreeNode<T>* llrotation(TreeNode<T>* vertex);
    static TreeNode<T>* rrrotation(TreeNode<T>* vertex);
    static TreeNode<T>* lrrotation(TreeNode<T>* vertex);
    static TreeNode<T>* rlrotation(TreeNode<T>* vertex);
    TreeNode<T>* findMin();
    TreeNode<T>* findMax();    
    void insert(T data, TreeNode<T>* = nullptr);
    static bool parentSideCheck(TreeNode<T>* node);
    void insertNode(T data);
    TreeNode<T>* searchNode(T data);
    

};

template<class T>
std::ostream& operator<<(std::ostream& os, AVL_Tree<T>* tree)
{
    TreeNode<int>::print2D(os, tree->getRoot());
    return os;
}

template<class T>
AVL_Tree<T>::AVL_Tree(TreeNode<T>* r)
{
    if(!r) 
    {
        // root = new TreeNode<T>();
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


template<class T>
TreeNode<T>* AVL_Tree<T>::llrotation(TreeNode<T>* vertex)
{
    TreeNode<T>* new_root = vertex->getLeft();
    TreeNode<T>* prev_root = vertex;
    prev_root->setLeft(new_root->getRight());
    new_root->setRight(prev_root);
    return new_root;
}

// template<class T>
// TreeNode<T>* AVL_Tree<T>::llrotation(TreeNode<T>* vertex)
// {
//     TreeNode<T>* new_root = this->getRoot()->getLeft();
//     TreeNode<T>* prev_root = this->getRoot();
//     prev_root->setLeft(new_root->getRight());
//     new_root->setRight(prev_root);
//     return new_root;
// }

template <class T>
TreeNode<T>* AVL_Tree<T>::rrrotation(TreeNode<T>* vertex)
{
    TreeNode<T>* new_root = vertex->getRight();
    TreeNode<T>* prev_root = vertex;
    prev_root->setRight(new_root->getLeft());
    new_root->setLeft(prev_root);
    return new_root;
}

// template <class T>
// TreeNode<T>* AVL_Tree<T>::rrrotation()
// {
//     TreeNode<T>* new_root = this->getRoot()->getRight();
//     TreeNode<T>* prev_root = this->getRoot();
//     prev_root->setRight(new_root->getLeft());
//     new_root->setLeft(prev_root);
//     return new_root;
// }


template<class T>
TreeNode<T>* AVL_Tree<T>:: lrrotation(TreeNode<T>* vertex)
{
    TreeNode<T>* new_root = vertex->getLeft()->getRight();
    TreeNode<T>* prev_root = vertex;
    prev_root->getLeft()->setRight(new_root->getLeft());
    new_root->setLeft(prev_root->getLeft());
    prev_root->setLeft(new_root->getRight());
    new_root->setRight(prev_root);
    return new_root;
}

// template<class T>
// TreeNode<T>* AVL_Tree<T>:: lrrotation()
// {
//     TreeNode<T>* new_root = this->getRoot()->getLeft()->getRight();
//     TreeNode<T>* prev_root = this->getRoot();
//     prev_root->getLeft()->setRight(new_root->getLeft());
//     new_root->setLeft(prev_root->getLeft());
//     prev_root->setLeft(new_root->getRight());
//     new_root->setRight(prev_root);
//     return new_root;
// }

template<class T>
TreeNode<T>* AVL_Tree<T>::rlrotation(TreeNode<T>* vertex)
{
    TreeNode<T>* new_root = vertex->getRight()->getLeft();
    TreeNode<T>* prev_root = vertex;
    prev_root->getRight()->setLeft(new_root->getRight());
    new_root->setRight(prev_root->getRight());
    prev_root->setRight(new_root->getLeft());
    new_root->setLeft(prev_root);
    return new_root;
}


// template<class T>
// TreeNode<T>* AVL_Tree<T>::rlrotation()
// {
//     TreeNode<T>* new_root = this->getRoot()->getRight()->getLeft();
//     TreeNode<T>* prev_root = this->getRoot();
//     prev_root->getRight()->setLeft(new_root->getRight());
//     new_root->setRight(prev_root->getRight());
//     prev_root->setRight(new_root->getLeft());
//     new_root->setLeft(prev_root);
//     return new_root;
// }

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
			// vertex->getLeft()->setData(data);
			// vertex->getLeft()->setLeft(nullptr);
			// vertex->getLeft()->setRight(nullptr);
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
			vertex->setRight(new TreeNode<T>);
			vertex->getRight()->setData(data);
			vertex->getRight()->setRight(nullptr);
			vertex->getRight()->setLeft(nullptr);
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
		// this->root->setData(data);
		// this->root->setLeft(nullptr);
        // this->root->setRight(nullptr);
        // this->root->setParent(nullptr);
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
        if(vertex->getBF() == 2)
        {
            if(vertex->getLeft()->getBF() >= 0)
            {
                parent = vertex->getParent();
                new_root = llrotation(vertex);
                is_rotated = true;
            }
            else if(vertex->getLeft()->getBF() == -1)
            {
                parent = vertex->getParent();
                new_root = lrrotation(vertex);
                is_rotated = true;
            }
        }
        else if(vertex->getBF() == -2)
        {
            if(vertex->getRight()->getBF() <= 0)
            {
                parent = vertex->getParent();
                new_root = rrrotation(vertex);
                is_rotated = true;
            }
            else if(vertex->getRight()->getBF() == 1)
            {
                parent = vertex->getParent();
                new_root = rlrotation(vertex);
                is_rotated = true;
            }
        }
        if(is_rotated)
        {
            if(!parent)
            {
                new_root->setParent(nullptr);                
            }
            else
            {
                if(parentSideCheck(vertex))//vertex is a left son
                {
                    parent->setLeft(new_root);
                    break;//single rotation
                }
                else                        //vertex is a right son
                {
                    parent->setRight(new_root);
                    break;//single rotation
                }
            }
            this->root = new_root;
        }        
        vertex = vertex->getParent();
    }
    return;
}

//helper function that returns true if node is left son, false if right son
template <class T>
bool AVL_Tree<T>::parentSideCheck(TreeNode<T>* node)
{
    TreeNode<T>* parent = node->getParent();
    if(parent->getLeft() == node)
    {
        return true;
    }
    assert(parent->getRight() == node);
    return false;
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