#ifndef WET1_AVOIDED_H
#define WET1_AVOIDED_H


#include <cassert>
#include <iostream>

class Avoided
{
public:
    unsigned int* avoided_fwd;
    unsigned int* avoided_bwd;
    unsigned start;

public:
    const unsigned int size;

    Avoided(const unsigned int& size);
    Avoided(const Avoided& to_copy);
    ~Avoided();
    void UnAvoid(const unsigned int& index);
    void PrintAvoided();
};










#endif //WET1_AVOIDED_H