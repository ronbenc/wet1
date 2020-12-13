#include "CoursesManager.h"

// CoursesManager::CoursesManager() : most_viewed(), course_map() {}

void CoursesManager::AddCourse(const int courseID, const int numOfClasses)
{
  assert(courseID > 0 && numOfClasses > 0);
  //CourseData to_insert(numOfClasses);
  course_map.insert(std::pair<int const, CourseData>(courseID, numOfClasses));
  //course_map.insert({(const int) courseID, to_insert});
}

  // void CoursesManager::RemoveCourse(const int courseID)
  // {
  //   assert(courseID > 0);
  //   assert(course_map.count(courseID) != 0);

  //   CourseData to_remove(course_map[courseID]);
  //   for(int classID = 0; classID < to_remove.num_of_classes; classID++)
  //   {
  //       if(to_remove.classes_array[classID] != nullptr)
  //       {
  //           to_remove.classes_array[classID]->erase(std::pair<int, int>(courseID, classID));
  //       }
  //   }
  //   course_map.erase(courseID);
  // }