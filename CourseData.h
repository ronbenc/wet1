#ifndef WET1_COURSE_DATA_H
#define WET1_COURSE_DATA_H

#include "List_Map.h"
#include "Avoided.h"
#include <set>
#include <map>

typedef std::set<std::pair<int, int>> ClassesTree;

class CourseData
{
public:
    //ClassesTree** classes_array; //an array of pointers / maybe iterators /naive approach - int
    List_Map<int, ClassesTree>::iterator* classes_array;
    const int num_of_classes;
    Avoided zero_viewing_time;

    CourseData(const int& num_of_classes = 0);
    CourseData(const CourseData& to_copy);
    ~CourseData();
    //CourseData& operator= (const CourseData& to_copy);

    void WatchClass(int classID, int time);
    int TimeViewed(int classID) const;
};

#endif //WET1_COURSE_DATA_H