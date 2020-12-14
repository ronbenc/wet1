#ifndef WET1_COURSE_MANGAGER_H
#define WET1_COURSE_MANGAGER_H


#include "CourseData.h"
#include "Exceptions.h"

typedef std::set<std::pair<int, int>> ClassesTree;

class CoursesManager
{
private:
    List_Map<int, ClassesTree> most_viewed;
    std::map<int const, CourseData> course_map;

public:
    CoursesManager() = default;
    ~CoursesManager() = default;
    void AddCourse(const int courseID, const int numOfClasses);
    void RemoveCourse(const int courseID);
    void WatchClass(const int courseID, const int classID, int time);
    int TimeViewed(const int courseID, const int classID);
    void GetMostViewedClasses(int numOfClasses, int* courses, int* classes) const;

    void PrintMostViewed();

private:
    void AddTimeViewed(const int courseID, const int classID, int time);
    void UpdateTimeViewed(List_Map<int, ClassesTree>::iterator prev_time_it, const int courseID, const int classID, int time);
};























#endif //WET1_COURSE_MANGAGER_H