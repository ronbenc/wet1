#include "CoursesManager.h"


void CoursesManager::AddCourse(const int courseID, const int numOfClasses)
{
  if(courseID <= 0 || numOfClasses <= 0)
  {
    throw InvalidInput();
  }
  if(course_map.contains(courseID))
  {
    throw Failure();
  }
  assert(courseID > 0 && numOfClasses > 0 && !course_map.contains(courseID));
  course_map.insert(courseID, numOfClasses);
}

void CoursesManager::RemoveCourse(const int courseID)
{
  if(courseID <= 0)
  {
    throw InvalidInput();
  }
  if(!course_map.contains(courseID))
  {
    throw Failure();             
  }

  assert(courseID > 0 && course_map.contains(courseID));

  CourseData to_remove(course_map[courseID]);
  for(int classID = 0; classID < to_remove.num_of_classes; classID++)
  {
      if(to_remove.classes_array[classID] != most_viewed.end())
      {
        List_Map<int, ClassesTree>::iterator curr_time_it = to_remove.classes_array[classID];
        curr_time_it->value.removeNode(Pair<int, int>(courseID, classID));

        if(curr_time_it->value.getSize() == 0)
        {
          most_viewed.erase(curr_time_it);
        }
      }
  }
  course_map.remove(courseID);
}

void CoursesManager::WatchClass(const int courseID, const int classID, int time)
{
  if(time <= 0 || classID < 0 || courseID <= 0)
  {
    throw InvalidInput();
  }
  if(!course_map.contains(courseID))
  {
    throw Failure();
  }
  if(classID+1 > course_map[courseID].num_of_classes)
  {
    throw InvalidInput();
  }
  assert(time > 0 && classID >= 0 && courseID > 0 && course_map.contains(courseID) && classID < course_map[courseID].num_of_classes);

  List_Map<int, ClassesTree>::iterator curr_time_it = course_map[courseID].classes_array[classID];
  if(curr_time_it == most_viewed.end())
  {
    AddTimeViewed(courseID, classID, time);
  }
  else
  {
    UpdateTimeViewed(curr_time_it ,courseID, classID, time);
  }
}

int CoursesManager::TimeViewed(const int courseID, const int classID)
{
  if(classID < 0 || courseID <= 0 )
  {
    throw InvalidInput();
  }
  if(!course_map.contains(courseID))
  {
    throw Failure();
  }
  if(classID+1 > course_map[courseID].num_of_classes)
  {
    throw InvalidInput();
  }
  assert(classID >= 0 && courseID > 0 && course_map.contains(courseID) && classID < course_map[courseID].num_of_classes);

  List_Map<int, ClassesTree>::iterator time_it = course_map[courseID].classes_array[classID];
  if(time_it == most_viewed.end())
  {
    return 0;
  }
  else
  {
    assert(time_it->key);
    return time_it->key;
  }
}

void CoursesManager::GetMostViewedClasses(int numOfClasses, int* courses, int* classes) const
{
  if(numOfClasses <= 0)
  {
    throw InvalidInput();
  }
  int index = 0;
  for(List_Map<int, ClassesTree>::const_reverse_iterator most_viewed_it = most_viewed.rbegin(); most_viewed_it != most_viewed.rend(); ++most_viewed_it)
  {
    for(ClassesTree::const_iterator classes_it = most_viewed_it->value.cbegin(); (classes_it != most_viewed_it->value.cend() && index < numOfClasses ); ++classes_it, ++index)
    {
      courses[index] = (*classes_it).first;
      classes[index] = (*classes_it).second;
    }
  }

  for(Map<int const, CourseData>::const_iterator course_it = course_map.cbegin(); course_it != course_map.cend() && (index < numOfClasses); ++course_it)
  {
    int curr_course = (*course_it).first;
    for(Avoided::const_iterator classes_it = (*course_it).second.zero_viewing_time.begin(); (classes_it != (*course_it).second.zero_viewing_time.end() && index < numOfClasses); ++classes_it, ++index)
    {
      courses[index] = curr_course;
      classes[index] = (*classes_it);
    }
  }

  if(index < numOfClasses)
  {
    throw Failure();
  }

}

// void CoursesManager::PrintMostViewed() //delete!
// {
//   for(List_Map<int, ClassesTree>::reverse_iterator most_viewed_it = most_viewed.rbegin(); most_viewed_it != most_viewed.rend(); most_viewed_it++)
//   {
//     int curr_time = most_viewed_it->key;
//     ClassesTree curr_classes = most_viewed_it->value;
//     for(ClassesTree::const_iterator classes_it = curr_classes.cbegin(); classes_it != curr_classes.cend(); classes_it++)
//     {
//       std::cout<<"time: "<<curr_time<<", lecture: "<<(*classes_it).first<<" ,class: "<<(*classes_it).second<<std::endl;
//     }
//   }

//   //print zero viewing time
//   for(Map<int const, CourseData>::const_iterator course_it = course_map.cbegin(); course_it != course_map.cend(); course_it++)
//   {
//     for(const unsigned int& index : (*course_it).second.zero_viewing_time)
//     {
//       std::cout<<"Time: 0, lecture: "<<(*course_it).first<<" ,class: "<<index<<std::endl;
//     }
//   }
// }

//***********************************************private methods***********************************************************
void CoursesManager::AddTimeViewed(const int courseID, const int classID, int time)
{
  assert(course_map[courseID].classes_array[classID] == most_viewed.end());

  List_Map<int, ClassesTree>::iterator new_time_it = most_viewed.find_position(time);

  if(new_time_it == most_viewed.end() || new_time_it->key != time) 
  {
      new_time_it = most_viewed.insert(new_time_it, time);
  }

  new_time_it->value.insertNode(Pair<int, int>(courseID, classID));
  course_map[courseID].classes_array[classID] = new_time_it;
  course_map[courseID].zero_viewing_time.UnAvoid(classID);
}

void CoursesManager::UpdateTimeViewed(List_Map<int, ClassesTree>::iterator prev_time_it, const int courseID, const int classID, int time)
{
  assert(course_map[courseID].classes_array[classID] != most_viewed.end());

  prev_time_it->value.removeNode(Pair<int, int>(courseID, classID)); //remove from old time value
  time += prev_time_it->key; //update time

  List_Map<int, ClassesTree>::iterator new_time_it = most_viewed.find_position(prev_time_it, time);

  if(new_time_it == most_viewed.end() || new_time_it->key != time) 
  {
      new_time_it = most_viewed.insert(new_time_it, time);
  }

  new_time_it->value.insertNode(Pair<int, int>(courseID, classID));
  course_map[courseID].classes_array[classID] = new_time_it;

  if(prev_time_it->value.getSize() == 0)
  {
    most_viewed.erase(prev_time_it);
  }
}