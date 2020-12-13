#include "CourseData.h"

CourseData::CourseData(const int& num_of_classes) : num_of_classes(num_of_classes), zero_viewing_time(num_of_classes)
{
    classes_array = new ClassesTree*[num_of_classes];
    for(int i = 0; i < num_of_classes; i++)
    {
        classes_array[i] = nullptr;
    }
}

CourseData::CourseData(const CourseData& to_copy) : num_of_classes(to_copy.num_of_classes), zero_viewing_time(to_copy.zero_viewing_time)
{
    classes_array = new ClassesTree*[num_of_classes];
    for(int i = 0; i < num_of_classes; i++)
    {
        classes_array[i] = to_copy.classes_array[i];
    }
}

CourseData::~CourseData()
{
    // for(int i =0; i < num_of_classes; i++)
    // {
    //     if(classes_array[i] != nullptr)
    //     {
    //         delete classes_array[i];
    //     }
    // }
    delete[] classes_array;
}
