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
    List(const List& to_copy);
    ~List();
    bool is_empty() const;
    void push_front(const T& data); 
    void push_back(const T& data);
    void pop(); //consider removing
    T& top(); //consider removing  

    class iterator;
    iterator begin();
    iterator end();

    class const_iterator;
    const_iterator begin() const;
    const_iterator end() const;

    class reverse_iterator;
    reverse_iterator rbegin();
    reverse_iterator rend();

    class const_reverse_iterator;
    const_reverse_iterator rbegin() const;
    const_reverse_iterator rend() const;

    iterator insert_before(iterator pos, const T& data);
    iterator erase(iterator pos);
    iterator find(const T& data); //find first occurance
};

template <class T>   
List<T>::List(): head(nullptr), tail(nullptr) {}

template <class T>   
List<T>::List(const List& to_copy): head(nullptr), tail(nullptr) 
{
    assert(this->is_empty());
    for(const T& item : to_copy)
        this->insert_before(this->end(), item);
}

template <class T>   
List<T>::~List()
{
    while (this->begin() != nullptr)
    {
        erase(this->begin());
    }
}
template<class T>
bool List<T>::is_empty() const
{
    return (head == nullptr);
}

template<class T>
void List<T>::push_front(const T& data)
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
}

template<class T>
void List<T>::push_back(const T& data)
{
    if(this->is_empty())
    {
        push_front(data);
    }

    Node<T>* new_node = new Node<T>(data);

    new_node->previous = tail;
    (new_node->previous)->next = new_node;
    tail = new_node;
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
typename List<T>::iterator List<T>::insert_before(iterator pos, const T& data)
{
    if(pos == this->end()) 
    {
        push_back(data);
        return iterator(tail);
    }

    if(pos == this->begin())
    {
        push_front(data);
        return iterator(head);
    }

    Node<T>* new_node = new Node<T>(data);
    Node<T>* next_node = pos.curr;

    new_node->next = next_node;
    new_node->previous =(next_node->previous);
    (next_node->previous)->next = new_node;        
    next_node->previous = new_node;
  
    return iterator(new_node);
}

template<class T>
typename List<T>::iterator List<T>::erase(iterator pos)
{
    Node<T>* to_delete = pos.curr;
    if(to_delete->previous == nullptr) //to_delete is the head
    {
        head = to_delete->next;
    }
    else
    {
        (to_delete->previous)->next = to_delete->next;
    }

    if(to_delete->next == nullptr) //to_delete is the tail
    {
        tail = to_delete->previous;
    }
    else
    {
        (to_delete->next)->previous = to_delete->previous;
    }

    delete to_delete;
    return ++pos;
}

template<class T>
typename List<T>::iterator List<T>::find(const T& data)
{
    List<T>::iterator it = this->begin();
    for(it; it!=this->end(); ++it)
    {
        if(*it == data)
            break;
    }

    return it;
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
            assert(curr != nullptr);
            curr = curr->next;
            return *this;
        }

        iterator operator++(int)
        {
            assert(curr != nullptr);
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
        return const_iterator(head);
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
            assert(curr != nullptr);
            curr = curr->next;
            return *this;
        }

        const_iterator operator++(int)
        {
            assert(curr != nullptr);
            iterator result = *this;
            ++*this;
            return result;
        }

        bool operator==(const const_iterator& it) const
        {
            return curr == it.curr;
        }

        bool operator!=(const const_iterator& it) const
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
            assert(curr != nullptr);
            curr = curr->previous;
            return *this;
        }

        reverse_iterator operator++(int)
        {
            assert(curr != nullptr);
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

//*************const_reverse_iterator********************************************************

    template<class T>
    typename List<T>::const_reverse_iterator List<T>::rbegin() const
    {
        return const_reverse_iterator(tail);
    }

    template<class T>
    typename List<T>::const_reverse_iterator List<T>::rend() const
    {
        return nullptr;
    }


    template<class T>
    class List<T>::const_reverse_iterator
    {
    private:
        Node<T>* curr;
        const_reverse_iterator(Node<T>* curr) : curr(curr) {};
        friend class List<T>;

    public:
        // Assumptions: non for all iterator's methods

        const T& operator*() const
        {
            assert(curr != nullptr);
            return curr->data;
        }

        const_reverse_iterator& operator++()
        {
            assert(curr != nullptr);
            curr = curr->previous;
            return *this;
        }

        const_reverse_iterator operator++(int)
        {
            assert(curr != nullptr);
            const_reverse_iterator result = *this;
            ++*this;
            return result;
        }

        bool operator==(const const_reverse_iterator& it) const
        {
            return curr == it.curr;
        }

        bool operator!=(const const_reverse_iterator& it) const
        {
            return !(*this==it);
        }

        const_reverse_iterator(const const_reverse_iterator&) = default;
        const_reverse_iterator& operator=(const const_reverse_iterator&) = default;
        ~const_reverse_iterator() = default;
    };

#endif //WET1_LIST_H