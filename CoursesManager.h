#ifndef WET1_COURSE_MANGAGER_H
#define WET1_COURSE_MANGAGER_H

#include "CourseData.h"
#include "AVL_Tree.h"
#include "AVL_Tree_iterator.h"
#include "Map.h"
#include "Exceptions.h"

typedef AVL_Tree<Pair<int, int>> ClassesTree;

class CoursesManager
{
private:
    List_Map<int, ClassesTree> most_viewed;
    Map<int const, CourseData> course_map;

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