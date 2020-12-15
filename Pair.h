#ifndef WET1_Pair_H
#define WET1_Pair_H

template <class S, class T>
class Pair
{
public:
    S first;
    T second;

    //Assumptions on S: constructor defined
    //Assumptions on T: constructor defined
    Pair(S first = S(), T second = T());

    //Assumptions on S: constructor defined
    //Assumptions on T: constructor defined
    Pair(const Pair<S,T>& to_copy);

    //Assumptions on S: = asigment defined
    //Assumptions on T: = asigment defined
    Pair<S, T>& operator=(const Pair<S,T>& other);

    //Assumptions on S: = destructor defined
    //Assumptions on T: = destructor defined
    ~Pair() = default;

    bool operator<(const Pair<S,T>& rhs) const;
};

//Assumptions on S: == operator defined
//Assumptions on T: if lhs.first == rhs.first, == operator defined
template <class S, class T>
bool operator==(const Pair<S,T>& lhs, const Pair<S,T>& rhs);

//Assumptions on S: == operator defined
//Assumptions on T: if lhs.first == rhs.first, == operator defined
template <class S, class T>
bool operator!=(const Pair<S,T>& lhs, const Pair<S,T>& rhs);

//Assumptions on S: < operator defined
//Assumptions on T: if lhs.first < rhs.first, < operator defined
template <class S, class T>
bool operator<(const Pair<S,T>& lhs, const Pair<S,T>& rhs);

//Assumptions on S: < operator defined, == operator defined
//Assumptions on T: if lhs.first < rhs.first, < operator defined. if lhs.first == rhs.first, == operator defined
template <class S, class T>
bool operator<=(const Pair<S,T>& lhs, const Pair<S,T>& rhs);

//Assumptions on S: < operator defined, == operator defined
//Assumptions on T: if lhs.first < rhs.first, < operator defined. if lhs.first == rhs.first, == operator defined
template <class S, class T>
bool operator>(const Pair<S,T>& lhs, const Pair<S,T>& rhs);

//Assumptions on S: < operator defined
//Assumptions on T: if lhs.first < rhs.first, < operator defined
template <class S, class T>
bool operator>=(const Pair<S,T>& lhs, const Pair<S,T>& rhs);


//***********************************function implementation****************************************

template <class S, class T>
Pair<S, T>::Pair(S first, T second) : first(first), second(second) {}

template <class S, class T>
Pair<S, T>::Pair(const Pair<S,T>& to_copy) : first(to_copy.first), second(to_copy.second) {}

template <class S, class T>
Pair<S, T>& Pair<S, T>::operator=(const Pair<S,T>& other) 
{
    first = other.first;
    second = other.second;
}

template <class S, class T>
bool Pair<S, T>::operator<(const Pair<S,T>& rhs) const
{
    return ((this->first < rhs.first) || (this->first  == rhs.first && this->second < rhs.second));
    //return (*this) < rhs;
}

template <class S, class T>
bool operator==(const Pair<S,T>& lhs, const Pair<S,T>& rhs)
{
    return (lhs.first == rhs.first && lhs.second == rhs.second);
}

template <class S, class T>
bool operator!=(const Pair<S,T>& lhs, const Pair<S,T>& rhs)
{
    return !(lhs == rhs);
}

template <class S, class T>
bool operator<(const Pair<S,T>& lhs, const Pair<S,T>& rhs)
{
    return ((lhs.first < rhs.first) || (lhs.first == rhs.first && lhs.second < rhs.second));
}

template <class S, class T>
bool operator<=(const Pair<S,T>& lhs, const Pair<S,T>& rhs)
{
    return (lhs < rhs || lhs == rhs);
}

template <class S, class T>
bool operator>(const Pair<S,T>& lhs, const Pair<S,T>& rhs)
{
    return !(lhs <= rhs);
}

template <class S, class T>
bool operator>=(const Pair<S,T>& lhs, const Pair<S,T>& rhs)
{
    return !(lhs < rhs);
}

#endif //WET1_Pair_H
