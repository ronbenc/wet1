#include "library.h"
#include "CoursesManager.h"

void *Init()
{
    CoursesManager *DS = new CoursesManager();
    //handle exections...
    return (void*)DS;
}

StatusType AddCourse (void *DS, int courseID, int numOfClasses)
{
    ((CoursesManager*)DS)->AddCourse(courseID, numOfClasses);
    //handle exections...
    return SUCCESS;
}

StatusType RemoveCourse(void *DS, int courseID)
{
    ((CoursesManager*)DS)->RemoveCourse(courseID);
    //handle exections...
    return SUCCESS;
}

StatusType WatchClass(void *DS, int courseID, int classID, int time)
{
    ((CoursesManager*)DS)->WatchClass(courseID, classID, time);
    //handle exections...
    return SUCCESS;
}

StatusType TimeViewed(void *DS, int courseID, int classID, int *timeViewed)
{
    *timeViewed = ((CoursesManager*)DS)->TimeViewed(courseID, classID);
    //handle exections...
    return SUCCESS;
}

StatusType GetMostViewedClasses(void *DS, int numOfClasses, int *courses, int *classes)
{
    ((CoursesManager*)DS)->GetMostViewedClasses(numOfClasses, courses, classes);
    //handle exections...
    return SUCCESS;
}

void Quit(void** DS)
{
    delete (CoursesManager*)*DS;
    DS = NULL;
}