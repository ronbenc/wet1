#ifndef TREENODE_H
#define TREENODE_H

#include <algorithm>
#include <iostream>

template<class T>
class TreeNode
{
    private:
    T data;
    TreeNode<T>* l;
    TreeNode<T>* r;
    int height;

    public:

    //***********constructors, destuctor**********
    // TreeNode() = delete;
    explicit TreeNode(const T& = T(), TreeNode<T>* left = nullptr, TreeNode<T>* right = nullptr);//checked
    TreeNode(const TreeNode<T>& toCopy) : data(toCopy.data), l(toCopy.l), r(toCopy.r), height(toCopy.height) {};//checked
    ~TreeNode();//checked
    
    // TreeNode& operator= (const TreeNode&);


    //****************getters and setters***********
    void heightCalc();//checked
    const T& getData() const;//checked
    const TreeNode* getLeft() const;//checked
    const TreeNode* getRight() const;//checked
    const int& getHeight() const;//checked

    void setData(const T&);//checked
    void setLeft(TreeNode<T>*);//checked
    void setRight(TreeNode<T>*);//checked
    void setHeight(const int&);//checked - might not be necessary??
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
TreeNode<T>::TreeNode(const T& input, TreeNode<T>* left, TreeNode<T>* right)
{
    data = input;
    l = left;
    r = right;
    this->heightCalc();
    
}

template<class T>
TreeNode<T>::~TreeNode()
{
    if(!this->getLeft() && !this->getRight())
    {
        //do something (or actually nothing needed)
    }
    else if(!this->getLeft())
    {
        delete this->getRight();
    }
    else if(!this->getRight())
    {
        delete this->getLeft();
    }
    else
    {
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
const T& TreeNode<T>::getData() const
{
    return this->data;
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
    this->heightCalc();
}

template<class T>
void TreeNode<T>::setRight(TreeNode<T>* input)
{
    this->r = input;
    this->heightCalc();
}

template<class T>
void TreeNode<T>::setHeight(const int& input)
{
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
std::ostream& operator<<(std::ostream& os, const TreeNode<T>& treeNode)
{
    os << "node value is: " << treeNode.getData() << std::endl;
    if(treeNode.getLeft())
    {
        os << "left node value is: " << (*treeNode.getLeft()).getData() << std::endl;
    }    
    if(treeNode.getRight())
    {
        os << "right node value is: " << (*treeNode.getRight()).getData() << std::endl;
    }
    os << "height: " << treeNode.getHeight() << std::endl;
    return os;
}



#endif //TREENODE_H