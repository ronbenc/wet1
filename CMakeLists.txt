cmake_minimum_required(VERSION 3.0.0)
project(CourseManager VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(avl main.cpp TreeNode.h AVL_Tree.h AVL_Tree_iterator.h) 

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
