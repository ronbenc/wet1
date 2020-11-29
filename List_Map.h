#ifndef WET1_LIST_MAP_H
#define WET1_LIST_MAP_H
#include <cassert>

template <class S, class T>
class Map_Node
{
public:
    S key;
    T value;
    Map_Node* next;
    Map_Node* previous;

    Map_Node(const S& key) : key(key), next(nullptr), previous(nullptr) {};
    ~Map_Node() = default;
};

template <class S, class T>
class List_Map
{
private:
    Map_Node<S, T> *head;
    Map_Node<S, T> *tail;

public:
    List_Map();
    List_Map(const List_Map& to_copy);
    ~List_Map();
    bool is_empty() const;
    T& operator[] (const S& key);

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

    iterator erase(iterator pos);

private:
    void push_front(const S& key); 
    void push_back(const S& key);
    iterator insert_before(iterator pos, const S& key);
};

template <class S, class T>
List_Map<S, T>::List_Map(): head(nullptr), tail(nullptr) {}

template <class S, class T>
List_Map<S, T>::List_Map(const List_Map& to_copy): head(nullptr), tail(nullptr) 
{
    assert(this->is_empty());
    for(const T& item : to_copy)
        this->push_back(item);
}

template <class S, class T>
List_Map<S, T>::~List_Map()
{
    while (this->begin() != nullptr)
    {
        erase(this->begin());
    }
}
template <class S, class T>
bool List_Map<S, T>::is_empty() const
{
    return (head == nullptr);
}

//assumptions on S: '<' operator defined
template <class S, class T>
T& List_Map<S, T>::operator[] (const S& key)
{
    List_Map<S, T>::iterator it = this->begin();
    for(it; it != this->end() && it->key < key; ++it);
    if(it == this->end() || it->key != key)
    {
        it = insert_before(it, key);
    }

    return it->value;
}

template <class S, class T>
void List_Map<S, T>::push_front(const S& key)
{
    Map_Node<S, T>* new_node = new Map_Node<S, T>(key);

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

template <class S, class T>
void List_Map<S, T>::push_back(const S& key)
{
    if(this->is_empty())
    {
        return push_front(key);
    }

    Map_Node<S, T>* new_node = new Map_Node<S, T>(key);

    new_node->previous = tail;
    (new_node->previous)->next = new_node;
    tail = new_node;
}

template <class S, class T>
typename List_Map<S, T>::iterator List_Map<S, T>::insert_before(iterator pos, const S& key)
{
    if(pos == this->end()) 
    {
        push_back(key);
        return iterator(tail);
    }

    if(pos == this->begin())
    {
        push_front(key);
        return iterator(head);
    }

    Map_Node<S, T>* new_node = new Map_Node<S, T>(key);
    Map_Node<S, T>* next_node = pos.curr;

    new_node->next = next_node;
    new_node->previous =(next_node->previous);
    (next_node->previous)->next = new_node;        
    next_node->previous = new_node;
  
    return iterator(new_node);
}

template <class S, class T>
typename List_Map<S, T>::iterator List_Map<S, T>::erase(iterator pos)
{
     Map_Node<S, T>* to_delete = pos.curr;
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

//*************iterator********************************************************

    template <class S, class T>
    typename List_Map<S, T>::iterator List_Map<S, T>::begin()
    {
        return iterator(head);
    }

    template <class S, class T>
    typename List_Map<S, T>::iterator List_Map<S, T>::end()
    {
        return nullptr;
    }

    template <class S, class T>
    class List_Map<S, T>::iterator
    {
    private:
        Map_Node<S, T>* curr;
        iterator(Map_Node<S, T>* curr) : curr(curr) {};
        friend class List_Map<S, T>;

    public:
        // Assumptions: non for all iterator's methods

        Map_Node<S, T>* operator->() const
        {
            assert(curr != nullptr);
            return curr;
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
    template <class S, class T>
    typename List_Map<S, T>::const_iterator List_Map<S, T>::begin() const
    {
        return iterator(head);
    }

    template <class S, class T>
    typename List_Map<S, T>::const_iterator List_Map<S, T>::end() const
    {
        return nullptr;
    }

    template <class S, class T>
    class List_Map<S, T>::const_iterator
    {
    private:
        Map_Node<S, T>* curr;
        const_iterator(Map_Node<S, T>* curr) : curr(curr) {};
        friend class List_Map<S, T>;

    public:
        // Assumptions: non for all const_iterator's methods

        T& operator*() const
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
            const_iterator result = *this;
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

    template <class S, class T>
    typename List_Map<S, T>::reverse_iterator List_Map<S, T>::rbegin()
    {
        return reverse_iterator(tail);
    }

    template <class S, class T>
    typename List_Map<S, T>::reverse_iterator List_Map<S, T>::rend()
    {
        return nullptr;
    }

    template <class S, class T>
    class List_Map<S, T>::reverse_iterator
    {
    private:
        Map_Node<S, T>* curr;
        reverse_iterator( Map_Node<S, T>* curr) : curr(curr) {};
        friend class List_Map<S, T>;

    public:
        // Assumptions: non for all reverse_iterator's methods

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

    template <class S, class T>
    typename List_Map<S, T>::const_reverse_iterator List_Map<S, T>::rbegin() const
    {
        return reverse_iterator(tail);
    }

    template <class S, class T>
    typename List_Map<S, T>::const_reverse_iterator List_Map<S, T>::rend() const
    {
        return nullptr;
    }

    template <class S, class T>
    class List_Map<S, T>::const_reverse_iterator
    {
    private:
        Map_Node<S, T>* curr;
        const_reverse_iterator( Map_Node<S, T>* curr) : curr(curr) {};
        friend class List_Map<S, T>;

    public:
        // Assumptions: non for all const_reverse_iterator's methods

        T& operator*() const
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
            reverse_iterator result = *this;
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