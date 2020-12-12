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

void Avoided::PrintAvoided()
{
    for(int i = start; i < size; i += avoided_fwd[i])
    {
        std::cout<<i;
    }
    std::cout<<std::endl;
}