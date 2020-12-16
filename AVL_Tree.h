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

template<class T>
class AVL_Tree
{
    private:
    TreeNode<T>* root;
    TreeNode<T>* min;
    int size;
    AVL_Tree(TreeNode<T>* r);//used to be public - itay 161220 debug
    
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
    // AVL_Tree(TreeNode<T>* r);
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
    // if(!r) 
    // {
    //     root = nullptr;
    //     min = nullptr;
    //     size = 0;        
    // }
    // else 
    // {
        root = r;
        min = root;
        size = 1;
    // }
}

//itay check if caued proiblem 161220 1647
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
void AVL_Tree<T>::deleteTree(TreeNode<T>* root)
{
    if(!root) {return;}
    deleteTree(root->getLeft());
    deleteTree(root->getRight());
    delete root;    
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
int AVL_Tree<T>::getSize() const
{
    return this->size;
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
    TreeNode<T>* curr = this->searchNode(data);
    if (!curr) {return;}
    TreeNode<T>* curr_parent = curr->getParent();
    TreeNode<T>* toBalance = nullptr;
    if(data == min->getData())
    {
        min = min->getParent();
    }
    if(!curr->getLeft() && !curr->getRight())   //case 1: has no children
    {
        if(curr != root) //if curr is not root, set parent's child ptr to null
        {
            toBalance = curr_parent;
        }
        else //if curr is root, set root to null
        {
            this->root = nullptr;
        }        
        delete curr;
    }
    else if(curr->getLeft() && curr->getLeft()) //case 2: has two children
    {
        TreeNode<T>* node = curr->getRight();
        while(node->getLeft())
        {
            node = node->getLeft();
        }
        TreeNode<T>* successor = node; //find the desired node to switch with deleted node
        T val = successor->getData();
        curr->setData(val); //set data in the node which was removed to desired data
        toBalance = curr;
        //delete successor and it's right child (successor has only 1 right child at most, and child is a leaf)
        delete successor->getRight();
        delete successor;                
    }
    else // case 3: has one child
    {
        TreeNode<T>* child = (curr->getLeft() ? curr->getLeft() : curr->getRight());
        if(curr != root)
        {
            if(curr == curr_parent->getLeft())
            {
                delete curr;
                curr_parent->setLeft(child);
            }
            else
            {
                delete curr;
                curr_parent->setRight(child);
            }
            toBalance = curr_parent;
        }
        else
        {
            delete curr;
            root = child;
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

template<class T>
const TreeNode<T>* AVL_Tree<T>::constFindNextPtr(const TreeNode<T>* node) const
{
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

template<class T>
TreeNode<T>* AVL_Tree<T>::findNextPtr(TreeNode<T>* node) const
{
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

template<class T>
const TreeNode<T>* AVL_Tree<T>::constFindPrevPtr(const TreeNode<T>* node) const
{
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

template<class T>
TreeNode<T>* AVL_Tree<T>::findPrevPtr(TreeNode<T>* node) const
{
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