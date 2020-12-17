cmake_minimum_required(VERSION 3.0.0)
project(wet1 VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(wet1 main.cpp Avoided.cpp CourseData.cpp CoursesManager.cpp library.cpp) 
# add_executable(wet1 main.cpp TreeNode.h AVL_Tree.h AVL_Tree_iterator.h Map.h) 

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
