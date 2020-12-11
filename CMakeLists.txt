cmake_minimum_required(VERSION 3.0.0)
project(IntMatrix VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(wet1 map_tester.cpp TreeNode.h List_Map.h)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
