#ifndef WET1_EXCEPTION_H
#define WET1_EXCEPTION_H

#include <iostream>

class Exception : public std::exception {};

//******************CoursesManagerExceptions*******************
class CoursesManagerExceptions : public Exception {};

class InvalidInput : public CoursesManagerExceptions {};

class Failure : public CoursesManagerExceptions {};

class TreeNodeException : public Exception {};
class IllegalArgument_TreeNode : public TreeNodeException 
{
    const char* what() noexcept
    {
        return "Error: illegal argument under TreeNode class";
    }
};

class AVL_TreeException : public Exception {};

class IllegalArgument_AVL_Tree : public AVL_TreeException 
{
    const char* what() noexcept
    {
        return "Error: illegal argument under AVL Tree class";
    }
};

class MapException : public Exception {};

class IllegalArgument_Map : public MapException 
{
    const char* what() noexcept
    {
        return "Error: illegal argument under Map class";
    }
};

#endif //WET1_EXCEPTION_H