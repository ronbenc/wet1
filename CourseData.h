#ifndef WET1_COURSE_DATA_H
#define WET1_COURSE_DATA_H

#include "Avoided.h"
#include <set>
#include <map>

typedef std::set<std::pair<int, int>> ClassesTree;

class CourseData
{
public:
    ClassesTree** classes_array; //an array of pointers
    const unsigned int num_of_classes;
    Avoided zero_viewing_time;
    int viewing_time_sum;
    
    CourseData(const unsigned int num_of_classes);
    ~CourseData();

    void WatchClass(int classID, int time);
    int TimeViewed(int classID) const;
};

#endif //WET1_COURSE_DATA_H