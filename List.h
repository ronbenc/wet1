#ifndef WET1_LIST_H
#define WET1_LIST_H
#include <cassert>

template <class T>
class Node
{
public:
    T data;
    Node* next;
    Node* previous;

    Node(const T& data) : data(data), next(nullptr), previous(nullptr) {};
    ~Node() = default;
};

template <class T>
class List
{
private:
    Node<T> *head;
    Node<T> *tail;

public:
    List();
    ~List();
    bool is_empty() const;
    void push(const T& data); //consider removing
    void pop(); //consider removing
    T& top(); //consider removing

    void insert_before(Node<T>* next_node, const T& data);

    class iterator;
    iterator begin();
    iterator end();
};

template <class T>   
List<T>::List(): head(nullptr), tail(nullptr) {}

template <class T>   
List<T>::~List()
{
    while (head != nullptr)
    {
        Node<T>* next_node = head->next;
        delete head;
        head = next_node;
    }
    
}
template<class T>
bool List<T>::is_empty() const
{
    return (head == nullptr);
}

template<class T>
void List<T>::push(const T& data)
{
    Node<T>* new_node = new Node<T>(data);

    if(this->is_empty())
    {
        tail = new_node;
    }
    else
    {
        new_node->next = head;
        (new_node->next)->previous = new_node;
    }
    
    head = new_node;
    return;
}

template<class T>
void List<T>::pop()
{
    Node<T>* to_remove = head;
    head = head->next;
    head->previous = nullptr;
    delete to_remove;
}

template<class T>
T& List<T>::top()
{
    return head->data;
}

template<class T>
void List<T>::insert_before(Node<T>* next_node, const T& data)
{
    Node<T>* new_node = new Node<T>(data);
    new_node->previous = next_node->previous;
    new_node->next = next_node;
    next_node->previous = new_node;
    if(head == next_node)
        head = new_node;
}

//*************iterator********************************************************

    template<class T>
    typename List<T>::iterator List<T>::begin()
    {
        return iterator(head);
    }

    template<class T>
    typename List<T>::iterator List<T>::end()
    {
        return nullptr;
    }


    template<class T>
    class List<T>::iterator
    {
    private:
        Node<T>* curr;
        iterator(Node<T>* curr) : curr(curr) {};
        friend class List<T>;

    public:
        // Assumptions: non for all iterator's methods

        //dereference current element to access element
        T& operator*() const
        {
            assert(curr != nullptr);
            return curr->data;
        }

        //advance iterator to next element in a matrix (prefix)
        iterator& operator++()
        {
            curr = curr->next;
            return *this;
        }

        //advance iterator to next element in a matrix (postfix)
        iterator operator++(int)
        {
            iterator result = *this;
            ++*this;
            return result;
        }

        //true if iterator are equal iterators. false otherwise
        bool operator==(const iterator& it) const
        {
            return curr == it.curr;
        }

        //true if iterator are not equal iterators. false otherwise
        bool operator!=(const iterator& it) const
        {
            return !(*this==it);
        }

        //iterator constructor
        iterator(const iterator&) = default;

        //iterator assigment operator
        iterator& operator=(const iterator&) = default;

        //iterator destructor
        ~iterator() = default;
    };



#endif //WET1_LIST_H