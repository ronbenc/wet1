cmake_minimum_required(VERSION 3.0.0)
project(CourseManager VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(CourseManager map_tester.cpp CoursesManager.cpp CourseData.cpp Avoided.cpp) 

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
