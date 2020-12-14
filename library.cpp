#include "library.h"
#include "CoursesManager.h"

void *Init()
{
    try
    {
        CoursesManager *DS = new CoursesManager();
        return (void*)DS;
    }
    catch(const std::bad_alloc& e)
    {
        return NULL;
    }
}

StatusType AddCourse (void *DS, int courseID, int numOfClasses)
{
    if(DS == NULL)
    {
        return INVALID_INPUT;
    }
    try
    {
        ((CoursesManager*)DS)->AddCourse(courseID, numOfClasses);
    }
    catch(const std::bad_alloc& e)
    {
        return ALLOCATION_ERROR;
    }
    catch(const InvalidInput& e)
    {
        return INVALID_INPUT;
    }
    catch(const Failure& e)
    {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType RemoveCourse(void *DS, int courseID)
{
    if(DS == NULL)
    {
        return INVALID_INPUT;
    }
    try
    {
        ((CoursesManager*)DS)->RemoveCourse(courseID);
    }
    catch(const std::bad_alloc& e)
    {
        return ALLOCATION_ERROR;
    }
    catch(const InvalidInput& e)
    {
        return INVALID_INPUT;
    }
    catch(const Failure& e)
    {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType WatchClass(void *DS, int courseID, int classID, int time)
{
    if(DS == NULL)
    {
        return INVALID_INPUT;
    }
    try
    {
        ((CoursesManager*)DS)->WatchClass(courseID, classID, time);
    }
    catch(const std::bad_alloc& e)
    {
        return ALLOCATION_ERROR;
    }
    catch(const InvalidInput& e)
    {
        return INVALID_INPUT;
    }
    catch(const Failure& e)
    {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType TimeViewed(void *DS, int courseID, int classID, int *timeViewed)
{
    if(DS == NULL)
    {
        return INVALID_INPUT;
    }
    try
    {
        *timeViewed = ((CoursesManager*)DS)->TimeViewed(courseID, classID);
    }
    catch(const std::bad_alloc& e)
    {
        return ALLOCATION_ERROR;
    }
    catch(const InvalidInput& e)
    {
        return INVALID_INPUT;
    }
    catch(const Failure& e)
    {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType GetMostViewedClasses(void *DS, int numOfClasses, int *courses, int *classes)
{
    if(DS == NULL)
    {
        return INVALID_INPUT;
    }
    try
    {
        ((CoursesManager*)DS)->GetMostViewedClasses(numOfClasses, courses, classes);
    }
    catch(const std::bad_alloc& e)
    {
        return ALLOCATION_ERROR;
    }
    catch(const InvalidInput& e)
    {
        return INVALID_INPUT;
    }
    catch(const Failure& e)
    {
        return FAILURE;
    }
    return SUCCESS;
}

void Quit(void** DS)
{
    delete *(CoursesManager**)DS;
    *DS = NULL;
}