#ifndef TREENODE_H
#define TREENODE_H

#include <algorithm>
#include <iostream>
#include <cassert>
#include "Exceptions.h"

template<class T>
class TreeNode
{
    private:
    T data;
    TreeNode<T>* l;
    TreeNode<T>* r;
    TreeNode<T>* p;
    int height;

    public:

    explicit TreeNode(T = T(), TreeNode<T>* left = nullptr, TreeNode<T>* right = nullptr, TreeNode<T>* parent = nullptr);
    ~TreeNode() = default;
    bool isLeftSon();
    bool isRightSon();
    void heightCalc();
    int getBF();
    T& getData();
    TreeNode* getLeft();
    TreeNode* getRight();
    TreeNode* getParent();
    int getHeight();
    const T& getData() const;
    const TreeNode* getLeft() const;
    const TreeNode* getRight() const;
    const TreeNode* getParent() const;
    const int& getHeight() const;
    void setData(const T&);
    void setLeft(TreeNode<T>*);
    void setRight(TreeNode<T>*);
    void setParent(TreeNode<T>*);
    void setHeight(const int&);    
    static void print2DUtil(std::ostream& os, const TreeNode<T> *root, int space);
    static void print2D(std::ostream& os, const TreeNode<T> *root);    
};


//**********************non-class functions' and operators' declarations********************

template<class T>
bool operator== (const TreeNode<T>&, const TreeNode<T>&);

template<class T>
bool operator!= (const TreeNode<T>&, const TreeNode<T>&);

template<class T>
bool operator< (const TreeNode<T>&, const TreeNode<T>&);

template<class T>
bool operator> (const TreeNode<T>&, const TreeNode<T>&);

template<class T>
bool operator>= (const TreeNode<T>&, const TreeNode<T>&);

template<class T>
bool operator<= (const TreeNode<T>&, const TreeNode<T>&);

template<class T>
std::ostream& operator<<(std::ostream&, const TreeNode<T>&);



//**********************in-class functions' implementations**********************

template<class T>
TreeNode<T>::TreeNode(T input, TreeNode<T>* left, TreeNode<T>* right, TreeNode<T>* parent) : data(input), l(left), r(right), p(parent)
{
    this->heightCalc();
}

// template<class T>
// TreeNode<T>::~TreeNode()
// {
//     TreeNode<T>* parent = this->getParent();
//     if(parent)
//     {        
//         if(parent->getLeft() == this)
//         {
//             parent->setLeft(nullptr);
//         }
//         else 
//         {
//             parent->setRight(nullptr);
//         }
//     }    
// }

template<class T>
bool TreeNode<T>::isLeftSon()
{
    if(!this) {return false;}
    TreeNode<T>* parent = this->getParent();
    if(parent && (parent->getLeft() == this))
    {
        return true;
    }
    return false;
}

template<class T>
bool TreeNode<T>::isRightSon()
{
    if(!this) {return false;}
    TreeNode<T>* parent = this->getParent();
    if(parent && (parent->getRight() == this))
    {
        return true;
    }
    return false;
}

template<class T>
void TreeNode<T>::heightCalc()
{
    if(!this) {this->setHeight(-1);}
    else
    {
        int l_height = (this->getLeft() ? this->getLeft()->height : -1);
        int r_height = (this->getRight() ? this->getRight()->height : -1);
        this->setHeight(std::max(l_height, r_height) + 1);
    }
}

template<class T>
int TreeNode<T>::getBF()
{
    if(!this) {return 0;}
    int l_height = 0;
    int r_height = 0;
    if(!this->getLeft()) {l_height = -1;}
    else {l_height = this->getLeft()->getHeight();}
    if(!this->getRight()) {r_height = -1;}
    else {r_height = this->getRight()->getHeight();}
    return (l_height - r_height);
}

template<class T>
T& TreeNode<T>::getData()
{
    if(!this) 
    {
        throw IllegalArgument_TreeNode();
    }
    return this->data;
}
template<class T>
TreeNode<T>* TreeNode<T>::getLeft()
{
    if(!this) 
    {
        throw IllegalArgument_TreeNode();
    }
    return this->l;
}

template<class T>
TreeNode<T>* TreeNode<T>::getRight()
{
    if(!this) 
    {
        throw IllegalArgument_TreeNode();
    }
    return this->r;
}

template<class T>
TreeNode<T>* TreeNode<T>::getParent()
{
    if(!this) 
    {
        throw IllegalArgument_TreeNode();
    }
    return this->p;
}

template<class T>
int TreeNode<T>::getHeight()
{
    if(!this) 
    {
        throw IllegalArgument_TreeNode();
    }
    return this->height;
}

template<class T>
const T& TreeNode<T>::getData() const
{
    if(!this) 
    {
        throw IllegalArgument_TreeNode();
    }
    return this->data;
}

template<class T>
const TreeNode<T>* TreeNode<T>::getLeft() const
{
    if(!this) 
    {
        throw IllegalArgument_TreeNode();
    }
    return this->l;
}

template<class T>
const TreeNode<T>* TreeNode<T>::getRight() const
{
    if(!this) 
    {
        throw IllegalArgument_TreeNode();
    }
    return this->r;
}

template<class T>
const TreeNode<T>* TreeNode<T>::getParent() const
{
    if(!this) 
    {
        throw IllegalArgument_TreeNode();
    }
    return this->p;
}

template<class T>
const int& TreeNode<T>::getHeight() const
{
    if(!this) 
    {
        throw IllegalArgument_TreeNode();
    }
    return this->height;
}

template<class T>
void TreeNode<T>::setData(const T& data)
{
    if(!this) 
    {
        throw IllegalArgument_TreeNode();
    }
    this->data = data;
}

template<class T>
void TreeNode<T>::setLeft(TreeNode<T>* input)
{
    if(!this) 
    {
        throw IllegalArgument_TreeNode();
    }    
    this->l = input;
    if(input)
    {
        input->setParent(this);
    }    
    this->heightCalc();
}

template<class T>
void TreeNode<T>::setRight(TreeNode<T>* input)
{
    if(!this) 
    {
        throw IllegalArgument_TreeNode();
    }
    this->r = input;
    if(input)
    {
        input->setParent(this);
    } 
    this->heightCalc();
}

template<class T>
void TreeNode<T>::setParent(TreeNode<T>* input)
{
    if(!this) 
    {
        throw IllegalArgument_TreeNode();
    }
    this->p = input;
}

template<class T>
void TreeNode<T>::setHeight(const int& input)
{
    if(!this) 
    {
        throw IllegalArgument_TreeNode();
    }
    this->height = input;
}

//******************************non-member functions' implementations**************************

template<class T>
bool operator== (const TreeNode<T>& a, const TreeNode<T>& b)
{
    return (a.getData() == b.getData());
}

template<class T>
bool operator!= (const TreeNode<T>& a, const TreeNode<T>& b)
{
    return !(a == b);
}

template<class T>
bool operator< (const TreeNode<T>& a, const TreeNode<T>& b)
{
    return (a.getData() < b.getData());
}

template<class T>
bool operator> (const TreeNode<T>& a, const TreeNode<T>& b)
{
    return (a.getData () > b.getData());
}

template<class T>
bool operator>= (const TreeNode<T>& a, const TreeNode<T>& b)
{
    return (a.getData () >= b.getData());
}

template<class T>
bool operator<= (const TreeNode<T>& a, const TreeNode<T>& b)
{
    return (a.getData () <= b.getData());
}

template<class T>
void treePrint(std::ostream& os, const TreeNode<T>& root, int depth)
{
    if(!root) {return;}
    for(int i = 0 ; i < 128/(depth + 2) ; i++)
    {
        os << " ";
    }
    os << root.getData() << std::endl;
    depth++;
    treeprint(os, root->getLeft(), depth);
    treeprint(os, root->getLeft(), depth);
    depth--;

}

template<class T>
void TreeNode<T>::print2DUtil(std::ostream& os, const TreeNode<T> *root, int space)
{  
    if (!root) 
    {
        return;
    }
    space += 10;  
    print2DUtil(os, root->r, space);      
    os << std::endl;  
    for (int i = 10; i < space; i++) 
    {
        os << " ";  
    }
    os << root->getData() <<"\n";    
    print2DUtil(os, root->l, space);
}  
  
template<class T>
void TreeNode<T>::print2D(std::ostream& os, const TreeNode<T> *root)
{  
    print2DUtil(os, root, 0);  
}

#endif //TREENODE_H