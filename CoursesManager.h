#ifndef WET1_COURSE_MANGAGER_H
#define WET1_COURSE_MANGAGER_H

#include "CourseData.h"


//typedef std::set<std::pair<int, int>> ClassesTree;

class CoursesManager
{
private:
    std::map<int, ClassesTree* > most_viewed;
    std::map<int, CourseData> course_map;

public:
    CoursesManager() = default;
    ~CoursesManager() = default;
    void AddCourse(int courseID, int numOfClasses);
    void RemoveCourse(int courseID);
};























#endif //WET1_COURSE_MANGAGER_H