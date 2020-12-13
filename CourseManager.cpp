#include "CoursesManager.h"

 void CoursesManager::AddCourse(int courseID, int numOfClasses)
 {
    assert(courseID > 0 && numOfClasses > 0);
    course_map.insert(courseID, numOfClasses);
 }

  void CoursesManager::RemoveCourse(int courseID)
  {
    assert(courseID > 0);
    assert(course_map.count(courseID) != 0);

    CourseData to_remove(course_map[courseID]);
    for(int classID = 0; classID < to_remove.num_of_classes; classID++)
    {
        if(to_remove.classes_array[classID] != nullptr)
        {
            to_remove.classes_array[classID]->erase(std::pair<int, int>(courseID, classID));
        }
    }
    course_map.erase(courseID);
  }