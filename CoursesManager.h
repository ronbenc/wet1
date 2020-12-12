#ifndef WET1_COURSE_MANGAGER_H
#define WET1_COURSE_MANGAGER_H

#include "CourseData.h"


typedef std::set<std::pair<int, int>> ClassTree;

class CoursesManager
{
private:
    std::map<int, ClassTree* > most_viewed;
    std::map<int, CourseData> course_tree;

public:
    CoursesManager();
    ~CoursesManager();
};

CoursesManager::CoursesManager()
{
}

CoursesManager::~CoursesManager()
{
}






















#endif //WET1_COURSE_MANGAGER_H