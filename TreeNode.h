#ifndef TREENODE_H
#define TREENODE_H

#include <algorithm>
#include <iostream>

template<class T>
class TreeNode
{
    private:
    T* data;
    TreeNode<T>* l;
    TreeNode<T>* r;
    TreeNode<T>* p;
    int height;

    public:

    // TreeNode() = delete;
    explicit TreeNode(T = T(), TreeNode<T>* left = nullptr, TreeNode<T>* right = nullptr, TreeNode<T>* parent = nullptr);//checked
    TreeNode(const TreeNode<T>& toCopy) : data(toCopy.data), l(toCopy.l), r(toCopy.r), p(toCopy.p), height(toCopy.height) {};//checked
    ~TreeNode();//checked - now changed, should check another time
    
    // TreeNode& operator= (const TreeNode&);
    void heightCalc();//checked    
    int getBF();
    T getData();
    TreeNode* getLeft();
    TreeNode* getRight();
    TreeNode* getParent();//checked
    int& getHeight();

    const T getData() const;//checked
    const TreeNode* getLeft() const;//checked
    const TreeNode* getRight() const;//checked
    const TreeNode* getParent() const;//checked
    const int& getHeight() const;//checked

    void setData(const T&);//checked
    void setLeft(TreeNode<T>*);//checked
    void setRight(TreeNode<T>*);//checked
    void setParent(TreeNode<T>*);//checked
    void setHeight(const int&);//checked - might not be necessary??
    

    // static void searchKey(TreeNode<T>* &curr, T data, TreeNode* &parent);
    
};


//**********************non-class functions' and operators' declarations********************

template<class T>
bool operator== (const TreeNode<T>&, const TreeNode<T>&);//checked

template<class T>
bool operator!= (const TreeNode<T>&, const TreeNode<T>&);//checked

template<class T>
bool operator< (const TreeNode<T>&, const TreeNode<T>&);//checked

template<class T>
bool operator> (const TreeNode<T>&, const TreeNode<T>&);//checked

template<class T>
bool operator>= (const TreeNode<T>&, const TreeNode<T>&);//checked

template<class T>
bool operator<= (const TreeNode<T>&, const TreeNode<T>&);//checked

template<class T>
std::ostream& operator<<(std::ostream&, const TreeNode<T>&);//checked, might change



//**********************in-class functions' implementations**********************

template<class T>
TreeNode<T>::TreeNode(T input, TreeNode<T>* left, TreeNode<T>* right, TreeNode<T>* parent)
{
    T* tmp_data = new T(input);
    data = tmp_data;
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
    if(!this->getLeft() && !this->getRight())
    {
        delete this->data;
    }
    else if(!this->getLeft())
    {
        delete this->data;
        delete this->getRight();
    }
    else if(!this->getRight())
    {
        delete this->data;
        delete this->getLeft();
    }
    else
    {
        delete this->data;
        delete this->getLeft();
        delete this->getRight();
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

// template<class T>
// TreeNode<T>& TreeNode<T>::operator=(const TreeNode& toCopy)
// {
//     this->data = toCopy.getData();
//     this->l = toCopy.getLeft();
//     this->r = toCopy.getRight();
//     this->height = toCopy.getHeight();
//     return this;
// }

template<class T>
T TreeNode<T>::getData()
{
    return *this->data;
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

template<class T>
const T TreeNode<T>::getData() const
{
    return *this->data;
}

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
// void TreeNode<T>::searchKey(TreeNode<T>* &curr, T data, TreeNode<T>* &parent)
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

template<class T>
std::ostream& operator<<(std::ostream& os, const TreeNode<T>& root)
{
    int depth = 0;
    treePrint(os, root, depth);

    

    // os << "node value is: " << treeNode.getData() << std::endl;
    // if(treeNode.getLeft())
    // {
    //     os << "left node value is: " << (*treeNode.getLeft()).getData() << std::endl;
    // }    
    // if(treeNode.getRight())
    // {
    //     os << "right node value is: " << (*treeNode.getRight()).getData() << std::endl;
    // }
    // os << "height: " << treeNode.getHeight() << std::endl;
    // return os;
}



#endif //TREENODE_H