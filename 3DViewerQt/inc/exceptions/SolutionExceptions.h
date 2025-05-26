#pragma once

#include "BaseException.h"

class NotRegisteredInSolutionException final : public BaseException
{
public:
    NotRegisteredInSolutionException(const char *filename,
                                     const char *funcName,
                                     int line,
                                     time_t time,
                                     const char *text = "Creator was not registered in a solution!") :
        BaseException(
            filename, funcName, line, time, text)
    {
    }
};