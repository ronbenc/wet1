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

    class const_iterator;
    const_iterator begin() const;
    const_iterator end() const;

    class reverse_iterator;
    reverse_iterator rbegin();
    reverse_iterator rend();
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

        T& operator*() const
        {
            assert(curr != nullptr);
            return curr->data;
        }

        iterator& operator++()
        {
            curr = curr->next;
            return *this;
        }

        iterator operator++(int)
        {
            iterator result = *this;
            ++*this;
            return result;
        }

        bool operator==(const iterator& it) const
        {
            return curr == it.curr;
        }

        bool operator!=(const iterator& it) const
        {
            return !(*this==it);
        }

        iterator(const iterator&) = default;
        iterator& operator=(const iterator&) = default;
        ~iterator() = default;
    };

//*************const_iterator********************************************************

    template<class T>
    typename List<T>::const_iterator List<T>::begin() const
    {
        return iterator(head);
    }

    template<class T>
    typename List<T>::const_iterator List<T>::end() const
    {
        return nullptr;
    }


    template<class T>
    class List<T>::const_iterator
    {
    private:
        Node<T>* curr;
        const_iterator(Node<T>* curr) : curr(curr) {};
        friend class List<T>;

    public:
        // Assumptions: non for all iterator's methods

        const T& operator*() const
        {
            assert(curr != nullptr);
            return curr->data;
        }

        const_iterator& operator++()
        {
            curr = curr->next;
            return *this;
        }

        const_iterator operator++(int)
        {
            iterator result = *this;
            ++*this;
            return result;
        }

        bool operator==(const iterator& it) const
        {
            return curr == it.curr;
        }

        bool operator!=(const iterator& it) const
        {
            return !(*this==it);
        }

        const_iterator(const const_iterator&) = default;
        const_iterator& operator=(const const_iterator&) = default;
        ~const_iterator() = default;
    };

//*************reverse_iterator********************************************************

    template<class T>
    typename List<T>::reverse_iterator List<T>::rbegin()
    {
        return reverse_iterator(tail);
    }

    template<class T>
    typename List<T>::reverse_iterator List<T>::rend()
    {
        return nullptr;
    }


    template<class T>
    class List<T>::reverse_iterator
    {
    private:
        Node<T>* curr;
        reverse_iterator(Node<T>* curr) : curr(curr) {};
        friend class List<T>;

    public:
        // Assumptions: non for all iterator's methods

        T& operator*() const
        {
            assert(curr != nullptr);
            return curr->data;
        }

        reverse_iterator& operator++()
        {
            curr = curr->previous;
            return *this;
        }

        reverse_iterator operator++(int)
        {
            reverse_iterator result = *this;
            ++*this;
            return result;
        }

        bool operator==(const reverse_iterator& it) const
        {
            return curr == it.curr;
        }

        bool operator!=(const reverse_iterator& it) const
        {
            return !(*this==it);
        }

        reverse_iterator(const reverse_iterator&) = default;
        reverse_iterator& operator=(const reverse_iterator&) = default;
        ~reverse_iterator() = default;
    };

#endif //WET1_LIST_H