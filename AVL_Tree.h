//********************************Generic AVL Tree:***************************************

// The data structure is an implementation of a genereic AVL Tree in which T is the generic type.

//***********Assumptions*************
// The following operators should be available: 
// operator<, operator>, operator<=, operator >= operator==, operator!= between two T objects
// operator=, operator<<(ostream&, T)

//***********Functionality*************
// The following data structure supports the follwing operations:

// Constructor of an AVL Tree, returns the tree by value, default root is null
//AVL_Tree();

// Constructor of an AVL Tree, destroys the tree recursively
//~AVL_Tree();    

//Insert given data to the tree
// void insertNode(T data);

//Remove given data from the tree
// void removeNode (T data);

//Returns true if a given data exists in the tree, false otherwise
//bool contains(T data);

//Print to os a given AVL Tree, supports concatenations
// std::ostream& operator<<(std::ostream& os, const AVL_Tree<T>& tree);

//The function returns an iterator to the minimal element in tree
// iterator AVL_Tree<T>::begin() const;
// const_iterator AVL_Tree<T>::cbegin() const;

//The function returns an iterator to the successor of maximal element in tree
// iterator AVL_Tree<T>::end() const; 
// const_iterator AVL_Tree<T>::cend() const; 

//***********Example of Use*************

// int main()
// {    
//     AVL_Tree<int> tree = AVL_Tree<int>();
//     tree.insertNode(0);
//     tree.insertNode(1);
//     tree.removeNode(0);
//     std::cout << tree;
//     return 0;
// }





#ifndef WET1_AVL_TREE_H
#define WET1_AVL_TREE_H

#include <cassert>
#include <algorithm>
#include "TreeNode.h"
#include "Exceptions.h"

template<class T>
class AVL_Tree
{
    private:
    TreeNode<T>* root;
    TreeNode<T>* min;
    int size;
    AVL_Tree(TreeNode<T>* r);
    
    void BalanceCheck(TreeNode<T>* leaf, bool single_rotate);
    TreeNode<T>* llrotation(TreeNode<T>* vertex);
    TreeNode<T>* rrrotation(TreeNode<T>* vertex);
    TreeNode<T>* lrrotation(TreeNode<T>* vertex);
    TreeNode<T>* rlrotation(TreeNode<T>* vertex);
    void insert(T data, TreeNode<T>* = nullptr);
    static void heightUpdate(TreeNode<T>* node);       
    TreeNode<T>* findMin() const;
    TreeNode<T>* findMax() const;   
    
    void deleteTree(TreeNode<T>* root);
    TreeNode<T>* findNextPtr(TreeNode<T>*) const;
    const TreeNode<T>* constFindNextPtr(const TreeNode<T>*) const;
    const TreeNode<T>* constFindPrevPtr(const TreeNode<T>*) const;
    TreeNode<T>* findPrevPtr(TreeNode<T>*) const;
    TreeNode<T>* searchNode(T data);
            
    public:
    AVL_Tree();
    ~AVL_Tree();
    void insertNode(T data);
    void removeNode(T data);
    bool contains(T data);
    TreeNode<T>* getRoot() const;   
    TreeNode<T>* getRoot();
    int getSize() const;

    class iterator;
    iterator begin() const;
    iterator end() const; 
    class const_iterator;
    const_iterator cbegin() const;
    const_iterator cend() const; 
};

template<class T>
std::ostream& operator<< (std::ostream& os, const AVL_Tree<T>& tree)
{
    TreeNode<T>::print2D(os, (&tree)->getRoot());
    return os;
}

template<class T>
AVL_Tree<T>::AVL_Tree(TreeNode<T>* r)
{
    assert(r);
    root = r;
    min = root;
    size = 1;
}

template <class T>
AVL_Tree<T>::AVL_Tree()
{
    root = nullptr;
    min = nullptr;
    size = 0;
}

template<class T>
AVL_Tree<T>::~AVL_Tree()
{    
    deleteTree(this->root);   
}

template<class T>
void AVL_Tree<T>::deleteTree(TreeNode<T>* tmp_root)
{
    if(!tmp_root) 
    {
        return;
    }
    // if(tmp_root == this->root)
    // {
    //     if(tmp_root->getParent())
    //     {
    //         if(tmp_root->isLeftSon())
    //         {
    //             tmp_root->getParent()->setLeft(nullptr);
    //         }
    //         else
    //         {
    //             assert(tmp_root->isRightSon());
    //             tmp_root->getParent()->setRight(nullptr);
    //         }            
    //     }
    //     return;
    // }
    deleteTree(tmp_root->getLeft());
    deleteTree(tmp_root->getRight());
    assert(tmp_root != nullptr);
    assert(tmp_root->getLeft() == nullptr && tmp_root->getRight() == nullptr);    
    TreeNode<T>* tmp_parent = tmp_root->getParent();
    if(tmp_parent)
    {
        if(tmp_root->isLeftSon())
        {
            tmp_parent->setLeft(nullptr);
        }
        else
        {
            assert(tmp_root->isRightSon());
            tmp_parent->setRight(nullptr);            
        }
    }
    delete tmp_root;
}

template <class T>
TreeNode<T>* AVL_Tree<T>::getRoot()
{
    if(!this)
    {
        throw IllegalArgument_AVL_Tree();
    }
    return this->root;
}

template <class T>
TreeNode<T>* AVL_Tree<T>::getRoot() const
{
    if(!this)
    {
        throw IllegalArgument_AVL_Tree();
    }
    return this->root;
}

template<class T>
int AVL_Tree<T>::getSize() const
{
    if(!this)
    {
        return 0;
    }
    return this->size;
}

template<class T>
TreeNode<T>* AVL_Tree<T>::llrotation(TreeNode<T>* vertex)
{
    assert(vertex);
    TreeNode<T>* new_root = vertex->getLeft();
    TreeNode<T>* prev_root = vertex;
    TreeNode<T>* prev_parent = vertex->getParent();
    prev_root->setLeft(new_root->getRight());
    new_root->setRight(prev_root);
    if(prev_parent)
    {
        if(prev_parent->getLeft() == vertex)
        {
            prev_parent->setLeft(new_root);
        }
        else
        {
            prev_parent->setRight(new_root);
        }
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
    assert(vertex);
    TreeNode<T>* new_root = vertex->getRight();
    TreeNode<T>* prev_root = vertex;
    TreeNode<T>* prev_parent = vertex->getParent();
    prev_root->setRight(new_root->getLeft());
    new_root->setLeft(prev_root);
    if(prev_parent)
    {
        if(prev_parent->getLeft() == vertex)
        {
            prev_parent->setLeft(new_root);
        }
        else
        {
            prev_parent->setRight(new_root);
        }
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
    assert(vertex);
    TreeNode<T>* new_root = vertex->getLeft()->getRight();
    TreeNode<T>* prev_root = vertex;
    TreeNode<T>* prev_parent = vertex->getParent();
    prev_root->getLeft()->setRight(new_root->getLeft());
    new_root->setLeft(prev_root->getLeft());
    prev_root->setLeft(new_root->getRight());
    new_root->setRight(prev_root);
    if(prev_parent)
    {
        if(prev_parent->getLeft() == vertex)
        {
            prev_parent->setLeft(new_root);
        }
        else
        {
            prev_parent->setRight(new_root);
        }
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
    assert(vertex);
    TreeNode<T>* new_root = vertex->getRight()->getLeft();
    TreeNode<T>* prev_root = vertex;
    TreeNode<T>* prev_parent = vertex->getParent();
    prev_root->getRight()->setLeft(new_root->getRight());
    new_root->setRight(prev_root->getRight());
    prev_root->setRight(new_root->getLeft());
    new_root->setLeft(prev_root);
    if(prev_parent)
    {
        if(prev_parent->getLeft() == vertex)
        {
            prev_parent->setLeft(new_root);
        }
        else
        {
            prev_parent->setRight(new_root);
        }
    }
    else
    {
        this->root = new_root;
        new_root->setParent(nullptr);
    }
    return new_root;
}

template <class T>
TreeNode<T>* AVL_Tree<T>::findMin() const
{
    assert(this);
    TreeNode<T>* node = this->getRoot();
    while(node->getLeft())
    {        
        node = node->getLeft();
    }
    return node;
}

template <class T>
TreeNode<T>* AVL_Tree<T>::findMax() const
{
    assert(this);
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
	assert(vertex);
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
    if(!this)
    {
        throw IllegalArgument_AVL_Tree();
    }
    if(root) 
    {
        this->insert(data, root);
        TreeNode<T>* curr = this->searchNode(data);
        if((*curr) < (*this->min))
        {
            min = this->searchNode(data);
            assert (min);
        }
    }
    else
    {
		this->root = new TreeNode<T>(data);
        this->min = root;
    }
    this->size++;
    TreeNode<T> *vertex = this->searchNode(data);
    assert(vertex);
    this->BalanceCheck(vertex, true);
}

template <class T>
void AVL_Tree<T>::BalanceCheck(TreeNode<T>* leaf, bool single_rotate)
{
    assert(this && leaf);
    TreeNode<T>* vertex = leaf;
    this->heightUpdate(leaf);
    while(vertex)
    {
        if(vertex->getBF() == 2)
        {
            if(vertex->getLeft()->getBF() >= 0)
            {
                this->llrotation(vertex);
                if(single_rotate)
                {
                    break;
                }                
            }
            else if(vertex->getLeft()->getBF() == -1)
            {
                this->lrrotation(vertex);
                if(single_rotate)
                {
                    break;
                }                
            }
        }
        else if(vertex->getBF() == -2)
        {
            if(vertex->getRight()->getBF() <= 0)
            {
                this->rrrotation(vertex);
                if(single_rotate)
                {
                    break;
                }                
            }
            else if(vertex->getRight()->getBF() == 1)
            {
                this->rlrotation(vertex);
                if(single_rotate)
                {
                    break;
                }                
            }
        }
        vertex = vertex->getParent();
    }    
    this->heightUpdate(leaf);
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
    assert(this);
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
    return nullptr;
}

template<class T>
void AVL_Tree<T>::removeNode(T data)
{
    assert(this);
    TreeNode<T>* toDelete = this->searchNode(data);
    if (!toDelete) {return;}
    TreeNode<T>* toDelete_parent = toDelete->getParent();
    TreeNode<T>* toBalance = nullptr;
    
    //check if updating minimal element is needed
    if(data == min->getData())
    {
        min = this->findNextPtr(min);
    }

    //case 1: has no children
    if(!toDelete->getLeft() && !toDelete->getRight())   
    {
        if(toDelete != root)
        {
            assert(toDelete_parent);
            toBalance = toDelete_parent;
            if(toDelete->isLeftSon())
            {
                toDelete_parent->setLeft(nullptr);
            }
            else
            {
                toDelete_parent->setRight(nullptr);
            }
        }
        else
        {
            this->root = nullptr;
        }    
        delete toDelete;
    }
    //case 2: has two children
    else if(toDelete->getLeft() && toDelete->getRight()) 
    {
        TreeNode<T>* node = toDelete->getRight();
        while(node->getLeft())
        {
            node = node->getLeft();
        }
        TreeNode<T>* successor = node; //find the desired node to place instead of the deleted node
        successor->setLeft(toDelete->getLeft());    
        if(successor->getParent() != toDelete) // successor is not son of toDelete
        {
            assert(successor->getParent());
            toBalance = successor->getParent();
            successor->getParent()->setLeft(successor->getRight());
            successor->setRight(toDelete->getRight());
        }
        else
        {
            toBalance = successor;
        }
        if(toDelete_parent)
        {
            if(toDelete->isLeftSon())
            {
                toDelete_parent->setLeft(successor);
            }
            else
            {
                toDelete_parent->setRight(successor);
            }
        }
        else
        {
            root = successor;
            root->setParent(nullptr);
        }        
        delete toDelete;
    }
    //case 3: has one child
    else 
    {
        TreeNode<T>* child = (toDelete->getLeft() ? toDelete->getLeft() : toDelete->getRight());
        assert(child);
        if(toDelete != root)
        {
            if(toDelete->isLeftSon())
            {
                toDelete_parent->setLeft(child);
            }
            else
            {
                toDelete_parent->setRight(child);
            }
            delete toDelete;
            toBalance = toDelete_parent;
        }
        else
        {
            root = child;
            child->setParent(nullptr);
            delete toDelete;
        }
    }
    size--;
    if(toBalance)
    {
        this->BalanceCheck(toBalance, false);
    }    
}

template<class T>
bool AVL_Tree<T>::contains(T data)
{
    return (this->searchNode(data) ? true : false);
}

//Helper function that returns a ptr to the next node (in order)
template<class T>
const TreeNode<T>* AVL_Tree<T>::constFindNextPtr(const TreeNode<T>* node) const
{
    assert(node);
    if(node->getRight()) // if node has a right son, find min of sub-tree rooted by right son
    {
        const TreeNode<T>* sub_root = node->getRight();
        while(sub_root->getLeft())
        {
            sub_root = sub_root->getLeft();
        }
        return sub_root;        
    }
    else if(node->getParent())
    {
        if(node->getParent()->getLeft() == node) //if node is a left son
        {
            return node->getParent();
        }
        else //if node is a right son
        {
            while(node->getParent() && node->getParent()->getLeft() != node)
            {
                node = node->getParent();
            }
            return node->getParent();
        }
    }        
    else //node is max
    {
        return nullptr;
    }
}

//helper function that returns a ptr to the previous node (in order)
template<class T>
TreeNode<T>* AVL_Tree<T>::findNextPtr(TreeNode<T>* node) const
{
    assert(node);
    if(node->getRight()) // if node has a right son, find min of sub-tree rooted by right son
    {
        TreeNode<T>* sub_root = node->getRight();
        while(sub_root->getLeft())
        {
            sub_root = sub_root->getLeft();
        }
        return sub_root;        
    }
    else if(node->getParent())
    {
        if(node->getParent()->getLeft() == node) //if node is a left son
        {
            return node->getParent();
        }
        else //if node is a right son
        {
            while(node->getParent() && node->getParent()->getLeft() != node)
            {
                node = node->getParent();
            }
            return node->getParent();
        }
    }        
    else //node is max
    {
        return nullptr;
    }
}

//Helper function that returns a ptr to the next node (in order)
template<class T>
const TreeNode<T>* AVL_Tree<T>::constFindPrevPtr(const TreeNode<T>* node) const
{
    assert(node);
    if(node->getLeft()) // if node has a left son, find max of sub-tree rooted by left son
    {
        TreeNode<T>* sub_root = node->getLeft();
        while(sub_root->getRight())
        {
            sub_root = sub_root->getRight();
        }
        return sub_root;        
    }
    else if(node->getParent())
    {
        if(node->getParent()->getRight() == node) //if node is a right son
        {
            return node->getParent();
        }
        else //if node is a left son
        {
            while(node->getParent() && node->getParent()->getRight() != node)
            {
                node = node->getParent();
            }
            return node->getParent();
        }
    }        
    else //node is min
    {
        return nullptr;
    }
}

//Helper function that returns a ptr to the previous node (in order)
template<class T>
TreeNode<T>* AVL_Tree<T>::findPrevPtr(TreeNode<T>* node) const
{
    assert(node);
    if(node->getLeft()) // if node has a left son, find max of sub-tree rooted by left son
    {
        TreeNode<T>* sub_root = node->getLeft();
        while(sub_root->getRight())
        {
            sub_root = sub_root->getRight();
        }
        return sub_root;        
    }
    else if(node->getParent())
    {
        if(node->getParent()->getRight() == node) //if node is a right son
        {
            return node->getParent();
        }
        else //if node is a left son
        {
            while(node->getParent() && node->getParent()->getRight() != node)
            {
                node = node->getParent();
            }
            return node->getParent();
        }
    }        
    else //node is min
    {
        return nullptr;
    }
}

#endif //WET1_AVL_TREE_H