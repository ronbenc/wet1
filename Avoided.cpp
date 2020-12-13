#include "Avoided.h"

Avoided::Avoided(const unsigned int& size) : start(0), size(size)
{
    avoided_fwd = new unsigned int [size]; 
    avoided_bwd = new unsigned int [size]; 
    for(int i = 0; i < size; i++)
    {
        avoided_fwd[i] = 1;
        avoided_bwd[i] = 1;
    }
}

Avoided::Avoided(const Avoided& to_copy) : start(to_copy.start), size(to_copy.size)
{
    avoided_fwd = new unsigned int [size]; 
    avoided_bwd = new unsigned int [size];
    for(int i = 0; i < size; i++)
    {
        avoided_fwd[i] = to_copy.avoided_fwd[i];
        avoided_bwd[i] = to_copy.avoided_bwd[i];
    } 
}

Avoided::~Avoided()
{
    delete[] avoided_fwd;
    delete[] avoided_bwd;
}

void Avoided::UnAvoid(const unsigned int& index)
{
    assert(index < size);
    if(index == start)
    {
        start+= avoided_fwd[index];
    }   
    else
    {
        avoided_fwd[index - avoided_bwd[index]] += avoided_fwd[index];
        if(index + avoided_fwd[index] < size)
        {
            avoided_bwd[index + avoided_fwd[index]] += avoided_bwd[index];
        }
    }
}

//*************const_iterator********************************************************

typename Avoided::const_iterator Avoided::begin() const
{
    return const_iterator(this, start);
}

typename Avoided::const_iterator Avoided::end() const
{
    return const_iterator(this, size);
}

Avoided::const_iterator::const_iterator(const Avoided* avoided, int index) : avoided(avoided), index(index) {}

const unsigned int& Avoided::const_iterator::operator*() const
{
    assert(index < avoided->size);

    return index;
}

typename Avoided::const_iterator& Avoided::const_iterator::operator++()
{
    index += avoided->avoided_fwd[index];
    return *this;
}

typename Avoided::const_iterator Avoided::const_iterator::operator++(int)
{
    const_iterator result = *this;
    ++*this;
    return result;
}

bool Avoided::const_iterator::operator==(const const_iterator& it) const
{
    return (avoided == it.avoided && index == it.index);
}

bool Avoided::const_iterator::operator!=(const const_iterator& it) const
{
    return !(*this == it);
}