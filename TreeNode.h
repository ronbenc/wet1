#ifndef TREENODE_H
#define TREENODE_H

#include <algorithm>
#include <iostream>
#include <cassert>

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
    ~TreeNode();
    void heightCalc();
    int getBF();
    T getData();
    TreeNode* getLeft();
    TreeNode* getRight();
    TreeNode* getParent();
    int& getHeight();
    const T getData() const;
    const TreeNode* getLeft() const;
    const TreeNode* getRight() const;
    const TreeNode* getParent() const;
    const int& getHeight() const;
    void setData(const T&);
    void setLeft(TreeNode<T>*);
    void setRight(TreeNode<T>*);
    void setParent(TreeNode<T>*);
    void setHeight(const int&);
    
    static void print2DUtil(TreeNode<T> *root, int space);
    static void print2D(TreeNode<T> *root);
    // TreeNode<T>* nodeSearch(T data) const;

    // static void searchKey(TreeNode<T>* &curr, T data, TreeNode* &parent);
    
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
std::ostream& operator<<(std::ostream&, const TreeNode<T>&);//checked, might change



//**********************in-class functions' implementations**********************

template<class T>
TreeNode<T>::TreeNode(T input, TreeNode<T>* left, TreeNode<T>* right, TreeNode<T>* parent)
{
    // T* tmp_data = new T(*input);
    // data = tmp_data;
    data = input;
    l = left;
    r = right;
    p = parent;
    this->heightCalc();
}

template<class T>
TreeNode<T>::~TreeNode()
{
    TreeNode<T>* parent = this->getParent();
    if(parent)
    {        
        if(parent->getLeft() == this)
        {
            parent->setLeft(nullptr);
        }
        else 
        {
            parent->setRight(nullptr);
        }
    }    
}


template<class T>
void TreeNode<T>::heightCalc()
{
    if (!this->getLeft() && !this->getRight()) {this->setHeight(0);}
    else if (!this->getLeft())
    {
        this->setHeight((this->getRight())->getHeight() + 1);
    }
    else if (!this->getRight())
    {
        this->setHeight((this->getLeft())->getHeight() + 1);
    }
    else
    {
        this->setHeight(std::max((this->getLeft())->getHeight(), (this->getRight())->getHeight()) + 1);
    }
}

template<class T>
int TreeNode<T>::getBF()
{
    return (this->getLeft()->getHeight() - this->getLeft()->getHeight());
}



template<class T>
T TreeNode<T>::getData()
{
    return this->data;
}
template<class T>
TreeNode<T>* TreeNode<T>::getLeft()
{
    return this->l;
}

template<class T>
TreeNode<T>* TreeNode<T>::getRight()
{
    return this->r;
}

template<class T>
TreeNode<T>* TreeNode<T>::getParent()
{
    return this->p;
}

template<class T>
int& TreeNode<T>::getHeight()
{
    return this->height;
}

// template<class T>
// const T* TreeNode<T>::getData() const
// {
//     return this->data;
// }

template<class T>
const TreeNode<T>* TreeNode<T>::getLeft() const
{
    return this->l;
}

template<class T>
const TreeNode<T>* TreeNode<T>::getRight() const
{
    return this->r;
}

template<class T>
const TreeNode<T>* TreeNode<T>::getParent() const
{
    return this->p;
}

template<class T>
const int& TreeNode<T>::getHeight() const
{
    return this->height;
}

template<class T>
void TreeNode<T>::setData(const T& data)
{
    this->data = data;
}

template<class T>
void TreeNode<T>::setLeft(TreeNode<T>* input)
{
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
    this->p = input;
}

template<class T>
void TreeNode<T>::setHeight(const int& input)
{
    this->height = input;
}

// template<class T>
// TreeNode<T>* TreeNode<T>::nodeSearch(T data) const
// {
//     if(!this)
//     {
//         return nullptr;
//     }
//     assert (this->getData);
//     if(*this->getData == data)
//     {
//         return this;
//     }
//     if(data < *this->getData())
//     {
//         return this->getLeft()->nodeSearch(data);
//     }
//     else
//     {
//         return this->getRight()->nodeSearch(data);
//     }
// }

// template<class T>
// void TreeNode<T>::nodeSearch(TreeNode<T>* &curr, T data, TreeNode<T>* &parent)
// {
//     while (curr != nullptr && curr->data != data)
//     {
//         parent = curr;    
//         if (data < curr->data)
//         {
//             curr = curr->left;
//         }            
//         else
//         {
//             curr = curr->right;
//         }            
//     }
// }

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
    return (a.getData () < b.getData());
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

//from internet - itay
template<class T>
void TreeNode<T>::print2DUtil(TreeNode<T> *root, int space)
{  
    if (!root) 
    {
        return;
    }
    space += 10;  
    print2DUtil(root->r, space);      
    std::cout << std::endl;  
    for (int i = 10; i < space; i++) 
    {
        std::cout << " ";  
    }
    std::cout << root->getData() <<"\n";    
    print2DUtil(root->l, space);
}  
  
template<class T>
void TreeNode<T>::print2D(TreeNode<T> *root)  
{  
    print2DUtil(root, 0);  
}  


#endif //TREENODE_H