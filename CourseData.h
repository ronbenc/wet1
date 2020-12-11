#ifndef WET1_COURSE_DATA_H
#define WET1_COURSE_DATA_H

#include <set>
#include <map>

class CourseData
{
public:
    std::map<int, std::set<std::pair<int, int>>* >** classes_array;
    //std::set<std::pair<int, int>>** classes_array; //an array of pointers
    const unsigned int num_of_classes;
    int sum;
    //maybe "avoided" arrays

    CourseData(const unsigned int num_of_classes);
    ~CourseData();

    void WatchClass(int classID, int time);
    int TimeViewed(int classID) const;
};

#endif //WET1_COURSE_DATA_H