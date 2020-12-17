#ifndef WET1_COURSE_DATA_H
#define WET1_COURSE_DATA_H

#include "Pair.h"
#include "List_Map.h"
#include "Avoided.h"
#include "AVL_Tree.h"
#include "AVL_Tree_iterator.h"
#include "Map.h"

typedef AVL_Tree<Pair<int, int>> ClassesTree;

class CourseData
{
public:
    const int num_of_classes;
    Avoided zero_viewing_time;
    List_Map<int, ClassesTree>::iterator* classes_array;

    CourseData(const int num_of_classes = 0);
    CourseData(const CourseData& to_copy);
    ~CourseData();

    bool operator<(const CourseData& rhs) const;
    bool operator==(const CourseData& rhs) const;
    bool operator<=(const CourseData& rhs) const;
};


#endif //WET1_COURSE_DATA_H