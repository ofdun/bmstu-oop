#ifndef ITERATOREXCEPTIONS_H
#define ITERATOREXCEPTIONS_H

#include "BaseException.h"

class OutOfBoundsException final : public BaseException
{
public:
    OutOfBoundsException(const char *filename,
                         const char *funcName,
                         int line,
                         time_t time,
                         const char *text = "Iterator is out of bounds!") : BaseException(
        filename, funcName, line, time, text)
    {
    }
};

class ExpiredException final : public BaseException
{
public:
    ExpiredException(const char *filename,
                     const char *funcName,
                     int line,
                     time_t time,
                     const char *text = "Iterator is expired!") : BaseException(filename, funcName, line, time, text)
    {
    }
};

#endif //ITERATOREXCEPTIONS_H