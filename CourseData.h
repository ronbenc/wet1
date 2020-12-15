#ifndef WET1_COURSE_DATA_H
#define WET1_COURSE_DATA_H

#include "Pair.h"
#include "List_Map.h"
#include "Avoided.h"
#include <set>
#include <map>

typedef std::set<Pair<int, int>> ClassesTree;

class CourseData
{
public:
    const int num_of_classes;
    Avoided zero_viewing_time;
    List_Map<int, ClassesTree>::iterator* classes_array;

    CourseData(const int num_of_classes = 0);
    CourseData(const CourseData& to_copy);
    ~CourseData();
};

#endif //WET1_COURSE_DATA_H