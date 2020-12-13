#ifndef WET1_COURSE_MANGAGER_H
#define WET1_COURSE_MANGAGER_H

#include "CourseData.h"


//typedef std::set<std::pair<int, int>> ClassesTree;

class CoursesManager
{
private:
    std::map<int, ClassesTree* > most_viewed;
    std::map<int const, CourseData> course_map;

public:
    CoursesManager() = default;
    ~CoursesManager() = default;
    void AddCourse(const int courseID, const int numOfClasses);
    // void RemoveCourse(const int courseID);
};























#endif //WET1_COURSE_MANGAGER_H