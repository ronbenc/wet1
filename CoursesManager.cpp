#include "CoursesManager.h"


void CoursesManager::AddCourse(const int courseID, const int numOfClasses)
{
  assert(courseID > 0 && numOfClasses > 0);
  course_map.insert(std::pair<int const, CourseData>(courseID, numOfClasses));
}

void CoursesManager::RemoveCourse(const int courseID)
{
  assert(courseID > 0);
  assert(course_map.count(courseID) != 0);

  //CourseData to_remove(course_map[courseID]);
  // for(int classID = 0; classID < to_remove.num_of_classes; classID++)
  // {
  //     if(to_remove.classes_array[classID] != nullptr)
  //     {
  //         to_remove.classes_array[classID]->erase(std::pair<int, int>(courseID, classID));
  //     }
  // }
  course_map.erase(courseID);
}

void CoursesManager::WatchClass(const int courseID, const int classID, int time)
{
  assert(courseID > 0 && classID >= 0 && time >= 0 && course_map.count(courseID) != 0 && classID < course_map[courseID].num_of_classes);
  if(time == 0)
  {
    return;
  }
  
  List_Map<int, ClassesTree>::iterator curr_time_it = course_map[courseID].classes_array[classID];
  if(curr_time_it == most_viewed.end())  //handle uninitialized
  {
    assert(course_map[courseID].classes_array[classID] == most_viewed.end());
    most_viewed[time].insert(std::pair<int const, int const>(courseID, classID)); //optimize using hints! avoid double search
    course_map[courseID].classes_array[classID] = most_viewed.find_position(time);
    course_map[courseID].zero_viewing_time.UnAvoid(classID);
  }
  else //update time
  {
    assert(course_map[courseID].classes_array[classID] != most_viewed.end());
    curr_time_it->value.erase({courseID, classID});
    // if(curr_time_it->value.empty())
    // {
    //   most_viewed.erase(curr_time_it);
    // }
    int prev_time = curr_time_it->key;
    time += prev_time;
    most_viewed[time].insert(std::pair<int const, int const>(courseID, classID));
    course_map[courseID].classes_array[classID] = most_viewed.find_position(courseID); //optimize using hints! avoid double search
  }
}

void CoursesManager::PrintMostViewed()
{
  for(List_Map<int, ClassesTree>::reverse_iterator most_viewed_it = most_viewed.rbegin(); most_viewed_it != most_viewed.rend(); most_viewed_it++)
  {
    int curr_time = most_viewed_it->key;
    ClassesTree curr_classes = most_viewed_it->value;
    for(ClassesTree::const_iterator classes_it = curr_classes.begin(); classes_it != curr_classes.end(); classes_it++)
    {
      std::cout<<"time: "<<curr_time<<" ,lecture: "<<classes_it->first<<" ,class: "<<classes_it->second<<std::endl;
    }
  }

  //print zero viewing time
  for(std::map<int const, CourseData>::const_iterator course_it = course_map.begin(); course_it != course_map.end(); course_it++)
  {
    course_it->second.zero_viewing_time.PrintAvoided();
  }
}