#include "List.h"


template <class S, class T>
class Map_data
{
public:
    S key;
    T value;

    Map_data(const S& key) : key(key) {};
    ~Map_data() = default;
};

template <class S, class T>
class Map_list : private List<Map_data<S,T>>
{
private:

public:
    T& operator[] (const S& key);

    using List<Map_data<S,T>>::begin;
};

template <class S, class T>
T& Map_list<S,T>::operator[] (const S& key)
{
    this->push_back(key);
    return (*this->begin()).value;
}