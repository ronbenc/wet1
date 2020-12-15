#include <iostream>
#include "List_Map.h"

void Print(const List_Map<int, char> map)
{
    for(List_Map<int, char>::const_iterator it = map.begin(); it!= map.end(); ++it)
    {
        std::cout<<"Key: "<<it->key<<", Value"<<it->value<<std::endl;
    }
}

void Reverse_Print(const List_Map<int, char> map)
{
    for(List_Map<int, char>::const_reverse_iterator it = map.rbegin(); it!= map.rend(); ++it)
    {
        std::cout<<"Key: "<<it->key<<", Value"<<it->value<<std::endl;
    }
}

int main()
{
    List_Map<int, char> map;

    //test insert
    map[0] = 'A';
    map[1] = 'B';
    map.insert(2, 'C');

    for(int i=0; i < 3; i++)
    {
        assert(map[i] == char('A'+ i));
    }

    //test erase and is_empty
    for(int i=0; i < 3; i++)
    {
        map.erase(i);
    }
    assert(map.is_empty());

    //test overriding
    map[0] = 'A';
    map[0] = 'a';
    assert(map[0] == 'a');
    map.insert(0, 'A');
    assert(map[0] == 'A');

    //test iterator 
    for(List_Map<int, char>::iterator it = map.begin(); it!= map.end(); ++it)
    {
        std::cout<<"Key: "<<it->key<<", Value"<<it->value<<std::endl;
    }

    //test reverse_iterator 
    for(List_Map<int, char>::reverse_iterator it = map.rbegin(); it!= map.rend(); ++it)
    {
        std::cout<<"Key: "<<it->key<<", Value"<<it->value<<std::endl;
    }

    //test const_iterator
    Print(map);

    //test const_reverse_iterator
    Reverse_Print(map);

    // List_Map<int, char>::iterator it = map.begin();
    // it = map.insert(it, 1, 'A');
    // map[3] = 'C';
    // map[5] = 'E';
    // it = map.find_position(2);
    // if(it->key != 2)
    //     map.insert(it, 2, 'B');
    // map.insert(it, 4, 'D');
    


    return 0;
}


