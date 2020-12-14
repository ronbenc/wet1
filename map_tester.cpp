#include <iostream>
#include "List_Map.h"

int main()
{
    List_Map<int, char> map;

    // //test insert
    // map[0] = 'A';
    // map[1] = 'B';
    // map.insert(2, 'C');

    // for(int i=0; i < 3; i++)
    // {
    //     assert(map[i] == char('A'+ i));
    // }

    // //test erase and is_empty
    // for(int i=0; i < 3; i++)
    // {
    //     map.erase(i);
    // }
    // assert(map.is_empty());

    // //test overriding
    // map[0] = 'A';
    // map[0] = 'a';
    // assert(map[0] == 'a');
    // map.insert(0, 'A');
    // assert(map[0] == 'A');

    List_Map<int, char>::iterator it = map.begin();
    it = map.insert(it, 1, 'A');
    map[3] = 'C';
    map[5] = 'E';
    it = map.find_position(2);
    if(it->key != 2)
        map.insert(it, 2, 'B');
    map.insert(it, 4, 'D');
    


    return 0;
}


