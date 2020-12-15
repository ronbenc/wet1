#ifndef WET1_AVOIDED_H
#define WET1_AVOIDED_H


#include <cassert>
#include <iostream>

class Avoided
{
private:
    const int size;
    int start;
    int* avoided_fwd;
    int* avoided_bwd;

public:
    Avoided(const int size);
    Avoided(const Avoided& to_copy);
    ~Avoided();
    void UnAvoid(const int index);

    class const_iterator;
    const_iterator begin() const;
    const_iterator end() const;
};

//*************const_iterator********************************************************

class Avoided::const_iterator
{
private:
    const Avoided* const avoided;
    unsigned int index;
    const_iterator(const Avoided* avoided, int index);
    friend class Avoided;
public:
    const unsigned int& operator*() const;
    const_iterator& operator++();
    const_iterator operator++(int);
    bool operator==(const const_iterator& it) const;
    bool operator!=(const const_iterator& it) const;
    const_iterator(const const_iterator&) = default;
    const_iterator& operator=(const const_iterator&) = default;
    ~const_iterator() = default;
};

#endif //WET1_AVOIDED_H