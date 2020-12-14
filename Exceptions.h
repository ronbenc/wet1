#ifndef WET1_EXCEPTION_H
#define WET1_EXCEPTION_H

#include <iostream>

class Exception : public std::exception {};

//******************CoursesManagerExceptions*******************
class CoursesManagerExceptions : public Exception {};

class InvalidInput : public CoursesManagerExceptions {};

class Failure : public CoursesManagerExceptions {};

#endif //WET1_EXCEPTION_H