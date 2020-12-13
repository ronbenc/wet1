#include "CourseData.h"

CourseData::CourseData(const unsigned int num_of_classes) : num_of_classes(num_of_classes), viewing_time_sum(0), zero_viewing_time(num_of_classes)
{
    classes_array = new std::set<std::pair<int, int>>*[num_of_classes];
    for(int i =0; i < num_of_classes; i++)
    {
        classes_array[i] = nullptr;
    }
}

CourseData::~CourseData()
{
    for(int i =0; i < num_of_classes; i++)
    {
        if(classes_array[i] != nullptr)
        {
            delete classes_array[i];
        }
        delete[] classes_array;
    }
}